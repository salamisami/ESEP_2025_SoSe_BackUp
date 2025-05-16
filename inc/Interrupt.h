#ifndef INTERRUPT_H
#define INTERRUPT_H
#pragma once

#include "Throw.h"
#include "Event.h"
#include "Sender.h"

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#include <stdexcept>

#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>
#include <vector>

#include <sys/mman.h>
#include <sys/dispatch.h>
#include <sys/types.h>
#include <sys/neutrino.h>
#include <sys/procmgr.h>
#include <hw/inout.h>
#include <sched.h>



class Interrupt {
public: //============================================ contructors & destructors ============================================
    Interrupt(const std::string destination);
    //Interrupt();
    virtual ~Interrupt();


public: //================================================ public functions ================================================



private: //================================================ private variables ================================================
    //classes, STL containers, and structs
    std::vector<uint8_t> pinsList;
    //pointers
    std::thread* interruptThread;
    uintptr_t gpio_bank_0;
    QNet::Sender* sender;
    //primitive types
    uint32_t inputPins;
    int interruptID;
    int internalConnectionID;
    int internalChannelID;
    //bool and char
    int last_causing_pin;
    bool test_mode;
    int last_pin_status;
    volatile bool interruptRunning;



private: //================================================ private functions ================================================
    void setup_interrupts();
    void setup_internal_pulse_message();
    void clean_internal_pulse_message();
    void interruptFunction(int channelID);
    void isr(void);
    int registerToBit(uint32_t inputRegister);
    void sendEvent(int causing_pin, int pin_status);


};

#endif