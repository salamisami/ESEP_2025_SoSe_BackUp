#ifndef CONTEXT_H
#define CONTEXT_H
#pragma once

#include "State.h"
#include "Macros.h"

template <typename T>
class Context
{
    static_assert(std::is_base_of<State, T>::value, "Template parameter must inherit from State");
    //============================================ constructors & destructors ============================================
public:
    Context();
    Context(ContextData *data);
    virtual ~Context();

    //================================================ public functions ================================================
public:
    virtual void handleEvent(_pulse event);
    std::string show_state();

    //================================================ private variables ================================================
protected:
    ContextData *data;
    State *state;

    //================================================ private functions ================================================
private:
    State* handleInterrupt(int event_value);
    State* handleCOM(int event_value);
    State* handleADC(int event_value);
    State* handleInternal(int event_value);
    State* handlePiece(int event_value);
    State* handleError(int event_value);
};

//================================================= constructors & destructors =================================================
template <typename T>
Context<T>::Context()
{
}
template <typename T>
Context<T>::Context(ContextData *data) : state(new T(data))
{
    this->data = data;
    state->entry();
}
template <typename T>
Context<T>::~Context()
{
    delete state;
}

//===================================================== private functions =====================================================

template <typename T>
State* Context<T>::handleInternal(int event_value) {
    State* newState = nullptr;
    switch((Internal_Enum) event_value) {
        case Internal_Enum::NEW_PIECE:
            newState = state->new_piece();
            break;
        case Internal_Enum::SORT_OUT:
            newState = state->sort_out();
            break;
        case Internal_Enum::SORT_OUT_FBM2:
            newState = state->sort_out_fbm2();
            break;
        case Internal_Enum::LET_THROUGH:
            newState = state->let_through();
            break;
        case Internal_Enum::RESET_TO_FLAT:
            newState = state->reset_to_flat();
            break;
        case Internal_Enum::RESET_TO_TALL:
            newState = state->reset_to_tall();
            break;
        case Internal_Enum::RESET_TO_TALL_W_METAL:
            newState = state->reset_to_tall_w_metal();
            break;
        case Internal_Enum::RAMP_FULL:
            newState = state->ramp_full();
            break;
        case Internal_Enum::RAMP_NOT_FULL:
            newState = state->ramp_not_full();
            break;
        case Internal_Enum::UNBLOCK_STARTING_AREA:
            newState = state->unblock_starting_area();
            break;
        case Internal_Enum::DELETE_W_MOTOR:
            newState = state->delete_w_motor();
            break;
        case Internal_Enum::MOTOR_FAST:
            newState = state->motor_fast();
            break;
        case Internal_Enum::MOTOR_SLOW:
            newState = state->motor_slow();
            break;
        case Internal_Enum::MOTOR_STOP_FSM:
            newState = state->motor_stop_fsm();
            break;
        case Internal_Enum::SORTED:
            newState = state->sorted();
            break;
        default:
            break;
    }
    return newState;
}



template<typename T>
State* Context<T>::handleADC(int event_value) {
    //TODO put newState = state->function() here
    State* newState = nullptr;
    switch((ADC_Enum) event_value) {
        case ADC_Enum::ADC_TIMEOUT:
            newState = state->adc_timeout();
            break;
        case ADC_Enum::ADC_NEW_PIECE:
            newState = state->adc_new_piece();
            break;
        case ADC_Enum::ADC_CALIBRATION_DONE:
            newState = state->adc_calibration_done();
            break;
        case ADC_Enum::ADC_W_B_DETECT:
            newState = state->adc_w_b_detect();
            break;
        case ADC_Enum::ADC_WF_DETECT:
            newState = state->adc_wf_detect();
            break;
        case ADC_Enum::ADC_WH_DETECT:
            newState = state->adc_wh_detect();
            break;
        case ADC_Enum::ADC_W_NOT_DETECT:
            newState = state->adc_w_not_detect();
            break;
        case ADC_Enum::ADC_INVALID_MESURE:
            newState = state->adc_invalid_measure();
            break;
        case ADC_Enum::ADC_CALIBRATE:
            break;
        case ADC_Enum::ADC_MESURE:
            break;
        case ADC_Enum::ADC_PREPARE:
            break;
        case ADC_Enum::ADC_STOP:
            newState = state->adc_w_not_detect();
            break;
        default:
            break;
    }
    return newState;

}


