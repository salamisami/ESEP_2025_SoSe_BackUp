#include "ReceiverP.h"

using namespace PM;
//================================================= contructors & destructors =================================================
Receiver::Receiver() {
    channelID = ChannelCreate(0);
    if(channelID < 0) {
        THROW("Failed to create Receiver");
    }

}

Receiver::~Receiver() {
    int status = ChannelDestroy(channelID);
    if(status < 0) {
        THROW("GNS-Receiver failed to clean");
    }
}

//===================================================== private functions =====================================================

//void Receiver::privateFunction(){}

//===================================================== public functions =====================================================

_pulse Receiver::receive() {
    _pulse pulse;
    int status = MsgReceivePulse(channelID, &pulse, sizeof(pulse), nullptr);
    if(status < 0) {
        THROW("Receive pulse message failed");
    }
    return pulse;
}

int Receiver::getChannelID(){
    return channelID;
}