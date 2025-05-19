#include "Thread_COM.h"

//================================================= contructors & destructors =================================================


//===================================================== private functions =====================================================

//void Thread_COM::privateFunction(){}

//===================================================== public functions =====================================================

//void Thread_COM::publicFunction(){}
void Thread_COM::send_event(int rcvid, int8_t event_code, int event_value, int priority) {
    int status = MsgSendPulse(rcvid, priority, event_code, event_value);
    if(status < 0) {
        THROW("Cannot send pulse message");
    }
}

int Thread_COM::receive_event(name_attach_t connection, _pulse* event) {
    int status = MsgReceivePulse(connection.chid, event, sizeof(_pulse), nullptr);
    if(status < 0) {
        THROW("Cannot receive pulse message");
    }
    return 0;
}

int Thread_COM::setup_thread_communication(const char* gns_name, name_attach_t* connection, int* rcvid) {
    int chid = ChannelCreate(0);
    if(chid < 0) {
        THROW("Cannot create Channel");
    }
    connection->chid = chid;
    int coid = ConnectAttach(0, 0, chid, _NTO_SIDE_CHANNEL, 0);
    if(coid < 0) {
        THROW("Cannot attach to a channel");
    }
    *rcvid = coid;
    return 0;
}