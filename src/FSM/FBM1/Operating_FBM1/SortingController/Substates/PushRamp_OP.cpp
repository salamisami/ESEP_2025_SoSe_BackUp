#include "PushRamp_OP.h"

PushRamp_OP::PushRamp_OP(ContextData* data) : State(data){}
PushRamp_OP::~PushRamp_OP(){}

void PushRamp_OP::entry(){
  PRINT_STATE;
  data->timer->start_timer(500, TIMER_ID::OPENGATE_OP);
  //HIER ANPASSEN ROBIN
  data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::SORTING_ON);
}

void PushRamp_OP::exit(){
  PRINT_STATE;
  data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::SORTING_OFF);

}

State* PushRamp_OP::clone(){
  return new PushRamp_OP(data);
}

State* PushRamp_OP::timer(TIMER_ID id){
  if(id == TIMER_ID::PUSHRAMP_OP){
    return new IdleSorting(data);
  }
  return nullptr;
}
