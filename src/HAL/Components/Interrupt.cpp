#include "Interrupt.h"

// GPIO Registers page 4877 
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

#define PULSE_STOP_THREAD _PULSE_CODE_MINAVAIL + 1
#define PULSE_INTR_ON_PORT0 _PULSE_CODE_MINAVAIL + 2

#define ONE_MILLISECOND 1000
//#define SHOW_EVENTS
#define GPIO_MMAP_SIZE   0x1000      //based on GPIO address range (4KB)
using namespace std;

//================================================= contructors & destructors =================================================

Interrupt::Interrupt(I_Sender* sender, Actuator* actuator)
    : gpio_bank_0(mmap_device_io(GPIO_MMAP_SIZE, (uint64_t) (GPIO_0)))
    , sender(sender)
    , actuator(actuator)
    , inputPins(0)
    , last_causing_pin(0)
    , test_mode(false)
    , last_pin_status(0)
    , interruptRunning(false) {
    setup_interrupts();
}

// Interrupt::Interrupt()
//     :gpio_bank_0(mmap_device_io(GPIO_MMAP_SIZE, (uint64_t) (GPIO_0)))
//     , inputPins(0)
//     , last_causing_pin(0)
//     , test_mode(true)
//     , last_pin_status(0)
//     , interruptRunning(false) {
//     externalChannelID = ChannelCreate(0);
//     externalConID = ConnectAttach(0, 0, externalChannelID, _NTO_SIDE_CHANNEL, 0);
//     setup_interrupts();
// }

Interrupt::~Interrupt() {
    MsgSendPulse(internalConnectionID, -1, PULSE_STOP_THREAD, 0); //using prio of calling thread.
    interruptThread.join();
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
    if(gpio_bank_0) {
        munmap_device_io(gpio_bank_0, GPIO_MMAP_SIZE);
    }
}

//===================================================== private functions =====================================================

void Interrupt::setup_interrupts() {
    pinsList.push_back(LASER_FRONT_BIT);
    pinsList.push_back(LASER_SORTING_BIT);
    pinsList.push_back(LASER_METAL_BIT);
    pinsList.push_back(ADC_TOP_AREA_BIT);
    //pinsList.push_back(SORTING_STATUS_BIT);
    pinsList.push_back(LASER_RAMP_BIT);
    pinsList.push_back(LASER_BACK_BIT);
    pinsList.push_back(BUTTON_START_BIT);
    pinsList.push_back(BUTTON_STOP_BIT);
    pinsList.push_back(BUTTON_RESET_BIT);
    pinsList.push_back(BUTTON_ESTOP_BIT);
    //pinsList.push_back(ADC_SIDE_AREA_BIT);

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


    interruptThread = std::thread(&Interrupt::threadFunction, this);
}

void Interrupt::setup_internal_pulse_message() {
    internalChannelID = ChannelCreate(0);//Create channel to receive interrupt pulse messages.
    if(internalChannelID < 0) {
        THROW("Could not create a channel!");
    }
    internalConnectionID = ConnectAttach(0, 0, internalChannelID, _NTO_SIDE_CHANNEL, 0); //Connect to channel.
    if(internalConnectionID < 0) {
        THROW("Could not connect to channel!");
    }
}

