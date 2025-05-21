#include "HAL.h"

#define MAILBOX_SIZE 1

//================================================= contructors & destructors =================================================
HAL::HAL(const char* gns_name, int dispatcher_rcvid) {
    hal_connection = name_attach_t();
    actuator_mailbox = new Mailbox<_pulse>(MAILBOX_SIZE);
    adc_mailbox = new Mailbox<_pulse>(MAILBOX_SIZE);
    DEBUG("Mailboxes are created");

    Thread_COM::setup_thread_communication(gns_name, &hal_connection, &hal_rcvid);
    DEBUG("setup_thread_communication success");
    if(dispatcher_rcvid == -1){
        Thread_COM::setup_thread_communication("DispatcherMock",&dispatcher_mock_connection,&dispatcher_mock_rcvid);
        dispatcher_rcvid = dispatcher_mock_rcvid;
    }
    interrupt = new Interrupt(dispatcher_rcvid);
    actuator = new Actuator(actuator_mailbox);
    //TODO call actuator isGate()
    //adc = new ADC_Class(dispatcher_rcvid, adc_mailbox);
    halThread = std::thread(&HAL::threadFunction, this);
}

HAL::~HAL() {
    Thread_COM::send_event(hal_rcvid, (int8_t) Topic::STOP_THREAD, 0, -1);
    halThread.join();
    //delete adc;
    delete actuator;
    delete interrupt;

    delete adc_mailbox;
    delete actuator_mailbox;
}

//===================================================== private functions =====================================================

void HAL::threadFunction() {
    hal_running = true;
    while(hal_running) {
        _pulse event;
        Thread_COM::receive_event(hal_connection, &event);
        Topic event_code = (Topic) event.code;
        switch(event_code) {
            case Topic::ACTUATOR:
                actuator_mailbox->put(event);
                break;
            case Topic::ADC:
                adc_mailbox->put(event);
                break;
            case Topic::STOP_THREAD:
                actuator_mailbox->put(event);
                hal_running = false;
                break;
            default:
                break;
        }
    }
}

//===================================================== public functions =====================================================

int HAL::getHAL_rcvid() {
    return hal_rcvid;
}

void HAL::test_ins() {
    std::cout << "Testing Inputs... Please put Piece on the front laser" << std::endl;
    bool running = true;
    int8_t actuatorCode = (int8_t) Topic::ACTUATOR;
    while(running) {
        _pulse msg;
        Thread_COM::receive_event(dispatcher_mock_connection, &msg);
        InterruptEnum event = (InterruptEnum) msg.value.sival_int;
        switch(event) {
            case InterruptEnum::LASER_FRONT_BLOCKED:
                std::cout << "Thanks!" << std::endl;
                Thread_COM::send_event(hal_rcvid, actuatorCode, (int) ActuatorEnum::TRAFFIC_GREEN_ON);
                Thread_COM::send_event(hal_rcvid, actuatorCode, (int) ActuatorEnum::MOTOR_RIGHT_START);
                break;
            case InterruptEnum::LASER_BACK_BLOCKED:
                Thread_COM::send_event(hal_rcvid, actuatorCode, (int) ActuatorEnum::MOTOR_STOP);
                Thread_COM::send_event(hal_rcvid, actuatorCode, (int) ActuatorEnum::TRAFFIC_GREEN_OFF);
                Thread_COM::send_event(hal_rcvid, actuatorCode, (int) ActuatorEnum::TRAFFIC_RED_ON);
                break;
            case InterruptEnum::LASER_BACK_UNBLOCKED:
                Thread_COM::send_event(hal_rcvid, actuatorCode, (int) ActuatorEnum::TRAFFIC_RED_OFF);
                Thread_COM::send_event(hal_rcvid, actuatorCode, (int) ActuatorEnum::TRAFFIC_YELLOW_OFF);
                Thread_COM::send_event(hal_rcvid, actuatorCode, (int) ActuatorEnum::TRAFFIC_GREEN_OFF);
                //running = false;
                break;
            case InterruptEnum::METAL_DETECTED:
                Thread_COM::send_event(hal_rcvid, actuatorCode, (int) ActuatorEnum::SORTING_ON);
                WAIT(500);
                Thread_COM::send_event(hal_rcvid, actuatorCode, (int) ActuatorEnum::SORTING_OFF);
                break;
            case InterruptEnum::BUTTON_ESTOP_PRESSED:
                running = false;
                break;
            case InterruptEnum::BUTTON_STOP_PRESSED:
                running = false;
                break;
            case InterruptEnum::ADC_TOP_AREA_BLOCKED:
                Thread_COM::send_event(hal_rcvid, actuatorCode, (int) ActuatorEnum::MOTOR_SLOW_ON);
                Thread_COM::send_event(hal_rcvid, actuatorCode, (int) ActuatorEnum::TRAFFIC_YELLOW_ON);
                break;
            case InterruptEnum::ADC_TOP_AREA_UNBLOCKED:
                Thread_COM::send_event(hal_rcvid, actuatorCode, (int) ActuatorEnum::MOTOR_SLOW_OFF);
                Thread_COM::send_event(hal_rcvid, actuatorCode, (int) ActuatorEnum::TRAFFIC_YELLOW_OFF);
                break;
            default:
                break;
        }
    }
    std::cout << "Testing Input done." << std::endl;
}