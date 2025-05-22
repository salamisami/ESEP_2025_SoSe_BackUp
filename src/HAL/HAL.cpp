#include "HAL.h"

#define MAILBOX_SIZE 1

//================================================= contructors & destructors =================================================
HAL::HAL(const char* local_gns_name, const char* target_gns_name) {
    local_receiver = new Thread_COM::Receiver(local_gns_name);
    local_sender = new Thread_COM::Sender(target_gns_name);
    mock_dispatcher_sender = new PulseMsg::Sender(local_receiver->getchid());
    init();
}

HAL::HAL() {
    local_receiver = new PulseMsg::Receiver();
    mock_dispatcher_receiver = new PulseMsg::Receiver();
    local_sender = new PulseMsg::Sender(mock_dispatcher_receiver->getchid());
    mock_dispatcher_sender = new PulseMsg::Sender(local_receiver->getchid());
    init();
}

HAL::~HAL() {
    mock_dispatcher_sender->send_event((int8_t) Topic::STOP_THREAD, 0);
    halThread.join();
    //delete adc;
    delete actuator;
    delete interrupt;

    delete adc_mailbox;
    delete actuator_mailbox;
    delete local_sender;
    delete local_receiver;
}

//===================================================== private functions =====================================================
void HAL::init() {
    actuator_mailbox = new Mailbox<_pulse>(MAILBOX_SIZE);
    adc_mailbox = new Mailbox<_pulse>(MAILBOX_SIZE);
    DEBUG("Mailboxes are created");

    interrupt = new Interrupt(local_sender);
    actuator = new Actuator(actuator_mailbox);
    //TODO call actuator isGate()
    //adc = new ADC_Class(dispatcher_rcvid, adc_mailbox);
    halThread = std::thread(&HAL::threadFunction, this);
}
void HAL::threadFunction() {
    DEBUG("HAL Thread started.");
    hal_running = true;
    while(hal_running) {
        _pulse event;
        local_receiver->receive_event(&event);
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


void HAL::test_ins() {
    std::cout << "Testing Inputs... Please put Piece on the front laser" << std::endl;
    bool running = true;
    int8_t actuatorCode = (int8_t) Topic::ACTUATOR;
    bool allowGo = true;
    bool allowSorting = true;
    while(running) {
        _pulse msg;
        mock_dispatcher_receiver->receive_event(&msg);
        InterruptEnum event = (InterruptEnum) msg.value.sival_int;
        switch(event) {
            case InterruptEnum::LASER_FRONT_BLOCKED:
                std::cout << "Thanks!" << std::endl;
                mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::TRAFFIC_GREEN_ON);
                if(allowGo) {
                    mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::MOTOR_RIGHT_START);
                }
                break;
            case InterruptEnum::LASER_BACK_BLOCKED:
                mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::MOTOR_STOP);
                mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::TRAFFIC_GREEN_OFF);
                mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::TRAFFIC_RED_ON);
                allowGo = false;
                break;
            case InterruptEnum::LASER_BACK_UNBLOCKED:
                mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::TRAFFIC_RED_OFF);
                mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::TRAFFIC_YELLOW_OFF);
                mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::TRAFFIC_GREEN_OFF);
                allowGo = true;
                break;
            case InterruptEnum::LASER_SORTING_GATE_BLOCKED:
                if(!allowSorting) {
                    break;
                }
                mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::SORTING_ON);
                WAIT(500);
                mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::SORTING_OFF);
                break;
            case InterruptEnum::BUTTON_ESTOP_PRESSED:
                running = false;
                break;
            case InterruptEnum::BUTTON_STOP_PRESSED:
                running = false;
                break;
            case InterruptEnum::ADC_TOP_AREA_BLOCKED:
                mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::MOTOR_SLOW_ON);
                mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::TRAFFIC_YELLOW_ON);
                break;
            case InterruptEnum::ADC_TOP_AREA_UNBLOCKED:
                mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::MOTOR_SLOW_OFF);
                mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::TRAFFIC_YELLOW_OFF);
                break;
            case InterruptEnum::LASER_RAMP_BLOCKED:
                allowSorting = false;
                break;
            case InterruptEnum::LASER_RAMP_UNBLOCKED:
                allowSorting = true;
                break;
            default:
                break;
        }
    }
    std::cout << "Testing Input done." << std::endl;
}