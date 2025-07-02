#include "EStopTest.h"

//================================================= constructors & destructors =================================================
EStopTest::EStopTest(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

EStopTest::~EStopTest() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void EStopTest::entry(){
	PRINT_STATE;
}

void EStopTest::exit(){
	PRINT_STATE;
}

State* EStopTest::clone(){
	return new EStopTest(data);
}

State* EStopTest::button_estop_pressed() {
	PRINT_STATE;
	return nullptr;
}

State* EStopTest::button_estop_released() {
	return nullptr;
	PRINT_STATE;
}
State* EStopTest::button_reset_pressed() {
	PRINT_STATE;
	return nullptr;
}

State* EStopTest::button_reset_released() {
	PRINT_STATE;
	return nullptr;
}

//COM------------------------------
State* EStopTest::com_button_reset_pressed() {
	PRINT_STATE;
	return nullptr;
}

State* EStopTest::com_button_estop_pressed() {
	PRINT_STATE;
	return nullptr;
}

State* EStopTest::com_button_estop_released() {
	PRINT_STATE;
	return nullptr;
}

