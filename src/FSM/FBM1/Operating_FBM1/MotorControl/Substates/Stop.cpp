#include "Stop.h"

//================================================= constructors & destructors =================================================
Stop::Stop(ContextData *data) : State(data)
{
    // substate = new SubState(data);
}

Stop::~Stop() {}

//===================================================== private functions =====================================================

//===================================================== public functions =====================================================
void Stop::entry()
{
    PRINT_STATE;
}

void Stop::exit()
{
    PRINT_STATE;
}

State *Stop::delete_w_motor()
{
    updateData(MotorPieceState::DELETE_W_MOTOR);
    if (data->workpieces)
    {
        return new Stop(data);
    }
    else
    {

        return new Idle(data);
    }
}

State *Stop::motor_slow()
{
    if (data->motor_stopped)
    {
        return new Stop(data);
    }
    else
    {
        updateData(MotorPieceState::SLOW);
        data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_RIGHT_START, (int) EventPriority::SECOND_PRIO);       
        data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_SLOW_ON, (int) EventPriority::SECOND_PRIO);
        for (auto& pair : *data->pieces_map) {
          Piece* piece = pair.second;  // pair.second is the value (Piece*)
          piece->piece_tracker->slow();               // Call fast() on the Piece*
        }
        return new Slow(data);
    }
}

State *Stop::motor_fast()
{
    if (data->motor_stopped)
    {
        return new Stop(data);
    }
    else
    {
        data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_RIGHT_START, (int) EventPriority::SECOND_PRIO);
        for (auto& pair : *data->pieces_map) {
          Piece* piece = pair.second;  // pair.second is the value (Piece*)
          piece->piece_tracker->fast();               // Call fast() on the Piece*
        }
        updateData(MotorPieceState::FAST);
        return new Fast(data);
    }
}

State *Stop::motor_stop_fsm()
{
  updateData(MotorPieceState::STOPPED);
  for (auto& pair : *data->pieces_map) {
    Piece* piece = pair.second;  // pair.second is the value (Piece*)
    piece->piece_tracker->stop();               // Call fast() on the Piece*
  }  
  return new Stop(data);
}

void Stop::updateData(MotorPieceState motorPieceState) {
    int id = data->event_payload;
    
    if (motorPieceState == MotorPieceState::DELETE_W_MOTOR) {
        // Remove the ID from the list if it exists
        if (data->workpieceList.contains(id)) {
            data->workpieceList.remove(id);
        } else {
            printf("Warning: Trying to delete ID %d that doesn't exist in workpiece list\n", id);
        }
    } else {
        // Add the ID if it doesn't exist, then update ALL workpieces to new state
        if (!data->workpieceList.contains(id)) {
            data->workpieceList.add(id, motorPieceState);
        }
        data->workpieceList.updateStateAll(motorPieceState);
    }
    data->workpieces = !data->workpieceList.isEmpty();
}

State* Stop::clone() {
    return new Stop(data);
}
