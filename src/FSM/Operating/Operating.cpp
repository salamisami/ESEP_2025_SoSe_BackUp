#include "Operating.h"

//================================================= contructors & destructors =================================================

Operating::Operating(ContextData* data, State* previousState): State(data){
    : State(data) {
    if(previousState == nullptr) {
        subState = new Traffic_Green_On_Slow(data);
    } else {
        subState = previousState;
    }
}

Operating::~Operating() {
}

//===================================================== private functions =====================================================

//void Operating::privateFunction(){}

//===================================================== public functions =====================================================

void Operating::entry() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    data->sender->send_event((int8_t)Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_GREEN_ON);
}

void Operating::exit() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    data->sender->send_event((int8_t)Topic::ACTUATOR, (int) ActuatorEnum::TRAFFIC_GREEN_OFF);
}

State* Operating::button_stop_pressed() {
    return new Idle(data);
}

// State* Operating::estop() {
//     data->stateStack->push(subState);
//     return new EmergencyStop(data);
// }

// State* Operating::forward() {
//     State* newSubstate = subState->forward();
//     if(newSubstate != nullptr) {
//         subState->exit();
//         delete subState;
//         subState = newSubstate;
//         subState->entry();
//     }
//     return nullptr;
// }

// State* Operating::backward() {
//     State* newSubstate = subState->backward();
//     if(newSubstate != nullptr) {
//         subState->exit();
//         delete subState;
//         subState = newSubstate;
//         subState->entry();
//     }
//     return nullptr;
// }

// State* Operating::tick() {
//     subState->exit();
//     subState->entry();
//     return nullptr;
// }

// State* Operating::service() {
//     State* newSubstate = subState->service();
//     if(newSubstate != nullptr) {
//         return newSubstate;
//     }
//     return nullptr;
// }


