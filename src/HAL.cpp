#include "HAL.h"

// GPIO Registers page 4877 
//outs
#define GPIO_SETDATAOUT     0x194
#define GPIO_CLEARDATAOUT   0x190
#define GPIO_OE             0x134
//ins
#define GPIO_LEVELDETECT0 0x140
#define GPIO_LEVELDETECT1 0x144
#define GPIO_RISINGDETECT 0x148
#define GPIO_FALLINGDETECT 0x14C
#define GPIO_IRQSTATUS_0 0x2C
#define GPIO_IRQSTATUS_1 0x30
#define GPIO_IRQSTATUS_SET_0 0x34
#define GPIO_IRQSTATUS_SET_1 0x38
#define GPIO_DATAIN 0x138

// Memory maps
#define GPIO_0 0x44E07000  //inputs,            page 180
#define GPIO_1 0x4804C000  //system outputs,    page 182
#define GPIO_2 0x481AC000  //human outputs,      page 183
#define GPIO_3 0x481AE000  //unknown,           page 183
#define INTERRUPT_CONTROLLER 0x48200000         //page 183

//Interrupt Tables: page 465
#define INTR_GPIO_0 97
#define INTR_GPIO_1 99
#define INTR_GPIO_2 33

/* My pulse codes */
#define PULSE_STOP_THREAD _PULSE_CODE_MINAVAIL + 1
#define PULSE_INTR_ON_PORT0 _PULSE_CODE_MINAVAIL + 2



#define ONE_MILLISECOND 1000

#define GPIO_MMAP_SIZE   0x1000      //based on GPIO address range (4KB)
using namespace std;

//===================== contructors & destructors =====================

HAL::HAL(int connectionID)
    :gpio_bank_0(mmap_device_io(GPIO_MMAP_SIZE, (uint64_t) (GPIO_0)))
    , gpio_bank_1(mmap_device_io(GPIO_MMAP_SIZE, (uint64_t) (GPIO_1)))
    , gpio_bank_2(mmap_device_io(GPIO_MMAP_SIZE, (uint64_t) (GPIO_2)))
    , externalConID(connectionID)
    , last_causing_pin(0)
    , last_pin_status(0)
    , inputPins(0)
    , receivingRunning(false) {

    pinsList.push_back(LASER_FRONT_BIT);
    pinsList.push_back(LASER_SORTING_BIT);
    pinsList.push_back(LASER_METAL_BIT);
    pinsList.push_back(ADC_AREA_BIT);
    pinsList.push_back(SORTING_STATUS_BIT);
    pinsList.push_back(LASER_RAMP_BIT);
    pinsList.push_back(LASER_BACK_BIT);
    pinsList.push_back(BUTTON_START_BIT);
    pinsList.push_back(BUTTON_STOP_BIT);
    pinsList.push_back(BUTTON_RESET_BIT);
    pinsList.push_back(BUTTON_ESTOP_BIT);
    pinsList.push_back(ADC_SIDE_AREA_BIT);

    for(auto pin : pinsList) {
        inputPins |= (1 << pin);
    }


    // request IO privileges (without this code, the code works too. What's the explanation?)
    ThreadCtl(_NTO_TCTL_IO, 0);

    int procmgr_status = procmgr_ability(
        0,
        PROCMGR_ADN_ROOT | PROCMGR_AOP_ALLOW | PROCMGR_AID_INTERRUPT,
        PROCMGR_ADN_NONROOT | PROCMGR_AOP_ALLOW | PROCMGR_AID_INTERRUPT,
        PROCMGR_ADN_ROOT | PROCMGR_AOP_ALLOW | PROCMGR_AID_IO,
        PROCMGR_ADN_NONROOT | PROCMGR_AOP_ALLOW | PROCMGR_AID_IO,
        PROCMGR_AID_EOL
    );
    if(procmgr_status != EOK) {
        throw std::runtime_error(std::string(__FUNCTION__) + "Requested abilities failed or denied!\n");
    }
    InterruptEnable(); //Enables interrupts.
    channelID = ChannelCreate(0);//Create channel to receive interrupt pulse messages.
    if(channelID < 0) {
        throw std::runtime_error(std::string(__FUNCTION__) + "Could not create a channel!\n");
    }
    internalConID = ConnectAttach(0, 0, channelID, _NTO_SIDE_CHANNEL, 0); //Connect to channel.
    if(internalConID < 0) {
        throw std::runtime_error(std::string(__FUNCTION__) + "Could not connect to channel!");
    }
    //Register interrupts by OS.
    struct sigevent interrupt_event;
    SIGEV_PULSE_INIT(&interrupt_event, internalConID, SIGEV_PULSE_PRIO_INHERIT, PULSE_INTR_ON_PORT0, 0);
    interruptID = InterruptAttachEvent(INTR_GPIO_0, &interrupt_event, 0);
    if(interruptID < 0) {
        throw std::runtime_error(std::string(__FUNCTION__) + "Interrupt was not able to be attached!");
    }

    out32((uintptr_t) gpio_bank_0 + GPIO_IRQSTATUS_SET_1, (inputPins));

    // Set irq event types.
    uint32_t currentConfig;

    //	(for rising edge detection)
    currentConfig = in32((uintptr_t) (gpio_bank_0 + GPIO_RISINGDETECT));//Read current config.
    out32((uintptr_t) (gpio_bank_0 + GPIO_RISINGDETECT), (currentConfig|inputPins));//Write new config back.
    // 	(for falling edge detection)
    currentConfig = in32((uintptr_t) (gpio_bank_0 + GPIO_FALLINGDETECT));//Read current config.
    out32((uintptr_t) (gpio_bank_0 + GPIO_FALLINGDETECT), (currentConfig|inputPins));//Write new config back.

    out32((uintptr_t) (gpio_bank_1 + GPIO_OE), 0);
    out32((uintptr_t) (gpio_bank_2 + GPIO_OE), 0);

    this->startReceiving();
}

