#include "Timer.h"

//================================================= contructors & destructors =================================================
Timer::Timer(I_Sender* sender) {
    this->sender = sender;
}

Timer::~Timer() {
    if(timerThread.joinable()) {
        timerThread.join();
    }
}

//===================================================== private functions =====================================================

//void Timer::privateFunction(){}

//===================================================== public functions =====================================================

void Timer::setTimer(int miliseconds, int id) {
    if(timerThread.joinable()){
        timerThread.join();
    }
    //TODO @Lucas please edit here
    timerThread = std::thread(&Timer::threadFunction, this, miliseconds, id);
}

void Timer::threadFunction(int miliseconds, int id) {
    DEBUG("Timer Started...");
    WAIT(1000);
    DEBUG("Sending event....");
    sender->send_event((int) Topic::TIMER, id, (int) EventPriority::SECOND_PRIO);
    std::cout << "Timer for " << miliseconds << " ist abgelaufen" << std::endl;
}