#include "OrthogonalState.h"

#include "State.h"

//================================================= contructors & destructors =================================================
OrthogonalState::OrthogonalState(ContextData* data)
    : data(data) {
    //std::cout << "OrthogonalState Constructor" << std::endl;
    list_of_suborthogonalstates = new std::vector<OrthogonalState*>();

}

//copy constructor (deep copy)
OrthogonalState::OrthogonalState(const OrthogonalState& other) :data(other.data) {
    list_of_suborthogonalstates = new std::vector<OrthogonalState*>();
    for(OrthogonalState* current_orthogonalstate : *other.list_of_suborthogonalstates) {
        if(current_orthogonalstate != nullptr) {
            OrthogonalState* copy_current_orthogonalstate = new OrthogonalState(*current_orthogonalstate);
            list_of_suborthogonalstates->emplace_back(copy_current_orthogonalstate);
        } else {

        }
        this->data = other.data;
    }
}

OrthogonalState::~OrthogonalState() {
    //std::cout << "OrthogonalState Destructor" << std::endl;
    for(OrthogonalState* current_orthogonalstate : *list_of_suborthogonalstates) {
        if(current_orthogonalstate != nullptr) {
            delete current_orthogonalstate;
        }
    }
    delete list_of_suborthogonalstates;
}

//===================================================== private functions =====================================================

OrthogonalState* OrthogonalState::handle_event_using_function(OrthogonalState* (OrthogonalState::* handler_function)()) {
    for(OrthogonalState* current_orthogonalstate : *list_of_suborthogonalstates) { 
        if(current_orthogonalstate == nullptr) {
            //do nothing
        } else {
            OrthogonalState* newSuborthogonalstate = (current_orthogonalstate->*handler_function)();
            if(newSuborthogonalstate != nullptr) {
                // there is suborthogonalstates change, change only the suborthogonalstates
                current_orthogonalstate->exit();
                delete current_orthogonalstate;
                current_orthogonalstate = newSuborthogonalstate;
                current_orthogonalstate->entry();
            }
        }
    }
    return nullptr;
}

//save history
// OrthogonalState* OrthogonalStateA::estop_pressed() {
//     OrthogonalState* clone_suborthogonalstate = new OrthogonalState(*suborthogonalstates);
//     data->orthogonalstateStack->push(clone_suborthogonalstate);
//     return new EmergencyStop(data);
// }

//load history
// OrthogonalState* EmergencyStop::estop_released() {
//     OrthogonalState* loaded_orthogonalstate = data->orthogonalstateStack->top();
//     data->orthogonalstateStack->pop();
//     return new OrthogonalStateA(data, loaded_orthogonalstate);
// }

//outside loop
// OrthogonalState* OrthogonalStateA::restart(){
//     return new OrthogonalStateA(data);
// }

//inside loop
// OrthogonalState* OrthogonalStateA::tick() {
//     super_suborthogonalstate->exit();
//     super_suborthogonalstate->entry();
//     return nullptr;
// }

//explicit entry
// OrthogonalState* OrthogonalStateA::service() {
//      OrthogonalState* initial_explicit_suborthogonalstate = new StartEngine(data);
//      return new StartCar(data, initial_explicit_suborthogonalstate);
// }

//explicit exit
// OrthogonalState* OrthogonalStateA::service()  {
//     for(auto current_orthogonalstate : *list_of_suborthogonalstates) {
//         if(current_orthogonalstate == nullptr) {
//             //do nothing
//         } else {
//             OrthogonalState* newSuborthogonalstate = current_orthogonalstate->service();
//             if(newSuborthogonalstate != nullptr) {
//                 //there is a super_suborthogonalstate change, explicit exit
//                 return newSuborthogonalstate;
//             }
//         }
//     }
//     return nullptr;
// }

//===================================================== public functions =====================================================

void OrthogonalState::entry() {
    //std::cout << __PRETTY_FUNCTION__ << std::endl;
    for(auto current_orthogonalstate : *list_of_suborthogonalstates) {
        if(current_orthogonalstate != nullptr) {
            current_orthogonalstate->entry();
        }
    }
}

void OrthogonalState::exit() {
    //std::cout << __PRETTY_FUNCTION__ << std::endl;
    for(auto current_orthogonalstate : *list_of_suborthogonalstates) {
        if(current_orthogonalstate != nullptr) {
            current_orthogonalstate->exit();
        }
    }
}

