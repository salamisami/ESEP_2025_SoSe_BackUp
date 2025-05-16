#include "Receiver.h"

using namespace QNet;
//================================================= contructors & destructors =================================================
Receiver::Receiver(const std::string name) {
    this->attach = name_attach(NULL, name.c_str(), NAME_FLAG_ATTACH_GLOBAL);
    if(this->attach == NULL) {
        THROW("GNS-Receiver failed to create");
    }

}

Receiver::~Receiver() {
    int status = name_detach(attach, 0);
    if(status < 0) {
        THROW("GNS-Receiver failed to clean");
    }
}

//===================================================== private functions =====================================================

//void Receiver::privateFunction(){}

//===================================================== public functions =====================================================

_pulse Receiver::receive(){
    _pulse pulse;
    int status = MsgReceivePulse(attach->chid, &pulse,sizeof(pulse), nullptr);
    if(status < 0){
        THROW("Receive pulse message failed");
    }
    return pulse;
}