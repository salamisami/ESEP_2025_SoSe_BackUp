#include "Stopwatch.h"

//================================================= constructors & destructors =================================================


//===================================================== public functions =====================================================
void Stopwatch::start() {
    mtx.lock();
    if(is_running) {
        mtx.unlock();
        DEBUG("Warning: Stopwatch is already running!");
        return;
    }
    if(is_reset) {
        // Fresh start (reset was called)
        start_time = std::chrono::steady_clock::now();
        accumulated_time = std::chrono::milliseconds(0);
        is_reset = false;
    } else if(!is_running) {
        // Resume from paused state
        start_time = std::chrono::steady_clock::now();
    }
    is_running = true;
    mtx.unlock();
}

long Stopwatch::peek_time() {
    mtx.lock();
    if(!is_running) {
        mtx.unlock();
        return accumulated_time.count();
    }
    auto current_time = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time);
    long total_time = (accumulated_time + elapsed).count();
    mtx.unlock();
    return total_time;
}

long Stopwatch::stop() {
    mtx.lock();
    if(!is_running) {
        mtx.unlock();
        return accumulated_time.count();
    }
    auto end_time = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    accumulated_time += elapsed;
    is_running = false;
    mtx.unlock();
    return accumulated_time.count();
}

void Stopwatch::reset() {
    mtx.lock();
    is_running = false;
    is_reset = true;
    accumulated_time = std::chrono::milliseconds(0);
    mtx.unlock();
}