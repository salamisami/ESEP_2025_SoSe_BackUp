#ifndef HAL_H
#define HAL_H
#pragma once


#include "Actuator.h"
#include "Interrupt.h"
#include "ADC_Class.h"
#include "Thread_COM.h"
#include "PulseMsg.h"
#include "QNet.h"
#include "Mailbox.h"



class HAL {
public: //============================================ contructors & destructors ============================================
	HAL();
	HAL(const char* local_gns_name, const char* target_gns_name);
	virtual ~HAL();


public: //================================================ public functions ================================================
	void test_ins();

private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	std::thread halThread;
	//mock here
	PulseMsg::Receiver mock_dispatcher_receiver;
	PulseMsg::Sender mock_dispatcher_sender;

	I_Receiver* local_receiver;
	I_Sender* local_sender;

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
void init();
	void threadFunction();

};

#endif