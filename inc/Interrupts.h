#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include <thread>
#include <vector>

#pragma once

//GPIO_0 - Sensors pin mapping
#define LASER_FRONT_BIT     2
#define LASER_SORTING_BIT   5
#define LASER_METAL_BIT     7
#define SORTING_STATUS_BIT  14
#define LASER_RAMP_BIT      15
#define LASER_BACK_BIT      20
#define BUTTON_START_BIT    22
#define BUTTON_STOP_BIT     23
#define BUTTON_RESET_BIT    26
#define BUTTON_ESTOP_BIT    27

class Interrupts {
public:
    Interrupts(int connectionID);
    virtual ~Interrupts();
    

    
    

private:
    int channelID, internalConID, externalConID;
    bool receivingRunning = false;
    int interruptID;
    int last_causing_pin = 0;
    int last_pin_status = 0;
    std::thread* receivingThread;
    uintptr_t gpio_bank_0;
    std::vector<uint8_t> pinsList;
    uint32_t inputPins;

    void receivingRoutine(int channelID);
    void handleInterrupt(void);
    void startReceiving();
    //uint32_t bitToRegister(int bit);
    int registerToBit(uint32_t inputRegister);
   
    
};

#endif