#ifndef THREADSAFEQUEUE_H
#define THREADSAFEQUEUE_H
#pragma once

#include <queue>
#include <mutex>
#include <semaphore.h>
#include <stdexcept>

//#define MAX_QUEUE 100

template <typename T>
class ThreadSafeQueue {
private:
    std::queue<T> queue;
    std::mutex mtx;
    //sem_t vacant;
    sem_t occupied;

public:
    ThreadSafeQueue() {
        //int initVacant = sem_init(&vacant,0, MAX_QUEUE);
        int initOccupied = sem_init(&occupied, 0, 0);

        if(initOccupied == -1) {
            throw std::runtime_error("Failed to initialize Semaphores in ThreadSafeQueue");
        }
    }
    ~ThreadSafeQueue() {
        std::lock_guard<std::mutex> lock(mtx);
        //sem_destroy(&vacant);
        sem_destroy(&occupied);
    }

    void push(const T& item) {
        //sem_wait(&vacant);
        std::lock_guard<std::mutex> lock(mtx);
        queue.push(item);
        sem_post(&occupied);
    }

    T pop() {
        sem_wait(&occupied);
        std::lock_guard<std::mutex> lock(mtx);
        T item = queue.front();
        queue.pop();
        //sem_post(&vacant);
        return item;
    }

    bool isEmpty() {
        std::lock_guard<std::mutex> lock(mtx);
        bool isEmpty = queue.empty();
        return isEmpty;
    }
};


#endif