#include "Actuator.h"

// GPIO Registers page 4877 
//outs
#define GPIO_SETDATAOUT     0x194
#define GPIO_CLEARDATAOUT   0x190
#define GPIO_OE             0x134

//ins
#define GPIO_DATAIN 0x138

// Memory maps
#define GPIO_0 0x44E07000  //for sorting type checking
#define GPIO_1 0x4804C000  //system outputs,    page 182
#define GPIO_2 0x481AC000  //human outputs,      page 183
#define GPIO_3 0x481AE000  //unknown,           page 183

//GPIO_0
#define SORTING_STATUS_BIT  14


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

#define ONE_MILLISECOND 1000

#define GPIO_MMAP_SIZE   0x1000      //based on GPIO address range (4KB)
using namespace std;

//================================================= contructors & destructors =================================================
Actuator::Actuator(Mailbox<_pulse>* mailbox)
    : mailbox(mailbox)
    , gpio_bank_1(mmap_device_io(GPIO_MMAP_SIZE, (uint64_t) (GPIO_1)))
    , gpio_bank_2(mmap_device_io(GPIO_MMAP_SIZE, (uint64_t) (GPIO_2)))
    , actuatorRunning(false)
    , is_local_estop(false) {
    out32((uintptr_t) (gpio_bank_1 + GPIO_OE), 0);
    out32((uintptr_t) (gpio_bank_2 + GPIO_OE), 0);
    global_shutdown();
    local_estop_deactivate();
    prohibit_operate = false;
    is_local_estop = false;
    is_local_estop = false;
    actuatorThread = std::thread(&Actuator::threadFunction, this);
}

Actuator::~Actuator() {
    actuatorRunning = false;
    actuatorThread.join();
    global_shutdown();


    if(gpio_bank_1) {
        munmap_device_io(gpio_bank_1, GPIO_MMAP_SIZE);
    }
    if(gpio_bank_2) {
        munmap_device_io(gpio_bank_2, GPIO_MMAP_SIZE);
    }
}

//===================================================== private functions =====================================================


void Actuator::set_data(uintptr_t gpio_bank, uint32_t bit) {
    mtx.lock();
    uint32_t pin = (1 << bit);
    out32((uintptr_t) (gpio_bank + GPIO_SETDATAOUT), pin);
    mtx.unlock();
}

void Actuator::clear_data(uintptr_t gpio_bank, uint32_t bit) {
    mtx.lock();
    uint32_t pin = (1 << bit);
    out32((uintptr_t) (gpio_bank + GPIO_CLEARDATAOUT), pin);
    mtx.unlock();
}

void Actuator::handleActuatorEvent(int event_value) {
    switch((ActuatorEnum) event_value) {
        case ActuatorEnum::MOTOR_SLOW_ON:
            motor_slow_on();
            break;
        case ActuatorEnum::MOTOR_SLOW_OFF:
            motor_slow_off();
            break;
        case ActuatorEnum::MOTOR_RIGHT_START:
            motor_right();
            break;
        case ActuatorEnum::MOTOR_LEFT_START:
            motor_left();
            break;
        case ActuatorEnum::MOTOR_STOP:
            motor_stop();
            break;
        case ActuatorEnum::SORTING_ON:
            sorting_on();
            break;
        case ActuatorEnum::SORTING_OFF:
            sorting_off();
            break;
        case ActuatorEnum::TRAFFIC_RED_ON:
            traffic_red_on();
            break;
        case ActuatorEnum::TRAFFIC_RED_OFF:
            traffic_red_off();
            break;
        case ActuatorEnum::TRAFFIC_YELLOW_ON:
            traffic_yellow_on();
            break;
        case ActuatorEnum::TRAFFIC_YELLOW_OFF:
            traffic_yellow_off();
            break;
        case ActuatorEnum::TRAFFIC_GREEN_ON:
            traffic_green_on();
            break;
        case ActuatorEnum::TRAFFIC_GREEN_OFF:
            traffic_green_off();
            break;
        case ActuatorEnum::LED_START_ON:
            led_start_on();
            break;
        case ActuatorEnum::LED_START_OFF:
            led_start_off();
            break;
        case ActuatorEnum::LED_RESET_ON:
            led_reset_on();
            break;
        case ActuatorEnum::LED_RESET_OFF:
            led_reset_off();
            break;
        case ActuatorEnum::LED_Q1_ON:
            led_q1_on();
            break;
        case ActuatorEnum::LED_Q1_OFF:
            led_q1_off();
            break;
        case ActuatorEnum::LED_Q2_ON:
            led_q2_on();
            break;
        case ActuatorEnum::LED_Q2_OFF:
            led_q2_off();
            break;
        case ActuatorEnum::TRAFFIC_RED_ON_FAST:
            traffic_red_fast();
            break;
        case ActuatorEnum::TRAFFIC_RED_ON_SLOW:
            traffic_red_slow();
            break;
        case ActuatorEnum::TRAFFIC_YELLOW_ON_FAST:
            traffic_yellow_fast();
            break;
        case ActuatorEnum::TRAFFIC_YELLOW_ON_SLOW:
            traffic_yellow_slow();
            break;
        case ActuatorEnum::TRAFFIC_GREEN_ON_FAST:
            traffic_green_fast();
            break;
        case ActuatorEnum::TRAFFIC_GREEN_ON_SLOW:
            traffic_green_slow();
            break;
        default:
            //THROW("Invalid Actuator Event!");
            break;
    }
}