HAL::~HAL() {
    MsgSendPulse(internalConID, -1, PULSE_STOP_THREAD, 0); //using prio of calling thread.
    receivingThread->join();
    delete receivingThread;

    //	(for rising edge detection)
    uint32_t currentConfig = in32((uintptr_t) (gpio_bank_0 + GPIO_RISINGDETECT));//Read current config.
    out32((uintptr_t) (gpio_bank_0 + GPIO_RISINGDETECT), (currentConfig^inputPins));//Write new config back.
    // 	(for falling edge detection)
    currentConfig = in32((uintptr_t) (gpio_bank_0 + GPIO_FALLINGDETECT));//Read current config.
    out32((uintptr_t) (gpio_bank_0 + GPIO_FALLINGDETECT), (currentConfig^inputPins));//Write new config back.
    out32((uintptr_t) gpio_bank_0 + GPIO_IRQSTATUS_SET_1, (inputPins));

   

    // Detach interrupts.
    int intr_detach_status = InterruptDetach(interruptID);
    if(intr_detach_status != EOK) {
        throw std::runtime_error(std::string(__FUNCTION__) + "Detaching interrupt failed!");
    }

    // Close channel
    int detach_status = ConnectDetach(internalConID);
    if(detach_status != EOK) {
        throw std::runtime_error(std::string(__FUNCTION__) + "Detaching channel failed!");
    }

    int destroy_status = ChannelDestroy(channelID);
    if(destroy_status != EOK) {
        throw std::runtime_error(std::string(__FUNCTION__) + "Destroying channel failed!");
    }
    InterruptDisable();

    motor_stop();
    traffic_red_off();
    traffic_yellow_off();
    traffic_green_off();
    led_start_off();
    led_reset_off();
    led_q1_off();
    led_q2_off();

    if(gpio_bank_0) {
        munmap_device_io(gpio_bank_0, GPIO_MMAP_SIZE);
    }
    if(gpio_bank_1) {
        munmap_device_io(gpio_bank_1, GPIO_MMAP_SIZE);
    }
    if(gpio_bank_2) {
        munmap_device_io(gpio_bank_2, GPIO_MMAP_SIZE);
    }

}


//========================= private functions =========================

void HAL::set_data(uintptr_t gpio_bank, uint32_t bit) {
    uint32_t pin = (1 << bit);
    out32((uintptr_t) (gpio_bank + GPIO_SETDATAOUT), pin);

}

void HAL::clear_data(uintptr_t gpio_bank, uint32_t bit) {
    uint32_t pin = (1 << bit);
    out32((uintptr_t) (gpio_bank + GPIO_CLEARDATAOUT), pin);
}

