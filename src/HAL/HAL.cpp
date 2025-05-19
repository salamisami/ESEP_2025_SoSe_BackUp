#include "HAL.h"

#define MAILBOX_SIZE 1

//================================================= contructors & destructors =================================================
HAL::HAL(const char* gns_name, int dispatcher_rcvid) {
    actuator_mailbox = new Mailbox<_pulse>(MAILBOX_SIZE);
    adc_mailbox = new Mailbox<_pulse>(MAILBOX_SIZE);

    Thread_COM::setup_thread_communication(gns_name, hal_mailbox, &hal_rcvid);
    interrupt = new Interrupt(dispatcher_rcvid);
    actuator = new Actuator(actuator_mailbox);
    //TODO call actuator isGate()
    //adc = new ADC_Class(dispatcher_rcvid, adc_mailbox);
    //TODO start thread
}

HAL::~HAL() {
    delete adc;
    delete actuator;
    delete interrupt;

    delete actuator_mailbox;
    delete adc_mailbox;
}

//===================================================== private functions =====================================================



//===================================================== public functions =====================================================

int HAL::getHAL_rcvid() {
    return hal_rcvid;
}

void HAL::test_ins() {
    std::cout << "Testing Inputs... Please put Piece on the front laser" << std::endl;
    bool running = true;
    int8_t code = (int8_t) Topic::INTERRUPT;
    while(running) {
        _pulse msg;
        Thread_COM::receive_event(*hal_mailbox, &msg);
        InterruptEnum event = (InterruptEnum) msg.value.sival_int;
        switch(event) {
            case InterruptEnum::LASER_FRONT_BLOCKED:
                std::cout << "Thanks!" << std::endl;
                Thread_COM::send_event(hal_rcvid, code, (int) ActuatorEnum::TRAFFIC_GREEN_ON);
                Thread_COM::send_event(hal_rcvid, code, (int) ActuatorEnum::MOTOR_RIGHT_START);
                break;
            case InterruptEnum::LASER_BACK_BLOCKED:
                Thread_COM::send_event(hal_rcvid, code, (int) ActuatorEnum::MOTOR_STOP);
                Thread_COM::send_event(hal_rcvid, code, (int) ActuatorEnum::TRAFFIC_GREEN_OFF);
                Thread_COM::send_event(hal_rcvid, code, (int) ActuatorEnum::TRAFFIC_RED_ON);
                break;
            case InterruptEnum::LASER_BACK_UNBLOCKED:
                Thread_COM::send_event(hal_rcvid, code, (int) ActuatorEnum::TRAFFIC_RED_OFF);
                Thread_COM::send_event(hal_rcvid, code, (int) ActuatorEnum::TRAFFIC_YELLOW_OFF);
                Thread_COM::send_event(hal_rcvid, code, (int) ActuatorEnum::TRAFFIC_GREEN_OFF);
                //running = false;
                break;
            case InterruptEnum::METAL_DETECTED:
                Thread_COM::send_event(hal_rcvid, code, (int) ActuatorEnum::SORTING_ON);
                WAIT(0.5);
                Thread_COM::send_event(hal_rcvid, code, (int) ActuatorEnum::SORTING_OFF);
                break;
            case InterruptEnum::BUTTON_ESTOP_PRESSED:
                running = false;
                break;
            case InterruptEnum::BUTTON_STOP_PRESSED:
                running = false;
                break;
            case InterruptEnum::ADC_TOP_AREA_BLOCKED:
                Thread_COM::send_event(hal_rcvid, code, (int) ActuatorEnum::MOTOR_SLOW_ON);
                Thread_COM::send_event(hal_rcvid, code, (int) ActuatorEnum::TRAFFIC_YELLOW_ON);
                break;
            case InterruptEnum::ADC_TOP_AREA_UNBLOCKED:
                Thread_COM::send_event(hal_rcvid, code, (int) ActuatorEnum::MOTOR_SLOW_OFF);
                Thread_COM::send_event(hal_rcvid, code, (int) ActuatorEnum::TRAFFIC_YELLOW_OFF);
                break;
            default:
                break;
        }
    }
    std::cout << "Testing Input done." << std::endl;
}