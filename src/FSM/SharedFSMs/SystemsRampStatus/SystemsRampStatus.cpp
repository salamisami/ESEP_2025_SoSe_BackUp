#include "SystemsRampStatus.h"




//================================================= constructors & destructors =================================================
SystemsRampStatus::SystemsRampStatus(ContextData* data) : HState(data, new NoRampFull(data)) {
    //substate = new SubState(data);
}

SystemsRampStatus::~SystemsRampStatus() {}

//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
void SystemsRampStatus::entry(){
	PRINT_STATE;
    
    HState::entry();
}

void SystemsRampStatus::exit(){
    HState::exit();
    
	PRINT_STATE;
}