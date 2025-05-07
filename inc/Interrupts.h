#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include <thread>
#include <vector>

#pragma once

class Interrupts {
public:
    Interrupts(int connectionID);
    virtual ~Interrupts();
    

    
    

private:
    int channelID, internalConID, externalConID;
    bool receivingRunning = false;
    int interruptID;
    std::thread* receivingThread;
    uintptr_t gpio_bank_0;
    std::vector<uint8_t> pinsList;
    uint32_t inputPins;

    void receivingRoutine(int channelID);
    void handleInterrupt(void);
    void startReceiving();
    //uint32_t bitToRegister(int bit);
    int registerToBit(uint32_t inputRegister);
    uint32_t definePins();
   
    
};

#endif