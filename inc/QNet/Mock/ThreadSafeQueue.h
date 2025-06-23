#ifndef THREADSAFEQUEUE_H
#define THREADSAFEQUEUE_H
#pragma once

#include <queue>
#include <mutex>
#include <stdexcept>
#include <condition_variable>

//#define MAX_QUEUE 100

template <typename T>
class ThreadSafeQueue {
private:
    std::queue<T> queue;
    std::mutex mtx;
    //sem_t vacant;
    std::condition_variable cv_occupied;

public:
    ThreadSafeQueue() = default;
    ~ThreadSafeQueue() {
        std::lock_guard<std::mutex> lock(mtx);
    }

    void push(const T& item) {
        //sem_wait(&vacant);
        std::lock_guard<std::mutex> lock(mtx);
        queue.push(item);
        cv_occupied.notify_one();
    }

    T pop() {
        std::unique_lock<std::mutex> lock(mtx);
        // Wait until queue is not empty
        cv_occupied.wait(lock, [this]() { return !queue.empty(); });

        T item = queue.front();
        queue.pop();
        return item;
    }

    bool isEmpty() {
        std::lock_guard<std::mutex> lock(mtx);
        bool isEmpty = queue.empty();
        return isEmpty;
    }
};


#endif