void Interrupt::clean_internal_pulse_message() {
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



int Interrupt::registerToBit(uint32_t inputRegister) {
    if(inputRegister == 0 || (inputRegister & (inputRegister - 1)) != 0) {
        DEBUG("Cannot convert register to bit offset, value is not a power of 2");
        return -1;
    }
    return __builtin_ctz(inputRegister);  // Count trailing zeros
}

void Interrupt::threadFunction() {
    ThreadCtl(_NTO_TCTL_IO, 0);	//Request IO privileges
    _pulse msg;
    interruptRunning = true;
    printf("Message thread started.\n");
    while(interruptRunning) {
        int recvid = MsgReceivePulse(internalChannelID, &msg, sizeof(_pulse), nullptr);
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

void Interrupt::isr(void) {
    /**
     * 1. Is the interrupt from my device?
     * 2. Reset the IRQ
     * 3. Send a task to a thread to respond to this interrupt(handle the interrupt)
     */
    uint32_t intrStatusReg = in32(uintptr_t(gpio_bank_0 + GPIO_IRQSTATUS_1));
    out32(uintptr_t(gpio_bank_0 + GPIO_IRQSTATUS_1), 0xffffffff);	//clear all interrupts.
    InterruptUnmask(INTR_GPIO_0, interruptID);				//unmask interrupt.
    int causing_pin = registerToBit(intrStatusReg);
    if(causing_pin < 0){
        return;
    }
    int pin_status = (in32((uintptr_t) gpio_bank_0 + GPIO_DATAIN) >> causing_pin) & 0x1;
    //if double events come at the same time, the system has to ignore it.
    if(last_causing_pin != causing_pin || last_pin_status != pin_status) {
        last_causing_pin = causing_pin;
        last_pin_status = pin_status;
        sendEvent(causing_pin, pin_status);
    }
}

bool Interrupt::button_estop_pressed(){
    //gpio_bank_0 = mmap_device_io(GPIO_MMAP_SIZE, (uint64_t) (GPIO_0));
    uint32_t status_register = in32((uintptr_t) gpio_bank_0 + GPIO_DATAIN);
    //std::cout << "Status Register of in32: 0x" << std::hex << status_register << std::endl;
    uint32_t status_pin = (1 << BUTTON_ESTOP_BIT);
    bool status = (status_register & status_pin);
    return !status;
}

bool Interrupt::is_switch(){
    uint32_t status_register = in32((uintptr_t) gpio_bank_0 + GPIO_DATAIN);
    //std::cout << "Status Register of in32: 0x" << std::hex << status_register << std::endl;
    uint32_t status_pin = (1 << SORTING_STATUS_BIT);
    bool status = (status_register & status_pin);
    return !status;
}

void Interrupt::sendEvent(int causing_pin, int pin_status) {
    InterruptEnum event;
    //Event is the namespace, Interrupt is the enum class
    #ifdef SHOW_EVENTS
    std::printf("Interrupt on pin %d, status: %d\n", causing_pin, pin_status);
    #endif
    switch(causing_pin) {
        // 1 : 0
        case LASER_FRONT_BIT:
            event = pin_status ? InterruptEnum::LASER_FRONT_UNBLOCKED : InterruptEnum::LASER_FRONT_BLOCKED;
            break;
        case LASER_BACK_BIT:
            event = pin_status ? InterruptEnum::LASER_BACK_UNBLOCKED : InterruptEnum::LASER_BACK_BLOCKED;
            break;
        case BUTTON_START_BIT:
            event = pin_status ? InterruptEnum::BUTTON_START_PRESSED : InterruptEnum::BUTTON_START_RELEASED;
            break;
        case BUTTON_STOP_BIT:
            event = pin_status ? InterruptEnum::BUTTON_STOP_RELEASED : InterruptEnum::BUTTON_STOP_PRESSED;
            break;
        case BUTTON_RESET_BIT:
            event = pin_status ? InterruptEnum::BUTTON_RESET_PRESSED : InterruptEnum::BUTTON_RESET_RELEASED;
            break;
        case BUTTON_ESTOP_BIT:
            event = pin_status ? InterruptEnum::BUTTON_ESTOP_RELEASED : InterruptEnum::BUTTON_ESTOP_PRESSED;
            if(event == InterruptEnum::BUTTON_ESTOP_PRESSED){
                actuator->local_estop_activate();
            } else {
                actuator->local_estop_deactivate();
            }
            sender->send_event((int8_t) Topic::INTERRUPT, (int) event, (int) EventPriority::FIRST_PRIO);
            return;
            //break;
        case LASER_SORTING_BIT:
            event = pin_status ? InterruptEnum::LASER_SORTING_GATE_UNBLOCKED : InterruptEnum::LASER_SORTING_GATE_BLOCKED;
            break;
        case LASER_RAMP_BIT:
            event = pin_status ? InterruptEnum::LASER_RAMP_UNBLOCKED : InterruptEnum::LASER_RAMP_BLOCKED;
            break;
        case LASER_METAL_BIT:
            event = pin_status ? InterruptEnum::METAL_DETECTED : InterruptEnum::METAL_NOT_DETECTED;
            break;
        // case ADC_SIDE_AREA_BIT:
        //     event = pin_status ? InterruptEnum::ADC_SIDE_AREA_UNBLOCKED : InterruptEnum::ADC_SIDE_AREA_BLOCKED;
        //     break;
        case ADC_TOP_AREA_BIT:
            event = pin_status ? InterruptEnum::ADC_TOP_AREA_BLOCKED : InterruptEnum::ADC_TOP_AREA_UNBLOCKED;
            break;
        default:
            break;
    }
    sender->send_event((int8_t) Topic::INTERRUPT, (int) event);
    //MsgSendPulse(sender->getcoid(),-1,(int8_t) Topic::INTERRUPT, (int) event);
    //std::cout << "send event to: " << (int) sender->getcoid() << std::endl;
}




//===================================================== public functions =====================================================
