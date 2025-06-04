#include "HAL.h"

#define MAILBOX_SIZE 1

//================================================= contructors & destructors =================================================
HAL::HAL(I_Receiver* local_receiver, I_Sender* local_sender) {
    detached = false;
    this->local_receiver = local_receiver;
    this->local_sender = local_sender;
    //mock_dispatcher_sender = new PulseMsg::Sender(local_receiver->getchid());
    init();
}

HAL::HAL() {
    detached = true;
    local_receiver = new PulseMsg::Receiver();
    mock_dispatcher_receiver = new PulseMsg::Receiver();
    local_sender = new PulseMsg::Sender(mock_dispatcher_receiver->getchid());
    mock_dispatcher_sender = new PulseMsg::Sender(local_receiver->getchid());
    init();
}

HAL::~HAL() {
    mock_dispatcher_sender->send_event((int8_t) Topic::STOP_THREAD, 0);
    halThread.join();
    delete adc;
    delete interrupt;
    delete actuator;
    //DEBUG("Actuator and Interrupts are deleted");

    delete adc_mailbox;
    delete actuator_mailbox;

    if(detached) {
        delete mock_dispatcher_sender;
        delete local_sender;
        delete mock_dispatcher_receiver;
        delete local_receiver;
    } else {
        delete mock_dispatcher_sender;
    }
}

//===================================================== private functions =====================================================
void HAL::init() {
    actuator_mailbox = new Mailbox<_pulse>(MAILBOX_SIZE);
    adc_mailbox = new Mailbox<_pulse>(MAILBOX_SIZE);
    DEBUG("Mailboxes are created");
    adc = new ADC_Class(adc_mailbox, local_sender);
    //TODO rethink SoC regarding the ESTOP
    actuator = new Actuator(actuator_mailbox, adc);
    interrupt = new Interrupt(local_sender, actuator);


    //TODO check that no sensors are blocked during init
    bool isGate = actuator->isGate();
    if(isGate) {
        local_sender->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::IS_SWITCH);
    } else {
        local_sender->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::IS_PUSHER);
    }
    halThread = std::thread(&HAL::threadFunction, this);
}
void HAL::threadFunction() {
    DEBUG("HAL Thread started.");
    hal_running = true;
    _pulse event;
    while(hal_running) {
        local_receiver->receive_event(&event);
        Topic event_code = (Topic) event.code;
        //int event_value = event.value.sival_int;
        switch(event_code) {
            case Topic::ACTUATOR:
                actuator_mailbox->put(event);
                break;
            case Topic::COM:
                actuator_mailbox->put(event);
                break;
            case Topic::ADC:
                adc_mailbox->put(event);
                break;
            case Topic::STOP_THREAD:
                hal_running = false;
                break;
            default:
                break;
        }
    }
    actuator_mailbox->put(event);
    adc_mailbox->put(event);
}

//===================================================== public functions =====================================================


void HAL::test_ins_ADC() {
    std::cout << "Testing ADC... Please put Piece on the front laser" << std::endl;
    bool running = true;
    int8_t actuatorCode = (int8_t) Topic::ACTUATOR;
    //int8_t AdcCode = (int8_t) Topic::ADC;
    bool calibrated = false;
    //bool allowGo = true;
    //bool allowSorting = true;
    bool is_weiche = false;
    if(!calibrated) {
        mock_dispatcher_sender->send_event((int8_t) Topic::ADC, (int) ADC_Enum::ADC_CALIBRATE);
    }
    while(running) {
        _pulse msg;
        mock_dispatcher_receiver->receive_event(&msg);
        Topic topic = (Topic) msg.code;
        switch(topic) {
            case Topic::INTERRUPT: {
                    InterruptEnum InterEvent = (InterruptEnum) msg.value.sival_int;
                    switch(InterEvent) {
                        case InterruptEnum::IS_PUSHER:
                            is_weiche = false;
                            break;
                        case InterruptEnum::IS_SWITCH:
                            is_weiche = true;
                            break;
                        case InterruptEnum::BUTTON_RESET_PRESSED:
                            running = false;
                            break;
                        case InterruptEnum::LASER_FRONT_BLOCKED:
                            std::cout << "Thanks!" << std::endl;
                            mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::TRAFFIC_GREEN_ON);
                            mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::MOTOR_RIGHT_START);
                            if(!calibrated) {
                                mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::MOTOR_SLOW_ON);
                            } else {
                                mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::MOTOR_SLOW_OFF);
                            }
                            break;
                        case InterruptEnum::LASER_FRONT_UNBLOCKED:
                            mock_dispatcher_sender->send_event((int8_t) Topic::ADC, (int) ADC_Enum::ADC_PREPARE);
                            break;
                        case InterruptEnum::LASER_BACK_BLOCKED:
                            mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::MOTOR_STOP);
                            mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::TRAFFIC_GREEN_OFF);
                            mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::TRAFFIC_RED_ON);
                            //allowGo = false;
                            break;
                        case InterruptEnum::LASER_BACK_UNBLOCKED:
                            mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::TRAFFIC_RED_OFF);
                            mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::TRAFFIC_YELLOW_OFF);
                            mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::TRAFFIC_GREEN_OFF);
                            //allowGo = true;
                            break;
                        case InterruptEnum::LASER_SORTING_GATE_BLOCKED:
                            if(calibrated) {
                                //let through
                                if(is_weiche) {
                                    //open the gate to go through
                                    mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::SORTING_ON);
                                    WAIT(500);
                                    mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::SORTING_OFF);
                                } else {
                                    //do not push to the ramp
                                }
                            } else {
                                //send to ramp
                                if(is_weiche) {
                                    //do nothing and let it slide 🛝
                                } else {
                                    //push the piece to ramp
                                    mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::SORTING_ON);
                                    WAIT(500);
                                    mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::SORTING_OFF);
                                }
                            }
                            break;
                        case InterruptEnum::BUTTON_ESTOP_PRESSED:
                            //running = false;
                            break;
                        case InterruptEnum::BUTTON_STOP_PRESSED:
                            //running = false;
                            break;
                        default:
                            break;
                    }
                    break;
                }
            case Topic::ADC: {
                    ADC_Enum AdcEvent = (ADC_Enum) msg.value.sival_int;
                    switch(AdcEvent) {
                        case ADC_Enum::ADC_NEW_PIECE:
                            mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::MOTOR_SLOW_ON);
                            mock_dispatcher_sender->send_event((int8_t) Topic::ADC, (int) ADC_Enum::ADC_MESURE);
                            mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::TRAFFIC_YELLOW_ON);
                            break;
                        case ADC_Enum::ADC_CALIBRATION_DONE:
                            mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::MOTOR_STOP);
                            calibrated = true;
                            DEBUG("Calibration Done!");
                            break;
                        case ADC_Enum::ADC_WH_DETECT:
                            DEBUG("ADC_WH_DETECT");
                            mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::MOTOR_SLOW_OFF);
                            mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::TRAFFIC_YELLOW_OFF);
                            break;
                        case ADC_Enum::ADC_WF_DETECT:
                            mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::MOTOR_SLOW_OFF);
                            mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::TRAFFIC_YELLOW_OFF);
                            DEBUG("ADC_WF_DETECT");
                            break;
                        case ADC_Enum::ADC_W_B_DETECT:
                            mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::MOTOR_SLOW_OFF);
                            mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::TRAFFIC_YELLOW_OFF);
                            DEBUG("ADC_W_B_DETECT");
                            break;
                        case ADC_Enum::ADC_W_NOT_DETECT:
                            mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::MOTOR_SLOW_OFF);
                            mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::TRAFFIC_YELLOW_OFF);
                            DEBUG("ADC_W_NOT_DETECT");
                            break;
                        case ADC_Enum::ADC_INVALID_MESURE:
                            //TODO implement this event
                            break;
                        default:
                            break;
                    }
                    break;
                }
            default:
                break;
        }
    }
    std::cout << "Testing ADC done." << std::endl;
}




void HAL::test_ins() {
    std::cout << "Testing Inputs... Please put Piece on the front laser" << std::endl;
    bool running = true;
    int8_t actuatorCode = (int8_t) Topic::ACTUATOR;
    bool allowGo = true;
    bool allowSorting = true;
    bool is_weiche = false;
    mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::TRAFFIC_GREEN_ON_SLOW);
    while(running) {
        _pulse msg;
        mock_dispatcher_receiver->receive_event(&msg);
        InterruptEnum event = (InterruptEnum) msg.value.sival_int;
        switch(event) {
            case InterruptEnum::IS_PUSHER:
                is_weiche = false;
                break;
            case InterruptEnum::IS_SWITCH:
                is_weiche = true;
                break;
            case InterruptEnum::LASER_FRONT_BLOCKED:
                std::cout << "Thanks!" << std::endl;
                if(allowGo) {
                    mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::MOTOR_RIGHT_START);
                    mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::TRAFFIC_GREEN_ON_FAST);
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

                mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::TRAFFIC_GREEN_ON_SLOW);
                allowGo = true;
                break;
            case InterruptEnum::LASER_SORTING_GATE_BLOCKED:
                if(allowSorting) {
                    if(is_weiche) {
                        //let the piece go to ramp
                    } else {
                        //open the gate to allow piece go through
                        mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::SORTING_ON);
                        WAIT(500);
                        mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::SORTING_OFF);
                    }
                } else {
                    if(is_weiche) {
                        //push the piece to ramp
                        mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::SORTING_ON);
                        WAIT(500);
                        mock_dispatcher_sender->send_event(actuatorCode, (int) ActuatorEnum::SORTING_OFF);
                    } else {
                        //let the piece go through
                    }
                }
                break;
            case InterruptEnum::BUTTON_ESTOP_PRESSED:
                //running = false;
                break;
            case InterruptEnum::BUTTON_STOP_PRESSED:
                mock_dispatcher_sender->send_event((int8_t) Topic::COM, (int) COM_Enum::BUTTON_ESTOP_PRESSED);
                break;
            case InterruptEnum::BUTTON_STOP_RELEASED:
                mock_dispatcher_sender->send_event((int8_t) Topic::COM, (int) COM_Enum::BUTTON_ESTOP_RELEASED);
                break;
            case InterruptEnum::BUTTON_RESET_PRESSED:
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
