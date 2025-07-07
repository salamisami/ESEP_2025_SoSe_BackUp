#include "Slow.h"

//================================================= constructors & destructors =================================================
Slow::Slow(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

Slow::~Slow() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void Slow::entry(){	
	PRINT_STATE;
}

void Slow::exit(){
    //TODO:Update data
    PRINT_STATE;
}

State* Slow::motor_fast(){
    if (data->motor_slowed){
        return new Slow(data);
    }
    else{
        data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_SLOW_OFF);
        updateData(MotorPieceState::FAST);
        for (auto& pair : *data->pieces_map) {
          Piece* piece = pair.second;  // pair.second is the value (Piece*)
          piece->piece_tracker->fast();               // Call fast() on the Piece*
        }
        return new Fast(data);
    }
}

State* Slow::motor_stop_fsm(){
        data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_SLOW_OFF);
        data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_STOP);
        for (auto& pair : *data->pieces_map) {
          Piece* piece = pair.second;  // pair.second is the value (Piece*)
          piece->piece_tracker->stop();               // Call fast() on the Piece*
        }
        updateData(MotorPieceState::STOPPED);
        return new Stop(data);
}

State *Slow::delete_w_motor()
{
  updateData(MotorPieceState::DELETE_W_MOTOR);
  if (data->workpieces)
    {
      return new Slow(data);
    }
  else
    {
      data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::MOTOR_SLOW_OFF);
      return new Idle(data);
    }
}
State* Slow::motor_slow(){
  updateData(MotorPieceState::SLOW);
        for (auto& pair : *data->pieces_map) {
          Piece* piece = pair.second;  // pair.second is the value (Piece*)
          piece->piece_tracker->slow();               // Call fast() on the Piece*
        }
    return new Slow(data);
}

void Slow::updateData(MotorPieceState motorPieceState) {
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

State* Slow::clone() {
    return new Slow(data);
}
