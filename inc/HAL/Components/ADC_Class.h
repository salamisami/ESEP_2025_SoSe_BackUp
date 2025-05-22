#ifndef ADC_CLASS_H
#define ADC_CLASS_H
#pragma once

#include "ADC_Utilities.h"
#include "Macros.h"
#include "Event.h"
#include "Thread_COM.h"
#include "Mailbox.h"

#include <thread>
#include <iostream>
#include <unistd.h>
#include <sys/dispatch.h>

class ADC_Class {
public: //============================================ contructors & destructors ============================================
	/**
	 * @brief Creates a constructor with rcvid and mailbox as parameters
	 * @param dispatcher_rcvid id used to send events to dispatcher
	 * @param mailbox a name_attach_t* connection, used to receive events
	 */
    ADC_Class(int dispatcher_rcvid,  Mailbox<_pulse>* mailbox);
    virtual ~ADC_Class();
	

public: //================================================ public functions ================================================
	//void publicFunction();
    void eventLoop();
    


private: //================================================ private variables ================================================
    //classes, STL containers, and structs
    std::thread ADCThread;

    TSCADC tscadc;
    ADC adc;

    Mailbox<_pulse>* mailbox;
    int dispatcher_rcvid;
    float bandVoltage;
    bool running;
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
    //float bandVoltage();
    void clibrate();
    void messureClassfySend();
	
};

#endif
