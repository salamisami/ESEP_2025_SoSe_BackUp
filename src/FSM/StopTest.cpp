#include "StopTest.h"

//================================================= constructors & destructors =================================================
StopTest::StopTest(ContextData* data) : State(data) {
    //substate = new SubState(data);
}

StopTest::~StopTest() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void StopTest::entry(){
	PRINT_STATE;
}

void StopTest::exit(){
	PRINT_STATE;
}