void Actuator::traffic_red_fast() {

}
void Actuator::traffic_red_slow() {
}
void Actuator::traffic_yellow_fast() {
}
void Actuator::traffic_yellow_slow() {
}
void Actuator::traffic_green_fast() {
}
void Actuator::traffic_green_slow() {
}




// void Actuator::handleEStop(int event_value) {
//     if((InterruptEnum) event_value == InterruptEnum::BUTTON_ESTOP_PRESSED) {
//         stop_moving_parts();
//     }
// }


void Actuator::threadFunction() {
    actuatorRunning = true;
    while(actuatorRunning) {
        _pulse pulse = mailbox->take();
        Topic event_code = (Topic) pulse.code;
        int event_value = pulse.value.sival_int;
        switch(event_code) {
            // case Topic::INTERRUPT:
            //     handleEStop(event_value);
            //     break;
            case Topic::ACTUATOR:
                handleActuatorEvent(event_value);
                break;
            case Topic::STOP_THREAD:
                actuatorRunning = false;
                break;
            case Topic::COM:
                if(event_value == (int) COM_Enum::BUTTON_ESTOP_PRESSED) {
                    is_neighbor_estop = true;
                } else if(event_value == (int) COM_Enum::BUTTON_ESTOP_RELEASED) {
                    is_neighbor_estop = false;
                }
                check_estop();
                break;
            default:
                break;
        }
    }
}

//GPIO_0
bool Actuator::isGate() {
    uintptr_t gpio_bank_0 = mmap_device_io(GPIO_MMAP_SIZE, (uint64_t) (GPIO_0));

    uint32_t status_register = in32((uintptr_t) gpio_bank_0 + GPIO_DATAIN);
    //std::cout << "Status Register of in32: 0x" << std::hex << status_register << std::endl;
    uint32_t sorting_status_pin = (1 << SORTING_STATUS_BIT);
    bool status = (status_register & sorting_status_pin);
    return !status;
}

//GPIO_1
void Actuator::motor_right() {
    if(prohibit_operate) {
        return;
    }
    clear_data(gpio_bank_1, MOTOR_LEFT_BIT);
    set_data(gpio_bank_1, MOTOR_RIGHT_BIT);
}

void Actuator::motor_left() {
    if(prohibit_operate) {
        return;
    }
    clear_data(gpio_bank_1, MOTOR_RIGHT_BIT);
    set_data(gpio_bank_1, MOTOR_LEFT_BIT);
}

void Actuator::motor_slow_on() {
    set_data(gpio_bank_1, MOTOR_SLOW_BIT);
}

void Actuator::motor_slow_off() {
    clear_data(gpio_bank_1, MOTOR_SLOW_BIT);
}

