#include "Operating.h"

//================================================= constructors & destructors =================================================

Operating::Operating(ContextData* data): OrthState(data,{
    new PieceControllerFBM1(data),
    new MotorControl(data),
    new SortingOrder(data),
    new StartingAreaTracker(data),
    new ErrorHandler(data)
}) {
}

Operating::Operating(ContextData* data, std::deque<State*> initial_substates): OrthState(data, initial_substates) {
    
}

Operating::~Operating() {
}

//===================================================== private functions =====================================================

//void Operating::privateFunction(){}

//===================================================== public functions =====================================================

void Operating::entry() {
    PRINT_STATE;
    data->sender->send_event((int8_t)Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_GREEN_ON);
    //data->sender->send_event((int8_t)Topic::ADC, (int) ADC_Enum::ADC_MESURE);
    OrthState::entry();
}

void Operating::exit() {
    OrthState::exit();
    PRINT_STATE;
    data->sender->send_event((int8_t)Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_GREEN_OFF);
}


State* Operating::button_stop_pressed() {
    return new IdleMode(data);
}

State* Operating::clone() {
    return new Operating(data, clone_substates());
}