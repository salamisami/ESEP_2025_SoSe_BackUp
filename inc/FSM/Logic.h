#ifndef LOGIC_H
#define LOGIC_H
#pragma once

#include "QNet.h"
#include "Context.h"
#include "Boot.h"
#include "Event.h"


#include "Mock_PM.h"
#include <pthread.h>
#include <thread>

void set_thread_priority(pthread_t thread, int priority) {
    struct sched_param param;
    param.sched_priority = priority;

    // Set FIFO scheduling policy with specified priority
    if (pthread_setschedparam(thread, SCHED_FIFO, &param) != 0) {
        std::cerr << "Failed to set logic thread priority: " << std::endl;
    }

    // Optional: Set thread CPU affinity
    // cpu_set_t cpuset;
    // CPU_ZERO(&cpuset);
    // CPU_SET(0, &cpuset);  // Pin to CPU 0
    // pthread_setaffinity_np(thread, sizeof(cpu_set_t), &cpuset);
}

template <typename InitialState>
class Logic {
public: //============================================ constructors & destructors ============================================
    /**
     * @brief Same as above, but the context data can be injected
     * @param local_sender sender to send events out
     * @param data context data to be injected
     */
    Logic(I_Receiver* local_receiver, I_Sender* local_sender, ContextData* input_data);

    /**
    * @brief This constructor is used, if the dispatcher is broadcast type. The context will use the same sender to send events out and to self
    * @param sender to send events out AND to self
    */
    Logic(I_Receiver* local_receiver, I_Sender* local_sender);
    virtual ~Logic();

public: //================================================ public functions ================================================
    std::string show_state();

private: //================================================ private variables ================================================
    //classes, STL containers, and structs
    std::thread logicThread;
    //pointers
    I_Receiver* local_receiver;
    I_Sender* local_sender;
    ContextData* data;
    Context<InitialState>* fsm;
    //primitive types
    //bool and char
    bool logicRunning;
    bool contextInjected = false;

private: //================================================ private functions ================================================
    void init();
    void threadFunction();
};

//================================================= constructors & destructors =================================================


template <typename InitialState>
Logic<InitialState>::Logic(I_Receiver* local_receiver, I_Sender* local_sender, ContextData* input_data)
    : local_receiver(local_receiver)
    , local_sender(local_sender)
    , data(input_data) {
    fsm = new Context<InitialState>(data);
    logicRunning = true;
    contextInjected = true;
    logicThread = std::thread(&Logic::threadFunction, this);
}

template <typename InitialState>
Logic<InitialState>::Logic(I_Receiver* local_receiver, I_Sender* local_sender)
    : local_receiver(local_receiver)
    , local_sender(local_sender){
    init();
}

template <typename InitialState>
void Logic<InitialState>::init() {
    data = new ContextData(local_sender);
    fsm = new Context<InitialState>(data);
    logicRunning = true;
    logicThread = std::thread(&Logic::threadFunction, this);
    set_thread_priority(logicThread.native_handle(), 250);  // Higher priority for main thread
}




template <typename InitialState>
Logic<InitialState>::~Logic() {
    logicRunning = false;
    if(logicThread.joinable()) {
        logicThread.join();
    }
    delete fsm;
    if(!contextInjected){
        delete data;
    }
}

//===================================================== private functions =====================================================
template <typename InitialState>
void Logic<InitialState>::threadFunction() {
    DEBUG("Logic thread is running");
    int eventNo = 0;
    while(logicRunning) {
        _pulse event;
        int status = local_receiver->receive_event(&event);
       ;
        if(status == 0) {
            eventNo++;
            int8_t topic = event.code;
            if(topic == (int8_t) Topic::STOP_THREAD) {
                logicRunning = false;
            }
            fsm->handleEvent(event);
        }
    }
}

//===================================================== public functions =====================================================
template <typename InitialState>
std::string Logic<InitialState>::show_state() {
    return fsm->show_state();
}

#endif // LOGIC_H