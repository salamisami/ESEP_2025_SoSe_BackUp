#include "Timer.h"

//================================================= contructors & destructors =================================================
Timer::Timer(I_Sender* sender)  {
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
    timerThread = std::thread(&Timer::threadFunction, this, miliseconds, id);
}

void Timer::threadFunction(int miliseconds, int id) {
    WAIT(miliseconds);
    sender->send_event((int) Topic::TIMER, id, (int) EventPriority::SECOND_PRIO);
}