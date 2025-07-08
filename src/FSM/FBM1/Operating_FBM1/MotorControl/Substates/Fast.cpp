#include "Fast.h"

//================================================= constructors & destructors =================================================
Fast::Fast(ContextData *data) : State(data)
{
    // substate = new SubState(data);
}

Fast::~Fast() {}

//===================================================== private functions =====================================================

//===================================================== public functions =====================================================
void Fast::entry()
{
    PRINT_STATE;
}

void Fast::exit()
{
    PRINT_STATE;
}

State *Fast::delete_w_motor()
{
  updateData(MotorPieceState::DELETE_W_MOTOR);
    if (data->workpieces)
    {
        return new Fast(data);
    }
    else
    {
        return new Idle(data);
    }
}

State *Fast::motor_slow()
{
    data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_SLOW_ON, (int) EventPriority::SECOND_PRIO);
    for (auto& pair : *data->pieces_map) {
    Piece* piece = pair.second;  // pair.second is the value (Piece*)
    piece->piece_tracker->slow();               // Call fast() on the Piece*
}
    updateData(MotorPieceState::SLOW);

    return new Slow(data);
}
State *Fast::motor_fast()
{
  updateData(MotorPieceState::FAST);  
    for (auto& pair : *data->pieces_map) {
    Piece* piece = pair.second;  // pair.second is the value (Piece*)
    piece->piece_tracker->fast();               // Call fast() on the Piece*
}
  return new Fast(data);
}

State *Fast::motor_stop_fsm()
{
  updateData(MotorPieceState::STOPPED);
    for (auto& pair : *data->pieces_map) {
    Piece* piece = pair.second;  // pair.second is the value (Piece*)
    piece->piece_tracker->stop();               // Call fast() on the Piece*
}
  data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_STOP, (int) EventPriority::SECOND_PRIO);
  return new Stop(data);
}

void Fast::updateData(MotorPieceState motorPieceState) {
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


State* Fast::clone() {
    return new Fast(data);
}

