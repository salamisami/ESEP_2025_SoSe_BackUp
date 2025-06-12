#include "Stopwatch.h"

//================================================= contructors & destructors =================================================


//===================================================== private functions =====================================================

//void Stopwatch::privateFunction(){}

//===================================================== public functions =====================================================

void Stopwatch::start() {
    mtx.lock();
    start_time = std::chrono::steady_clock::now();
    is_running = true;
    mtx.unlock();
}

long Stopwatch::stop() {
    mtx.lock();
    if(!is_running) {
        mtx.unlock();
        THROW("Stopwatch was never started!");
    }
    auto end_time = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    is_running = false;
    mtx.unlock();
    return duration.count();
}