int HAL::registerToBit(uint32_t inputRegister) {
    if(inputRegister == 0 || (inputRegister & (inputRegister - 1)) != 0) {
        throw std::runtime_error(std::string(__FUNCTION__) +
            ": Cannot convert register to bit offset, value is not a power of 2");
    }
    return __builtin_ctz(inputRegister);  // Count trailing zeros
}

void HAL::receivingRoutine(int channelID) {
    ThreadCtl(_NTO_TCTL_IO, 0);	//Request IO privileges
    _pulse msg;
    receivingRunning = true;
    printf("Message thread started.\n");
    while(receivingRunning) {
        int recvid = MsgReceivePulse(channelID, &msg, sizeof(_pulse), nullptr);
        if(recvid < 0) {
            throw std::runtime_error(std::string(__FUNCTION__) + "MsgReceivePulse failed!");
        }
        if(recvid == 0) {	//pulse received.
            //Stop thread while it blocks.
            if(msg.code == PULSE_STOP_THREAD) {
                printf("Thread kill code received!\n");
                receivingRunning = false;
            }
            if(msg.code == PULSE_INTR_ON_PORT0) {
                handleInterrupt();
            }
            // Do not ignore OS pulses!
        }
    }
    printf("Message thread stops...\n");
}

void HAL::handleInterrupt(void) {
    /**
     * 1. Is the interrupt from my device?
     * 2. Reset the IRQ
     * 3. Send a task to a thread to respond to this interrupt(handle the interrupt)
     */
    uint32_t intrStatusReg = in32(uintptr_t(gpio_bank_0 + GPIO_IRQSTATUS_1));
    out32(uintptr_t(gpio_bank_0 + GPIO_IRQSTATUS_1), 0xffffffff);	//clear all interrupts.
    InterruptUnmask(INTR_GPIO_0, interruptID);				//unmask interrupt.
    int causing_pin = registerToBit(intrStatusReg);
    int pin_status = (in32((uintptr_t) gpio_bank_0 + GPIO_DATAIN) >> causing_pin) & 0x1;
    //if double events come at the same time, the system has to ignore it.
    if(last_causing_pin != causing_pin || last_pin_status != pin_status) {
        last_causing_pin = causing_pin;
        last_pin_status = pin_status;
        #ifdef SHOW_EVENTS
        std::printf("Interrupt on pin %d, status: %d\n", causing_pin, pin_status);
        #endif
        //TODO e-stopp is still trigerred 2x during e-stop pull. 
        //TODO send event to external pulse message (GNS)
        MsgSendPulse(externalConID, 5, causing_pin, pin_status);
    }

}

void HAL::startReceiving() {
    receivingThread = new thread(&HAL::receivingRoutine, this, channelID);

}

//========================= public functions =========================

bool HAL::isGate() {
    uint32_t status_register = in32((uintptr_t) gpio_bank_0 + GPIO_DATAIN);
    std::cout << "Status Register of in32: 0x" << std::hex << status_register << std::endl;
    uint32_t sorting_status_pin = (1 << SORTING_STATUS_BIT);
    bool status = (status_register & sorting_status_pin);
    return !status;
}

//GPIO_1

void HAL::motor_right() {
    clear_data(gpio_bank_1, MOTOR_LEFT_BIT);
    set_data(gpio_bank_1, MOTOR_RIGHT_BIT);

}


void HAL::motor_left() {
    clear_data(gpio_bank_1, MOTOR_RIGHT_BIT);
    set_data(gpio_bank_1, MOTOR_LEFT_BIT);
}


void HAL::motor_slow_on() {
    set_data(gpio_bank_1, MOTOR_SLOW_BIT);
}

void HAL::motor_slow_off() {
    clear_data(gpio_bank_1, MOTOR_SLOW_BIT);
}

void HAL::motor_stop() {
    clear_data(gpio_bank_1, MOTOR_RIGHT_BIT);
    clear_data(gpio_bank_1, MOTOR_LEFT_BIT);

    //set_data(gpio_bank_1, MOTOR_STOP_BIT);
    //clear_data(gpio_bank_1, MOTOR_STOP_BIT);
    motor_slow_off();

}

