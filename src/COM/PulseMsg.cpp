#include "PulseMsg.h"

using namespace PulseMsg;
//================================================= contructors & destructors =================================================
Receiver::Receiver() {
    this->chid = ChannelCreate(0);
    if(this->chid < 0) {
        THROW("Cannot perform ChannelCreate");
    }
}
Receiver::~Receiver() {

}

Sender::Sender(){
    coid = -1;
}
Sender::Sender(int chid) {
    this->coid = ConnectAttach(0, 0, chid, _NTO_SIDE_CHANNEL, 0);
    if(this->coid < 0) {
        THROW("Cannot perform ConnectAttach");
    }
}

Sender::~Sender() {
}



//===================================================== private functions =====================================================


//===================================================== public functions =====================================================
int Receiver::receive_event(_pulse* msg) {
    int status = MsgReceivePulse(chid, msg, sizeof(_pulse), nullptr);
    return status;
}
int Receiver::getchid() {
    return chid;
}

void Sender::send_event(int8_t code, int value, int priority) {
    int status = MsgSendPulse(coid, priority, code, value);
    if (status < 0){
        THROW("Cannot perform MsgSendPulse");
    }
}

int Sender::getcoid(){
    return coid;
}