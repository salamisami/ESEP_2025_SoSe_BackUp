#include "Sender.h"

using namespace QNet;
//================================================= contructors & destructors =================================================
Sender::Sender(const std::string receiver_name) {
    connectionID = name_open(receiver_name.c_str(), NAME_FLAG_ATTACH_GLOBAL);
    if(connectionID < 0) {
        THROW("GNS-Sender failed to create!");
    }
}

Sender::~Sender() {
    int detach_status = name_close(connectionID);
    if(detach_status < 0) {
        THROW("GNS-Sender failed to close!");
    }
}

//===================================================== private functions =====================================================

//void Sender::privateFunction(){}

//===================================================== public functions =====================================================

void Sender::send(int8_t code, int value, int priority){
    int status = MsgSendPulse(connectionID, priority,code, value);
    if(status < 0 ){
        THROW("Send pulse message failed.");
    }
}

int Sender::getConnectionID(){
    return connectionID;
}