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
    ADC_Class(Mailbox<_pulse>* mailbox, I_Sender* sender);
    virtual ~ADC_Class();
	

public: //================================================ public functions ================================================
	//void publicFunction();
    void eventLoop();
    


private: //================================================ private variables ================================================
    //classes, STL containers, and structs
    TSCADC tscadc;
    ADC adc;

    //pointers
    std::thread ADCThread;
    I_Sender* sender;
    Mailbox<_pulse>* mailbox;

    //primitive Types
    float bandVoltage;
    bool running;
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
    //float bandVoltage();
    void clibrate();
    void messureClassfySend();
	
};

#endif
