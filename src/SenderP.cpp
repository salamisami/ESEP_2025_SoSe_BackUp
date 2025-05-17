#include "SenderP.h"

using namespace PM;
//================================================= contructors & destructors =================================================
Sender::Sender(int channelID) {
    connectionID = ConnectAttach(0,0,channelID,_NTO_SIDE_CHANNEL,0);
    if(connectionID < 0){
        THROW("Error creating sender");
    }
}

Sender::~Sender() {
    int detach_status = ConnectDetach(connectionID);
    if(detach_status < 0) {
        THROW("Error destroying sender");
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
