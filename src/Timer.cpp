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

void Timer::start_timer(int miliseconds, TIMER_ID id) {
    //TODO @Lucas please edit here
    timerThread = std::thread(&Timer::threadFunction, this, miliseconds, id);
    timerThread.detach();
}

void Timer::threadFunction(int miliseconds, TIMER_ID id) {
    WAIT(miliseconds);
    sender->send_event((int) Topic::TIMER, (int) id, (int) EventPriority::SECOND_PRIO);
}