void HAL::traffic_red_on() {
    set_data(gpio_bank_1, TRAFFIC_RED_BIT);
}

void HAL::traffic_red_off() {
    clear_data(gpio_bank_1, TRAFFIC_RED_BIT);
}

void HAL::traffic_yellow_on() {
    set_data(gpio_bank_1, TRAFFIC_YELLOW_BIT);
}

void HAL::traffic_yellow_off() {
    clear_data(gpio_bank_1, TRAFFIC_YELLOW_BIT);
}

void HAL::traffic_green_on() {
    set_data(gpio_bank_1, TRAFFIC_GREEN_BIT);
}

void HAL::traffic_green_off() {
    clear_data(gpio_bank_1, TRAFFIC_GREEN_BIT);
}

void HAL::sorting_on() {
    set_data(gpio_bank_1, SORTING_BIT);
}

void HAL::sorting_off() {
    clear_data(gpio_bank_1, SORTING_BIT);
}

//GPIO_2

void HAL::led_start_on() {
    set_data(gpio_bank_2, LED_START_BIT);
}

void HAL::led_start_off() {
    clear_data(gpio_bank_2, LED_START_BIT);
}

void HAL::led_reset_on() {
    set_data(gpio_bank_2, LED_RESET_BIT);
}

void HAL::led_reset_off() {
    clear_data(gpio_bank_2, LED_RESET_BIT);
}

void HAL::led_q1_on() {
    set_data(gpio_bank_2, LED_Q1_BIT);
}

void HAL::led_q1_off() {
    clear_data(gpio_bank_2, LED_Q1_BIT);
}

void HAL::led_q2_on() {
    set_data(gpio_bank_2, LED_Q2_BIT);
}

void HAL::led_q2_off() {
    clear_data(gpio_bank_2, LED_Q2_BIT);
}

void HAL::wait(float seconds) {
    usleep(ONE_MILLISECOND * 1000 * seconds);
}

void HAL::test_ins(int externalChannelID) {
    std::cout << "Testing Inputs... Please put Piece on the front laser" << std::endl;
    bool running = true;
    _pulse msg;
    while(running) {
        MsgReceivePulse(externalChannelID, &msg, sizeof(msg), nullptr);
        int code = msg.code;
        int value = msg.value.sival_int;
        
        switch(code) {
            case LASER_FRONT_BIT:
                if(value == 0){
                    std::cout << "Thanks!" << std::endl;
                    this->traffic_green_on();
                    this->motor_right();
                }
                break;
            case LASER_BACK_BIT:
                if(value == 0){
                    this->motor_stop();
                    this->traffic_green_off();
                    this->traffic_red_on();
                } else {
                    running = false;
                }
                break;
            case LASER_METAL_BIT:
                if(value == 0){
                    this->sorting_on();
                    wait(0.1);
                    this->sorting_off();
                }
                break;
            case BUTTON_STOP_BIT:
                if(value == 0){
                    running = false;
                }
                break;
            case ADC_SIDE_AREA_BIT:
                if(value == 0){
                    this->motor_slow_on();
                    this->traffic_yellow_on();
                } else {
                    this->motor_slow_off();
                    this->traffic_yellow_off();
                }
                break;
            default:
                break;
        }
    }
    std::cout << "Testing Input done." << std::endl;
}

void HAL::test_outs() {
    std::cout << "Testing Outputs..." << std::endl;
    this->traffic_red_on();
    wait(1);
    this->traffic_red_off();
    this->traffic_yellow_on();
    wait(1);
    this->traffic_yellow_off();
    this->traffic_green_on();
    wait(1);
    this->traffic_green_off();
    this->motor_slow_on();
    this->motor_right();
    wait(1);
    this->motor_slow_off();
    wait(1);
    this->motor_left();
    this->motor_slow_on();
    wait(1);
    this->motor_slow_off();
    wait(1);
    this->motor_stop();
    this->sorting_on();
    wait(1);
    this->sorting_off();
    this->led_start_on();
    wait(1);
    this->led_reset_on();
    wait(1);
    this->led_q1_on();
    wait(1);
    this->led_q2_on();
    wait(1);
    this->led_start_off();
    this->led_reset_off();
    this->led_q1_off();
    this->led_q2_off();
    std::cout << "Testing Outputs done." << std::endl;
}
