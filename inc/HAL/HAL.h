#ifndef HAL_H
#define HAL_H
#pragma once


#include "Actuator.h"
#include "Interrupt.h"
#include "ADC_Class.h"
#include "Thread_COM.h"
#include "Mailbox.h"



class HAL {
public: //============================================ contructors & destructors ============================================
	HAL(const char* gns_name, int dispatcher_rcvid = -1);
	virtual ~HAL();


public: //================================================ public functions ================================================
	int getHAL_rcvid();
	void test_ins();
	void test_ins_ADC();

private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	std::thread halThread;
	name_attach_t hal_connection;
	name_attach_t dispatcher_mock_connection;
	//pointers
	Interrupt* interrupt;
	Actuator* actuator;
	ADC_Class* adc;
	
	Mailbox<_pulse>* actuator_mailbox;
	Mailbox<_pulse>* adc_mailbox;
	//primitive types
	int hal_rcvid;
	int dispatcher_mock_rcvid;
	//bool and char
	volatile bool hal_running;



private: //================================================ private functions ================================================
	void threadFunction();

};

#endif