template <typename T>
State* Context<T>::handleCOM(int event_value) {
    State* newState = nullptr;
    switch((COM_Enum) event_value) {
        //TODO is this true?
        case COM_Enum::NEW_PIECE_TO_SORT:
            newState = state->new_piece_to_sort();
            break;
        case COM_Enum::NEW_PIECE_NOT_TO_SORT:
            newState = state->new_piece_not_to_sort();
            break;
        case COM_Enum::BUTTON_ESTOP_PRESSED:
            newState = state->com_button_estop_pressed();
            break;
        case COM_Enum::BUTTON_ESTOP_RELEASED:
            newState = state->com_button_estop_released();
            break;
        case COM_Enum::HEARTBEAT:
            newState = state->heartbeat();
            break;
        case COM_Enum::TIMEOUT_COM:
            newState = state->timeout_com();
            break;
        case COM_Enum::RECONNECT:
            newState = state->reconnect();
            break;
        case COM_Enum::RAMP_FULL:
            newState = state->ramp_full();
            break;
        case COM_Enum::RAMP_NOT_FULL:
            newState = state->ramp_not_full();
            break;
        case COM_Enum::RESET_TO_FLAT:
            newState = state->reset_to_flat();
            break;
        case COM_Enum::RESET_TO_TALL:
            newState = state->reset_to_tall();
            break;
        case COM_Enum::RESET_TO_TALL_W_METAL:
            newState = state->reset_to_tall_w_metal();
            break;
        case COM_Enum::FBM_2_READY:
            newState = state->fbm_2_ready();
            break;
        case COM_Enum::FBM_2_BUSY:
            newState = state->fbm_2_busy();
            break;
        case COM_Enum::REQUEST_TRANSFER:
            newState = state->request_transfer();
            break;
        case COM_Enum::TRANSFER_DONE:
            newState = state->transfer_done();
            break;
        case COM_Enum::TRANSFER_FAILED:
            newState = state->transfer_failed();
            break;
        case COM_Enum::TRANSFER_START_TALL:
            newState = state->transfer_start_tall();
            break;
        case COM_Enum::TRANSFER_START_TALL_W_METAL:
            newState = state->transfer_start_tall_w_metal();
            break;
        case COM_Enum::TRANSFER_START_FLAT:
            newState = state->transfer_start_flat();
            break;
        case COM_Enum::TRANSFER_START_OTHER:
            newState = state->transfer_start_other();
            break;
        case COM_Enum::TRANSFER_START_TALL_SORT_OUT:
            newState = state->transfer_start_tall_sort_out();
            break; 
        case COM_Enum::TRANSFER_START_TALL_W_METAL_SORT_OUT:
            newState = state->transfer_start_tall_w_metal_sort_out();   
            break;
        case COM_Enum::TRANSFER_START_FLAT_SORT_OUT:
            newState = state->transfer_start_flat_sort_out();
            break;  
        default:
            break;
    }
    return newState;
}


template <typename T>
State *Context<T>::handleInterrupt(int event_value)
{
    State *newState = nullptr;
    switch ((InterruptEnum)event_value)
    {
    case InterruptEnum::LASER_FRONT_BLOCKED:
        newState = state->laser_front_blocked();
        break;
    case InterruptEnum::LASER_FRONT_UNBLOCKED:
        newState = state->laser_front_unblocked();
        break;
    case InterruptEnum::LASER_BACK_BLOCKED:
        newState = state->laser_back_blocked();
        break;
    case InterruptEnum::LASER_BACK_UNBLOCKED:
        newState = state->laser_back_unblocked();
        break;
    case InterruptEnum::BUTTON_START_PRESSED:
        newState = state->button_start_pressed();
        break;
    case InterruptEnum::BUTTON_START_RELEASED:
        newState = state->button_start_released();
        break;
    case InterruptEnum::BUTTON_STOP_PRESSED:
        newState = state->button_stop_pressed();
        break;
    case InterruptEnum::BUTTON_STOP_RELEASED:
        newState = state->button_stop_released();
        break;
    case InterruptEnum::BUTTON_RESET_PRESSED:
        newState = state->button_reset_pressed();
        break;
    case InterruptEnum::BUTTON_RESET_RELEASED:
        newState = state->button_reset_released();
        break;
    case InterruptEnum::BUTTON_ESTOP_PRESSED:
        newState = state->button_estop_pressed();
        break;
    case InterruptEnum::BUTTON_ESTOP_RELEASED:
        newState = state->button_estop_released();
        break;
    case InterruptEnum::METAL_DETECTED:
        newState = state->metal_detected();
        break;
    case InterruptEnum::METAL_NOT_DETECTED:
        newState = state->metal_not_detected();
        break;
    case InterruptEnum::LASER_SORTING_GATE_BLOCKED:
        newState = state->laser_sorting_gate_blocked();
        break;
    case InterruptEnum::LASER_SORTING_GATE_UNBLOCKED:
        newState = state->laser_sorting_gate_unblocked();
        break;
    case InterruptEnum::LASER_RAMP_BLOCKED:
        newState = state->laser_ramp_blocked();
        break;
    case InterruptEnum::LASER_RAMP_UNBLOCKED:
        newState = state->laser_ramp_unblocked();
        break;
    case InterruptEnum::ADC_TOP_AREA_BLOCKED:
        newState = state->adc_top_area_blocked();
        break;
    case InterruptEnum::ADC_TOP_AREA_UNBLOCKED:
        newState = state->adc_top_area_unblocked();
        break;
        // case InterruptEnum::ADC_SIDE_AREA_BLOCKED:
        //     newState = state->adc_side_area_blocked();
        //     break;
        // case InterruptEnum::ADC_SIDE_AREA_UNBLOCKED:
        //     newState = state->adc_side_area_unblocked();
        //     break;
    case InterruptEnum::IS_SWITCH:
        newState = state->is_switch();
        break;
    case InterruptEnum::IS_PUSHER:
        newState = state->is_pusher();
        break;
    default:
        break;
    }
    return newState;
}


