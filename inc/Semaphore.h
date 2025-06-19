#ifndef SEMAPHORE_H
#define SEMAPHORE_H
#pragma once

#include <mutex>
#include <condition_variable>

class Semaphore {
public:
    // Constructor with initial count
    explicit Semaphore(unsigned int count = 0);
    virtual ~Semaphore() = default;

    // Increment the semaphore and notify one waiting thread
    void notify();

    // Decrement the semaphore, blocking if count is zero
    void wait();

    // Try to decrement the semaphore without blocking
    // Returns true if successful, false otherwise
    bool try_wait();

    // Get the current count (mostly useful for debugging)
    unsigned int get_count();

private:
    std::mutex mutex_;
    std::condition_variable cv_;
    unsigned int count_;
};

#endif
