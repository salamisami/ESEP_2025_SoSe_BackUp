#ifndef HAL_H
#define HAL_H
#pragma once


#include "Actuator.h"
#include "Interrupt.h"
#include "ADC_Class.h"
#include "Thread_COM.h"
#include "PulseMsg.h"
#include "Mailbox.h"



class HAL {
public: //============================================ contructors & destructors ============================================
	HAL(const char* gns_name, int dispatcher_rcvid = -1);
	virtual ~HAL();


public: //================================================ public functions ================================================
	int getHAL_rcvid();
	void test_ins();

private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	std::thread halThread;
	PulseMsg::Receiver dispatcher_mock_receiver;
	PulseMsg::Sender dispatcher_mock_sender;
	Thread_COM::Receiver receiver;
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