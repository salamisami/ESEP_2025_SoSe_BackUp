#include "Operating.h"

//================================================= contructors & destructors =================================================

Operating::Operating(ContextData* data, State* previousState): State(data) {
    if(previousState == nullptr) {
        substate = new Traffic_Green_On_Slow(data);
    } else {
        substate = previousState;
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
//     data->stateStack->push(substate);
//     return new EmergencyStop(data);
// }

// State* Operating::forward() {
//     State* newSubstate = substate->forward();
//     if(newSubstate != nullptr) {
//         substate->exit();
//         delete substate;
//         substate = newSubstate;
//         substate->entry();
//     }
//     return nullptr;
// }

// State* Operating::backward() {
//     State* newSubstate = substate->backward();
//     if(newSubstate != nullptr) {
//         substate->exit();
//         delete substate;
//         substate = newSubstate;
//         substate->entry();
//     }
//     return nullptr;
// }

// State* Operating::tick() {
//     substate->exit();
//     substate->entry();
//     return nullptr;
// }

// State* Operating::service() {
//     State* newSubstate = substate->service();
//     if(newSubstate != nullptr) {
//         return newSubstate;
//     }
//     return nullptr;
// }


