#ifndef ADC_CLASS_H
#define ADC_CLASS_H
#pragma once

#include "ADC_Utilities.h"
#include "Macros.h"
#include "Event.h"
#include "Thread_COM.h"

#include <thread>
#include <iostream>
#include <unistd.h>
#include <sys/dispatch.h>
#include <mutex>

class ADC_Class {
public: //============================================ contructors & destructors ============================================
	/**
	 * @brief Creates a constructor with rcvid as parameters
	 * @param dispatcher_rcvid id used to send events to dispatcher
	 */
    ADC_Class(I_Sender* sender);
    virtual ~ADC_Class();
	

public: //================================================ public functions ================================================
    /**
     * @brief stops the ADC immediately. This function will be called, as soon as e-stop button is pressed.
     */
    void adc_estop();
    void adc_reset();

    void handle_event(_pulse event);




private: //================================================ private variables ================================================
    //classes, STL containers, and structs
    TSCADC tscadc;
    ADC adc;
    std::mutex calibrate_mtx;
    std::mutex measure_mtx;

    //pointers
    std::thread adc_thread;
    I_Sender* sender;

    //primitive Types
    float bandVoltage;
    bool adcStopped;
    bool running;
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
    void calibrate();
    void measureClassifySend();
	
};

#endif