void Actuator::motor_stop() {
    clear_data(gpio_bank_1, MOTOR_RIGHT_BIT);
    clear_data(gpio_bank_1, MOTOR_LEFT_BIT);

    //set_data(gpio_bank_1, MOTOR_STOP_BIT);
    //clear_data(gpio_bank_1, MOTOR_STOP_BIT);
    motor_slow_off();

}

void Actuator::traffic_red_on() {
    set_data(gpio_bank_1, TRAFFIC_RED_BIT);
}

void Actuator::traffic_red_off() {
    clear_data(gpio_bank_1, TRAFFIC_RED_BIT);
}

void Actuator::traffic_yellow_on() {
    set_data(gpio_bank_1, TRAFFIC_YELLOW_BIT);
}

void Actuator::traffic_yellow_off() {
    clear_data(gpio_bank_1, TRAFFIC_YELLOW_BIT);
}

void Actuator::traffic_green_on() {
    set_data(gpio_bank_1, TRAFFIC_GREEN_BIT);
}

void Actuator::traffic_green_off() {
    clear_data(gpio_bank_1, TRAFFIC_GREEN_BIT);
}

void Actuator::sorting_on() {
    if(prohibit_operate) {
        return;
    }
    set_data(gpio_bank_1, SORTING_BIT);
}

void Actuator::sorting_off() {
    clear_data(gpio_bank_1, SORTING_BIT);
}

//GPIO_2

void Actuator::led_start_on() {
    set_data(gpio_bank_2, LED_START_BIT);
}

void Actuator::led_start_off() {
    clear_data(gpio_bank_2, LED_START_BIT);
}

void Actuator::led_reset_on() {
    set_data(gpio_bank_2, LED_RESET_BIT);
}

void Actuator::led_reset_off() {
    clear_data(gpio_bank_2, LED_RESET_BIT);
}

void Actuator::led_q1_on() {
    set_data(gpio_bank_2, LED_Q1_BIT);
}

void Actuator::led_q1_off() {
    clear_data(gpio_bank_2, LED_Q1_BIT);
}

void Actuator::led_q2_on() {
    set_data(gpio_bank_2, LED_Q2_BIT);
}

void Actuator::led_q2_off() {
    clear_data(gpio_bank_2, LED_Q2_BIT);
}



//===================================================== public functions =====================================================
void Actuator::global_shutdown() {
    stop_moving_parts();
    traffic_red_off();
    traffic_yellow_off();
    traffic_green_off();
    led_start_off();
    led_reset_off();
    led_q1_off();
    led_q2_off();
}

void Actuator::stop_moving_parts() {
    DEBUG("Stoping moving parts...");
    sorting_off();
    motor_stop();
}


void Actuator::check_estop() {
    prohibit_operate = (is_local_estop || is_neighbor_estop);
    if(prohibit_operate) {
        stop_moving_parts();
    }
}

void Actuator::local_estop_activate() {
    is_local_estop = true;
    check_estop();
}

void Actuator::local_estop_deactivate() {
    is_local_estop = false;
    check_estop();
}


void Actuator::test_outs() {
    std::cout << "Testing Outputs..." << std::endl;
    this->traffic_red_on();
    WAIT(1000);
    this->traffic_red_off();
    this->traffic_yellow_on();
    WAIT(1000);
    this->traffic_yellow_off();
    this->traffic_green_on();
    WAIT(1000);
    this->traffic_green_off();
    this->motor_slow_on();
    this->motor_right();
    WAIT(1000);
    this->motor_slow_off();
    WAIT(1000);
    this->motor_left();
    this->motor_slow_on();
    WAIT(1000);
    this->motor_slow_off();
    WAIT(1000);
    this->motor_stop();
    this->sorting_on();
    WAIT(1000);
    this->sorting_off();
    this->led_start_on();
    WAIT(1000);
    this->led_reset_on();
    WAIT(1000);
    this->led_q1_on();
    WAIT(1000);
    this->led_q2_on();
    WAIT(1000);
    this->led_start_off();
    this->led_reset_off();
    this->led_q1_off();
    this->led_q2_off();
    std::cout << "Testing Outputs done." << std::endl;
}
