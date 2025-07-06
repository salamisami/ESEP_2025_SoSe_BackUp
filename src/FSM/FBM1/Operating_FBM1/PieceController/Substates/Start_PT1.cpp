#include "Start_PT1.h"

//================================================= constructors & destructors =================================================
Start_PT1::Start_PT1(ContextData* data, LocalDataPT1 localdata) : State(data), localdata_(localdata) {
    //substate = new SubState(data);
}

Start_PT1::~Start_PT1() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void Start_PT1::entry(){
	PRINT_STATE;
	data->sender->send_event((int8_t) Topic::MOTOR_FAST, (int) localdata_.id);
}

void Start_PT1::exit(){
	PRINT_STATE;
}

State* Start_PT1::clone(){
	return new Start_PT1(data, localdata_);
}

State* Start_PT1::laser_front_unblocked() {
	return new StartADC_PT1(data, localdata_);
}