#ifndef ADVANCEDTIMER_H
#define ADVANCEDTIMER_H

#include <functional>
#include <chrono>
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <utility>

class AdvancedTimer {
public:
    AdvancedTimer() : active_(false) {}

    ~AdvancedTimer() {
        stop();
    }

    // Regular function version
    void start(int milliseconds, void (*function_to_call_after_timeout)()) {
        start_impl(milliseconds, function_to_call_after_timeout);
    }

    // Member function version
    template<typename T>
    void start(int milliseconds, void (T::* member_function)(), T* object) {
        start_impl(milliseconds, [object, member_function]() {
            (object->*member_function)();
            });
    }

    // Functor/lambda version
    template<typename F>
    void start(int milliseconds, F&& function_to_call_after_timeout) {
        start_impl(milliseconds, std::forward<F>(function_to_call_after_timeout));
    }

    long stop() {
        if(!active_) {
            return -1; // AdvancedTimer wasn't running
        }

        // Calculate remaining time
        auto now = std::chrono::steady_clock::now();
        auto end_time = start_time_ + std::chrono::milliseconds(initial_duration_);
        long remaining = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - now).count();

        // Stop the AdvancedTimer
        {
            std::lock_guard<std::mutex> lock(mutex_);
            active_ = false;
            cv_.notify_one();
        }

        if(AdvancedTimer_thread_.joinable()) {
            AdvancedTimer_thread_.join();
        }

        return remaining > 0 ? remaining : 0;
    }

private:
    template<typename F>
    void start_impl(int milliseconds, F&& function_to_call_after_timeout) {
        // Stop any existing AdvancedTimer
        stop();

        // Set the active flag
        active_ = true;
        start_time_ = std::chrono::steady_clock::now();
        initial_duration_ = milliseconds;

        // Start the AdvancedTimer thread
        AdvancedTimer_thread_ = std::thread([this, milliseconds, f = std::forward<F>(function_to_call_after_timeout)]() {
            std::unique_lock<std::mutex> lock(mutex_);
            auto start_time = std::chrono::steady_clock::now();
            auto end_time = start_time + std::chrono::milliseconds(milliseconds);

            while(active_ && std::chrono::steady_clock::now() < end_time) {
                cv_.wait_until(lock, end_time);
            }

            if(active_) {
                active_ = false;
                lock.unlock(); // Unlock before calling the function
                f();
            }
            });
    }

    std::atomic<bool> active_;
    std::thread AdvancedTimer_thread_;
    std::mutex mutex_;
    std::condition_variable cv_;

    // For calculating remaining time
    std::chrono::steady_clock::time_point start_time_;
    long initial_duration_;
};

#endif