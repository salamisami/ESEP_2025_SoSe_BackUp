#include "SortingOut_PT1.h"

//================================================= constructors & destructors =================================================
SortingOut_PT1::SortingOut_PT1(ContextData* data, LocalDataPT1 localdata) : State(data), localdata_(localdata) {
    //substate = new SubState(data);
}

SortingOut_PT1::~SortingOut_PT1() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void SortingOut_PT1::entry(){
  data->timer->start_timer(1000, TIMER_ID::SORTINGOUT_PT1);
  data->timer->start();
	PRINT_STATE;
}

void SortingOut_PT1::exit(){
  data->timer->stop();
	PRINT_STATE;
}

State* SortingOut_PT1::clone(){
	return new SortingOut_PT1(data, localdata_);
}

State* SortingOut_PT1::laser_ramp_blocked(){
	data->sender->send_event((int8_t) Topic::DELETE_W_MOTOR, (int) localdata_.id);
  return State::EXIT_STATE;
}

State* SortingOut_PT1::timer(TIMER_ID id){
  if (id == TIMER_ID::SORTINGOUT_PT1){
    return new PieceMissing_PT1(data, localdata_);
  }
  return nullptr;
}

