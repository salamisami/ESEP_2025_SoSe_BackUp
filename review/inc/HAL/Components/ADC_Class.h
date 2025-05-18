#ifndef ADC_CLASS_H
#define ADC_CLASS_H
#pragma once

#include "ADC_Utilities.h"
#include <sys/dispatch.h>

class ADC_Class {
public: //============================================ contructors & destructors ============================================
	/**
	 * @brief Creates a constructor with rcvid and mailbox as parameters
	 * @param dispatcher_rcvid id used to send events to dispatcher
	 * @param mailbox a name_attach_t* connection, used to receive events
	 */
    ADC_Class(int dispatcher_rcvid, name_attach_t* mailbox);
    virtual ~ADC_Class();
	

public: //================================================ public functions ================================================
	//void publicFunction();
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif