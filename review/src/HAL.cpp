/*#include "HAL.h"

#include <iostream>
#include <stdint.h>
#include <sys/mman.h>
#include <hw/inout.h>
#include <sys/neutrino.h>

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

//GPIO_0 - Sensors pin mapping
#define LASER_FRONT_BIT     2
#define ADC_SIDE_AREA_BIT   3
#define ADC_TOP_AREA_BIT    4
#define LASER_SORTING_BIT   5
#define LASER_METAL_BIT     7
#define SORTING_STATUS_BIT  14
#define LASER_RAMP_BIT      15
#define LASER_BACK_BIT      20
#define BUTTON_START_BIT    22
#define BUTTON_STOP_BIT     23
#define BUTTON_RESET_BIT    26
#define BUTTON_ESTOP_BIT    27

//GPIO_1 - Internal actuator pin mapping
#define MOTOR_RIGHT_BIT     12
#define MOTOR_LEFT_BIT      13
#define MOTOR_SLOW_BIT      14
#define MOTOR_STOP_BIT      15 //useless?
#define TRAFFIC_RED_BIT     16
#define TRAFFIC_YELLOW_BIT  17
#define TRAFFIC_GREEN_BIT   18
#define SORTING_BIT         19

//GPIO_2 - External actuator pin mapping
#define LED_START_BIT       2
#define LED_RESET_BIT       3
#define LED_Q1_BIT          4
#define LED_Q2_BIT          5

#define GNS_NAME            "HAL"


#define THROW(msg) \
    throw std::runtime_error(std::string(__FUNCTION__) + ": " + msg)

#define ONE_MILLISECOND 1000

#define GPIO_MMAP_SIZE   0x1000      //based on GPIO address range (4KB)
using namespace std;

//============================================ contructors & destructors ============================================

HAL::HAL(std::string attach_point)
    : attach_point(attach_point)

    , gpio_bank_0(mmap_device_io(GPIO_MMAP_SIZE, (uint64_t) (GPIO_0)))
    , gpio_bank_1(mmap_device_io(GPIO_MMAP_SIZE, (uint64_t) (GPIO_1)))
    , gpio_bank_2(mmap_device_io(GPIO_MMAP_SIZE, (uint64_t) (GPIO_2)))

    , inputPins(0)
    , last_causing_pin(0)
    , test_mode(false)
    , last_pin_status(0)
    , interruptRunning(false)
    , actuatorRunning(false) {

    setup_GNS_receiver();
    externalConID = setup_GNS_sender();
    setup_interrupts();
    actuatorThread = new std::thread(&HAL::actuatorFunction, this, attach->chid);
    MsgSendPulse(externalConID, SIGEV_PULSE_PRIO_INHERIT, (int) Event::Dispatcher::HAL_READY, 0);
}

HAL::HAL()
    :gpio_bank_0(mmap_device_io(GPIO_MMAP_SIZE, (uint64_t) (GPIO_0)))
    , gpio_bank_1(mmap_device_io(GPIO_MMAP_SIZE, (uint64_t) (GPIO_1)))
    , gpio_bank_2(mmap_device_io(GPIO_MMAP_SIZE, (uint64_t) (GPIO_2)))
    , inputPins(0)
    , last_causing_pin(0)
    , test_mode(true)
    , last_pin_status(0)
    , interruptRunning(false)
    , actuatorRunning(false) {
    externalChannelID = ChannelCreate(0);
    externalConID = ConnectAttach(0, 0, externalChannelID, _NTO_SIDE_CHANNEL, 0);
    setup_interrupts();
}

HAL::~HAL() {
    MsgSendPulse(internalConnectionID, -1, PULSE_STOP_THREAD, 0); //using prio of calling thread.
    interruptThread->join();
    delete interruptThread;
    if(test_mode) {

    } else {
        actuatorRunning = false;
        actuatorThread->join();
        delete actuatorThread;
        clean_GNS_receiver();
        clean_GNS_sender();
    }
    //	(for rising edge detection)
    uint32_t currentConfig = in32((uintptr_t) (gpio_bank_0 + GPIO_RISINGDETECT));//Read current config.
    out32((uintptr_t) (gpio_bank_0 + GPIO_RISINGDETECT), (currentConfig ^ inputPins));//Write new config back.
    // 	(for falling edge detection)
    currentConfig = in32((uintptr_t) (gpio_bank_0 + GPIO_FALLINGDETECT));//Read current config.
    out32((uintptr_t) (gpio_bank_0 + GPIO_FALLINGDETECT), (currentConfig ^ inputPins));//Write new config back.
    out32((uintptr_t) gpio_bank_0 + GPIO_IRQSTATUS_SET_1, (inputPins));

    // Detach interrupts.
    int intr_detach_status = InterruptDetach(interruptID);
    if(intr_detach_status != EOK) {
        THROW("Detaching interrupt failed!");
    }
    clean_internal_pulse_message();
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


//================================================ private functions ================================================

void HAL::setup_interrupts() {
    pinsList.push_back(LASER_FRONT_BIT);
    pinsList.push_back(LASER_SORTING_BIT);
    pinsList.push_back(LASER_METAL_BIT);
    pinsList.push_back(ADC_TOP_AREA_BIT);
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
        THROW("Requested procmgr_status failed!");
    }
    InterruptEnable(); //Enables interrupts.
    setup_internal_pulse_message();
    //Register interrupts by OS.
    struct sigevent interrupt_event;
    SIGEV_PULSE_INIT(&interrupt_event, internalConnectionID, SIGEV_PULSE_PRIO_INHERIT, PULSE_INTR_ON_PORT0, 0);
    interruptID = InterruptAttachEvent(INTR_GPIO_0, &interrupt_event, 0);
    if(interruptID < 0) {
        THROW("Interrupt was not able to be attached!");
    }

    out32((uintptr_t) gpio_bank_0 + GPIO_IRQSTATUS_SET_1, (inputPins));

    // Set irq event types.
    uint32_t currentConfig;

    //	(for rising edge detection)
    currentConfig = in32((uintptr_t) (gpio_bank_0 + GPIO_RISINGDETECT));//Read current config.
    out32((uintptr_t) (gpio_bank_0 + GPIO_RISINGDETECT), (currentConfig | inputPins));//Write new config back.
    // 	(for falling edge detection)
    currentConfig = in32((uintptr_t) (gpio_bank_0 + GPIO_FALLINGDETECT));//Read current config.
    out32((uintptr_t) (gpio_bank_0 + GPIO_FALLINGDETECT), (currentConfig | inputPins));//Write new config back.

    out32((uintptr_t) (gpio_bank_1 + GPIO_OE), 0);
    out32((uintptr_t) (gpio_bank_2 + GPIO_OE), 0);

    interruptThread = new std::thread(&HAL::interruptFunction, this, internalChannelID);
}

void HAL::setup_internal_pulse_message() {
    internalChannelID = ChannelCreate(0);//Create channel to receive interrupt pulse messages.
    if(internalChannelID < 0) {
        THROW("Could not create a channel!");
    }
    internalConnectionID = ConnectAttach(0, 0, internalChannelID, _NTO_SIDE_CHANNEL, 0); //Connect to channel.
    if(internalConnectionID < 0) {
        THROW("Could not connect to channel!");
    }
}

void HAL::clean_internal_pulse_message() {
    // Close channel
    int detach_status = ConnectDetach(internalConnectionID);
    if(detach_status != EOK) {
        THROW("Detaching channel failed!");
    }
    int destroy_status = ChannelDestroy(internalChannelID);
    if(destroy_status != EOK) {
        THROW("Destroying channel failed!");
    }
}

int HAL::setup_GNS_sender() {
    int connectionID = name_open(attach_point.c_str(), NAME_FLAG_ATTACH_GLOBAL);
    if(connectionID < 0) {
        THROW("GNS-Sender failed to create!");
    }
    return connectionID;
}
void HAL::clean_GNS_sender() {
    int detach_status = name_close(externalConID);
    if(detach_status < 0) {
        THROW("GNS-Sender failed to close!");
    }
}


void HAL::setup_GNS_receiver() {
    this->attach = name_attach(NULL, GNS_NAME, NAME_FLAG_ATTACH_GLOBAL);
    if(this->attach == NULL) {
        THROW("GNS-Receiver failed to create");
    }
}

void HAL::clean_GNS_receiver() {
    int status = name_detach(attach, 0);
    if(status < 0) {
        THROW("GNS-Receiver failed to clean");
    }
}


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
        THROW("Cannot convert register to bit offset, value is not a power of 2");
    }
    return __builtin_ctz(inputRegister);  // Count trailing zeros
}

void HAL::interruptFunction(int channelID) {
    ThreadCtl(_NTO_TCTL_IO, 0);	//Request IO privileges
    _pulse msg;
    interruptRunning = true;
    printf("Message thread started.\n");
    while(interruptRunning) {
        int recvid = MsgReceivePulse(channelID, &msg, sizeof(_pulse), nullptr);
        if(recvid < 0) {
            THROW("MsgReceivePulse failed!");
        }
        if(recvid == 0) {	//pulse received.
            //Stop thread while it blocks.
            if(msg.code == PULSE_STOP_THREAD) {
                printf("Thread kill code received!\n");
                interruptRunning = false;
            }
            if(msg.code == PULSE_INTR_ON_PORT0) {
                isr();
            }
            // Do not ignore OS pulses!
        }
    }
    printf("Message thread stops...\n");
}

void HAL::isr(void) {
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

        //TODO e-stopp is still trigerred 2x during e-stop pull. 
        sendEvent(causing_pin, pin_status);
    }

}


void HAL::sendEvent(int causing_pin, int pin_status) {
    Event::Interrupt event;
    //Event is the namespace, Interrupt is the enum class
    using namespace Event;
    #ifdef SHOW_EVENTS
    std::printf("Interrupt on pin %d, status: %d\n", causing_pin, pin_status);
    #endif
    switch(causing_pin) {
        // 1 : 0
        case LASER_FRONT_BIT:
            event = pin_status ? Interrupt::LASER_FRONT_UNBLOCKED : Interrupt::LASER_FRONT_BLOCKED;
            break;
        case LASER_BACK_BIT:
            event = pin_status ? Interrupt::LASER_BACK_UNBLOCKED : Interrupt::LASER_BACK_BLOCKED;
            break;
        case BUTTON_START_BIT:
            event = pin_status ? Interrupt::BUTTON_START_PRESSED : Interrupt::BUTTON_START_RELEASED;
            break;
        case BUTTON_STOP_BIT:
            event = pin_status ? Interrupt::BUTTON_STOP_PRESSED : Interrupt::BUTTON_STOP_RELEASED;
            break;
        case BUTTON_RESET_BIT:
            event = pin_status ? Interrupt::BUTTON_RESET_PRESSED : Interrupt::BUTTON_RESET_RELEASED;
            break;
        case BUTTON_ESTOP_BIT:
            event = pin_status ? Interrupt::BUTTON_ESTOP_PRESSED : Interrupt::BUTTON_ESTOP_RELEASED;
            break;
        case LASER_SORTING_BIT:
            event = pin_status ? Interrupt::LASER_SORTING_GATE_UNBLOCKED : Interrupt::LASER_SORTING_GATE_BLOCKED;
            break;
        case LASER_RAMP_BIT:
            event = pin_status ? Interrupt::LASER_RAMP_UNBLOCKED : Interrupt::LASER_RAMP_BLOCKED;
            break;
        case LASER_METAL_BIT:
            event = pin_status ? Interrupt::METAL_DETECTED : Interrupt::METAL_NOT_DETECTED;
            break;
        case ADC_SIDE_AREA_BIT:
            event = pin_status ? Interrupt::ADC_SIDE_AREA_UNBLOCKED : Interrupt::ADC_SIDE_AREA_BLOCKED;
            break;
        case ADC_TOP_AREA_BIT:
            event = pin_status ? Interrupt::ADC_TOP_AREA_BLOCKED : Interrupt::ADC_TOP_AREA_UNBLOCKED;
            break;
        default:
            break;

    }
    MsgSendPulse(externalConID, SIGEV_PULSE_PRIO_INHERIT, INTERRUPT_PULSE, (int) event);
}

void HAL::actuatorFunction(int chid) {
    actuatorRunning = true;
    _pulse pulse;
    while(actuatorRunning) {
        int rcvid = MsgReceive(chid, &pulse, sizeof(_pulse), NULL);
        if(rcvid < 0) {
            THROW("MsgReceive Failed.");
        }
        Event::Actuator value = (Event::Actuator) pulse.value.sival_int;
        using namespace Event;
        switch(value) {
            case Actuator::MOTOR_RIGHT_START:
                motor_right();
                break;
            case Actuator::MOTOR_LEFT_START:
                motor_left();
                break;
            case Actuator::MOTOR_STOP:
                motor_stop();
                break;
            case Actuator::SORTING_ON:
                sorting_on();
                break;
            case Actuator::SORTING_OFF:
                sorting_off();
                break;
            case Actuator::TRAFFIC_GREEN_ON:
                traffic_green_on();
                break;
            case Actuator::TRAFFIC_GREEN_OFF:
                traffic_green_off();
                break;
            case Actuator::TRAFFIC_GREEN_ON_SLOW:
                break;
            case Actuator::TRAFFIC_GREEN_ON_FAST:
                break;
            default:
                THROW("Invalid Actuator Event!");
                break;
        }
    }
}


//================================================ public functions ================================================

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



void HAL::test_ins() {
    int temporaryChID = ChannelCreate(0);
    if(temporaryChID < 0) {
        THROW("ChannelCreate failed.");
    }
    int temporaryConID = ConnectAttach(0, 0, temporaryChID, _NTO_SIDE_CHANNEL, 0);
    if(temporaryConID < 0) {
        THROW("ConenctAttach failed.");
    }
    int savedConID = externalConID;

    externalConID = temporaryConID;

    std::cout << "Testing Inputs... Please put Piece on the front laser" << std::endl;
    bool running = true;
    _pulse msg;
    while(running) {
        MsgReceivePulse(temporaryChID, &msg, sizeof(msg), nullptr);
        int code = msg.code;
        if(code != INTERRUPT_PULSE) {
            return;
        }
        Event::Interrupt event = (Event::Interrupt) msg.value.sival_int;
        using namespace Event;
        switch(event) {
            case Interrupt::LASER_FRONT_BLOCKED:
                std::cout << "Thanks!" << std::endl;
                this->traffic_green_on();
                this->motor_right();
                break;
            case Interrupt::LASER_BACK_BLOCKED:
                this->motor_stop();
                this->traffic_green_off();
                this->traffic_red_on();
                break;
            case Interrupt::LASER_BACK_UNBLOCKED:
                running = false;
                break;
            case Interrupt::METAL_DETECTED:
                this->sorting_on();
                wait(0.5);
                this->sorting_off();
                break;
            case Interrupt::BUTTON_STOP_PRESSED:
                running = false;
                break;
            case Interrupt::ADC_SIDE_AREA_BLOCKED:
                this->motor_slow_on();
                this->traffic_yellow_on();
                break;
            case Interrupt::ADC_SIDE_AREA_UNBLOCKED:
                this->motor_slow_off();
                this->traffic_yellow_off();
                break;
            default:
                break;
        }
    }
    std::cout << "Testing Input done." << std::endl;
    externalConID = savedConID;
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
