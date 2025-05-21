#include "Timer.h"

//================================================= contructors & destructors =================================================
Timer::Timer(int feedbackConnectionID) : coid(feedbackConnectionID) {

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
    int status = MsgSendPulse(coid, (int) EventPriority::SECOND_PRIO, (int) Topic::TIMER, id);
    if(status < 0) {
        THROW("Cannot set up a timer");
    }
}