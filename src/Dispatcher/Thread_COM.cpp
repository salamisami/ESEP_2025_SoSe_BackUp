#include "Thread_COM.h"

//================================================= contructors & destructors =================================================


//===================================================== private functions =====================================================

//void Thread_COM::privateFunction(){}

//===================================================== public functions =====================================================

//void Thread_COM::publicFunction(){}
void Thread_COM::send_event(int rcvid, int8_t event_code, int event_value, int priority) {
}

_pulse Thread_COM::receive_event(name_attach_t connection) {
    return _pulse();
}

void Thread_COM::setup_thread_communication(const char* gns_name, name_attach_t* connection, int* rcvid) {
}