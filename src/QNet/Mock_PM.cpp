#include "Mock_PM.h"

using namespace Mock_PM;

//================================================= contructors & destructors =================================================
Receiver::Receiver() {
}

Receiver::~Receiver() {

}



int Mock_PM::Receiver::receive_event(_pulse* event) {
    *event = queue.pop();
    return 0;
}

int Mock_PM::Receiver::getchid() {
    return 0;
}

ThreadSafeQueue<_pulse>* Receiver::getQueue(){
    return &queue;
}

//===================================================== private functions =====================================================

//void Mock_PM::privateFunction(){}

//===================================================== public functions =====================================================

//void Mock_PM::publicFunction(){}















//================================================= contructors & destructors =================================================
Mock_PM::Sender::Sender(Receiver* receiver) {
    queue = receiver->getQueue();
}

Mock_PM::Sender::~Sender() {
}


//===================================================== public functions =====================================================
void Mock_PM::Sender::send_event(int8_t event_code, int event_value, int priority) {
    _pulse event;
    event.code = event_code;
    event.value.sival_int = event_value;
    queue->push(event);
}

int Mock_PM::Sender::getcoid() {
    return 0;
}
