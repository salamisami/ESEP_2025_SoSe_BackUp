#include "OpenGate_OP.h"

OpenGate_OP::OpenGate_OP(ContextData* data) : State(data){}
OpenGate_OP::~OpenGate_OP(){}

void OpenGate_OP::entry(){
  PRINT_STATE;
  data->timer->start_timer(500, TIMER_ID::OPENGATE_OP);
  data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::SORTING_ON);
}

void OpenGate_OP::exit(){
  PRINT_STATE;
  data->sender->send_event((int8_t) Topic::ACTUATOR, (int) ActuatorEnum::SORTING_OFF);

}

State* OpenGate_OP::clone(){
  return new OpenGate_OP(data);
}

State* OpenGate_OP::timer(TIMER_ID id){
  if(id == TIMER_ID::OPENGATE_OP){
    return new IdleSorting(data);
  }
  return nullptr;
}