OrthogonalState* OrthogonalState::timer(int id) {
    for(OrthogonalState* current_orthogonalstate : *list_of_suborthogonalstates) {
        if(current_orthogonalstate == nullptr) {
            //do nothing
        } else {
            OrthogonalState* newSuborthogonalstate = current_orthogonalstate->timer(id);
            if(newSuborthogonalstate != nullptr) {
                // there is suborthogonalstates change, change only the suborthogonalstates
                current_orthogonalstate->exit();
                delete current_orthogonalstate;
                current_orthogonalstate = newSuborthogonalstate;
                current_orthogonalstate->entry();
            }
        }
    }
    return nullptr;
}


OrthogonalState* OrthogonalState::laser_front_blocked() {
    return handle_event_using_function(&OrthogonalState::laser_front_blocked);
}

OrthogonalState* OrthogonalState::laser_front_unblocked() {
    return handle_event_using_function(&OrthogonalState::laser_front_unblocked);
}

OrthogonalState* OrthogonalState::laser_back_blocked() {
    return handle_event_using_function(&OrthogonalState::laser_back_blocked);
}

OrthogonalState* OrthogonalState::laser_back_unblocked() {
    return handle_event_using_function(&OrthogonalState::laser_back_unblocked);
}

OrthogonalState* OrthogonalState::button_start_pressed() {
    return handle_event_using_function(&OrthogonalState::button_start_pressed);
}

OrthogonalState* OrthogonalState::button_start_released() {
    return handle_event_using_function(&OrthogonalState::button_start_released);
}

OrthogonalState* OrthogonalState::button_stop_pressed() {
    return handle_event_using_function(&OrthogonalState::button_stop_pressed);
}

OrthogonalState* OrthogonalState::button_stop_released() {
    return handle_event_using_function(&OrthogonalState::button_stop_released);
}

OrthogonalState* OrthogonalState::button_reset_pressed() {
    return handle_event_using_function(&OrthogonalState::button_reset_pressed);
}

OrthogonalState* OrthogonalState::button_reset_released() {
    return handle_event_using_function(&OrthogonalState::button_reset_released);
}

OrthogonalState* OrthogonalState::button_estop_pressed() {
    return handle_event_using_function(&OrthogonalState::button_estop_pressed);
}

OrthogonalState* OrthogonalState::button_estop_released() {
    return handle_event_using_function(&OrthogonalState::button_estop_released);
}

OrthogonalState* OrthogonalState::metal_detected() {
    return handle_event_using_function(&OrthogonalState::metal_detected);
}

OrthogonalState* OrthogonalState::metal_not_detected() {
    return handle_event_using_function(&OrthogonalState::metal_not_detected);
}

OrthogonalState* OrthogonalState::laser_sorting_gate_blocked() {
    return handle_event_using_function(&OrthogonalState::laser_sorting_gate_blocked);
}

OrthogonalState* OrthogonalState::laser_sorting_gate_unblocked() {
    return handle_event_using_function(&OrthogonalState::laser_sorting_gate_unblocked);
}

OrthogonalState* OrthogonalState::laser_ramp_blocked() {
    return handle_event_using_function(&OrthogonalState::laser_ramp_blocked);
}

OrthogonalState* OrthogonalState::laser_ramp_unblocked() {
    return handle_event_using_function(&OrthogonalState::laser_ramp_unblocked);
}

OrthogonalState* OrthogonalState::adc_top_area_blocked() {
    return handle_event_using_function(&OrthogonalState::adc_top_area_blocked);
}

OrthogonalState* OrthogonalState::adc_top_area_unblocked() {
    return handle_event_using_function(&OrthogonalState::adc_top_area_unblocked);
}

OrthogonalState* OrthogonalState::adc_side_area_blocked() {
    return handle_event_using_function(&OrthogonalState::adc_side_area_blocked);
}

OrthogonalState* OrthogonalState::adc_side_area_unblocked() {
    return handle_event_using_function(&OrthogonalState::adc_side_area_unblocked);
}

OrthogonalState* OrthogonalState::adc_calibration_done() {
    return handle_event_using_function(&OrthogonalState::adc_calibration_done);
}

OrthogonalState* OrthogonalState::adc_new_piece() {
    return handle_event_using_function(&OrthogonalState::adc_new_piece);
}