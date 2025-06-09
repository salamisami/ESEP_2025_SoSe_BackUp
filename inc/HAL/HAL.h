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
	/**
	 * @brief creates a hal without connection. Use this for test purposes
	 */
	HAL();

	/**
	 * @brief creates a hal with connection. The connection can be mocked, qnet, or gns. (Because they are all using the same interface).
	 * 
	 * The HAL will send an initial event during initialization, whether the machine has a pusher or a switch gate.
	 * Additionally, if the estop is pressed during initialization, it will prevent moving parts from moving, and send an estop event using @param local_sender
	 * 
	 * @param local_receiver pointer to receiver, used by HAL to receive events
	 * @param local_sender pointer so sender, used by HAL to send events. HAL will use this @param local_sender to send a confirmation, whether it is a switch or a pusher.
	 */
	HAL(I_Receiver* local_receiver, I_Sender* local_sender);
	virtual ~HAL();


public: //================================================ public functions ================================================
	/**
	 * @brief Tests the Interrupt and Actuators. Use this without external connection is recommended
	 */
	/**
	 * @brief Tests the Interrupt and Actuators. Use this without external connection is recommended
	 */
	void test_ins();
	void test_ins_ADC();

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
