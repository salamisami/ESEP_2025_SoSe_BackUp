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
    //TODO calling this twice will not create 2 separate threads
    if(timerThread.joinable()) {
        timerThread.join();
    }
    DEBUG("Creating new timer thread");
    timerThread = std::thread(&Timer::threadFunction, this, miliseconds, id);
}

void Timer::threadFunction(int miliseconds, int id) {
    DEBUG("Timer Started...");
    WAIT(1000);
    DEBUG("Sending event....");
    sender->send_event((int) Topic::TIMER, id, (int) EventPriority::SECOND_PRIO);
    DEBUG("Timer ended...");
}