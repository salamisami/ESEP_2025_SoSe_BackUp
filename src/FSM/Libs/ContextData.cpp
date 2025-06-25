#include "ContextData.h"
#include "HState.h"

//================================================= constructors & destructors =================================================
ContextData::ContextData(){}
ContextData::ContextData(I_Sender* sender, I_Sender* to_self_sender) {
    this->sender = sender;
    stateStack = new std::stack<State*>();
    timer = new Timer(to_self_sender);
    //TODO check for config
}

bool ContextData::check_config(){
	return(access (this->config_path.c_str(), F_OK) != -1);
}

ContextData::~ContextData() {
    delete timer;
    delete stateStack;
}

//===================================================== private functions =====================================================

//void ContextData::privateFunction(){}

//===================================================== public functions =====================================================

//void ContextData::publicFunction(){}