template <typename T>
State* Context<T>::handlePiece(int event_value) {
    State* newState = nullptr;
    switch((PieceEnum) event_value) {
        case PieceEnum::UNKNOWN:
            newState = state->unknown_piece();
            break;
        case PieceEnum::FLAT:
            newState = state->flat_piece();
            break;
        case PieceEnum::TALL:
            newState = state->tall_piece();
            break;
        case PieceEnum::TALL_WITH_METAL:
            newState = state->tall_w_metal_piece();
            break;
        default:
            break;
    }
    return newState;
}

template <typename T>
State* Context<T>::handleError(int event_value) {
    State* newState = nullptr;
    switch((Error_Enum) event_value) {
        case Error_Enum::ERROR_W_LOST:
            newState = state->error_w_lost();
            break;
        case Error_Enum::ERROR_W_APPEARED:
            newState = state->error_w_appear();
            break;
        case Error_Enum::PIECE_APPEARED_RESOLVED:
            newState = state->piece_appeared_resolved();
            break;
        case Error_Enum::ERROR_W_LOST_RESOLVED:
            newState = state->piece_lost_resolved();
            break;
        default:
            break;
    }
    return newState;
}


//===================================================== public functions =====================================================
template <typename T>
std::string Context<T>::show_state() {
    return state->get_current_state();
}

template <typename T>
void Context<T>::handleEvent(_pulse event)
{
    State *newState = nullptr;
    Topic event_code = (Topic)event.code;
    int event_value = event.value.sival_int;
    data->event_payload = event_value;
    switch(event_code) {
        case Topic::INTERRUPT:
            newState = handleInterrupt(event_value);
            break;
        case Topic::TIMER:
            newState = state->timer((TIMER_ID) event_value);
            break;
        case Topic::ADC:
            newState = handleADC(event_value);
            break;
        case Topic::INTERNAL:
            newState = handleInternal(event_value);
            break;
        case Topic::COM:
            newState = handleCOM(event_value);
            break;
        case Topic::CHECK_PIECE:
            newState = handlePiece(event_value);
            break;
        case Topic::ERROR:
            newState = handleError(event_value);
            break;
        case Topic::STOP_THREAD:
            state->exit();
            break;
        case Topic::MOTOR_STOP_FSM:
            newState = state->motor_stop_fsm();
            break;
        case Topic::MOTOR_FAST:
            newState = state->motor_fast();
            break;
        case Topic::MOTOR_SLOW:
            newState = state->motor_slow();
            break;
        case Topic::DELETE_W_MOTOR:
            newState = state->delete_w_motor();
            break;
        default:
            break;
    }
    if (newState != nullptr)
    {
        state->exit();
        delete state;
        // Check if we're getting an exit request
        if(newState == State::EXIT_STATE) {
            // Handle according to your state machine's requirements:
            // - Terminate program
            // - Transition to error state
            // - Restart machine
            THROW("Top-level state requested exit");
        } else {
            state = newState;
            state->entry();
        }
    }
}

#endif
