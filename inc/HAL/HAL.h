#ifndef HAL_H
#define HAL_H
#pragma once


#include "Actuator.h"
#include "Interrupt.h"
#include "ADC_Class.h"
#include "PulseMsg.h"
#include "QNet.h"
#include "Mailbox.h"



class HAL {
public: //============================================ contructors & destructors ============================================
	HAL();
	HAL(I_Receiver* local_receiver, I_Sender* local_sender);
	virtual ~HAL();


public: //================================================ public functions ================================================
	void test_ins();

private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	std::thread halThread;
	//mock here
	PulseMsg::Receiver* mock_dispatcher_receiver;
	PulseMsg::Sender* mock_dispatcher_sender;

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
	bool detached;



private: //================================================ private functions ================================================
void init();
	void threadFunction();

};

#endif