#include "Interrupts.h"

#include <stdio.h>
#include <stdexcept>
#include <errno.h>
#include <sys/neutrino.h>
#include <sys/procmgr.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>
#include <vector>
//
//#include "simqnxgpioapi.h"
//#include "simqnxirqapi.h"
#include <sys/mman.h>
#include <hw/inout.h>



/* Interrupt numbers  (spruh73l.pdf S.465 ff.) */
#define INTR_GPIO_0 97
#define INTR_GPIO_1 99
#define INTR_GPIO_2 33

/* GPIO port addresses (spruh73l.pdf S.177 ff.) */
//(for memory map)
#define GPIO_0 0x44E07000
#define GPIO_1 0x4804C000
#define GPIO_2 0x481AC000

/* GPIO port registers length */
#define GPIO_MMAP_SIZE 0x1000

/* GPIO register offsets (spruh73l.pdf S.4877) */
#define GPIO_LEVELDETECT0 0x140
#define GPIO_LEVELDETECT1 0x144
#define GPIO_RISINGDETECT 0x148
#define GPIO_FALLINGDETECT 0x14C
#define GPIO_IRQSTATUS_0 0x2C
#define GPIO_IRQSTATUS_1 0x30
#define GPIO_IRQSTATUS_SET_0 0x34
#define GPIO_IRQSTATUS_SET_1 0x38
#define GPIO_DATAIN 0x138
#define GPIO_SETDATAOUT 0x194

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


/* Helper macros */
//#define BIT_MASK(x) (0x1 << (x)) //or (x << 1)


/* My pulse codes */
#define PULSE_STOP_THREAD _PULSE_CODE_MINAVAIL + 1
#define PULSE_INTR_ON_PORT0 _PULSE_CODE_MINAVAIL + 2

using namespace std;

//===================== contructors & destructors =====================
Interrupts::Interrupts(int connectionID)
	:externalConID(connectionID)
	, gpio_bank_0(mmap_device_io(GPIO_MMAP_SIZE, GPIO_0)) {

	pinsList.push_back(LASER_FRONT_BIT);
	pinsList.push_back(LASER_SORTING_BIT);
	pinsList.push_back(LASER_METAL_BIT);
	pinsList.push_back(SORTING_STATUS_BIT);
	pinsList.push_back(LASER_RAMP_BIT);
	pinsList.push_back(LASER_BACK_BIT);
	pinsList.push_back(BUTTON_START_BIT);
	pinsList.push_back(BUTTON_STOP_BIT);
	pinsList.push_back(BUTTON_RESET_BIT);
	pinsList.push_back(BUTTON_ESTOP_BIT);

	inputPins = (1 << LASER_FRONT_BIT)
	| (1 << LASER_SORTING_BIT)
	| (1 << LASER_METAL_BIT)
	| (1 << SORTING_STATUS_BIT)
	| (1 << LASER_RAMP_BIT)
	| (1 << LASER_BACK_BIT)
	| (1 << BUTTON_START_BIT)
	| (1 << BUTTON_STOP_BIT)
	| (1 << BUTTON_RESET_BIT)
	| (1 << BUTTON_ESTOP_BIT);

	ThreadCtl(_NTO_TCTL_IO, 0);	//Request IO privileges for process.
	// Request interrupt and IO abilities.
	int procmgr_status = procmgr_ability(
		0,
		PROCMGR_ADN_ROOT | PROCMGR_AOP_ALLOW | PROCMGR_AID_INTERRUPT,
		PROCMGR_ADN_NONROOT | PROCMGR_AOP_ALLOW | PROCMGR_AID_INTERRUPT,
		PROCMGR_ADN_ROOT | PROCMGR_AOP_ALLOW | PROCMGR_AID_IO,
		PROCMGR_ADN_NONROOT | PROCMGR_AOP_ALLOW | PROCMGR_AID_IO,
		PROCMGR_AID_EOL
	);
	if(procmgr_status != EOK) {
		throw std::runtime_error("Requested abilities failed or denied!");
	}
	InterruptEnable(); //Enables interrupts.
	channelID = ChannelCreate(0);//Create channel to receive interrupt pulse messages.
	if(channelID < 0) {
		throw std::runtime_error("Could not create a channel!\n");
	}
	internalConID = ConnectAttach(0, 0, channelID, _NTO_SIDE_CHANNEL, 0); //Connect to channel.
	if(internalConID < 0) {
		throw std::runtime_error("Could not connect to channel!");
	}
	//Register interrupts by OS.
	struct sigevent interrupt_event;
	SIGEV_PULSE_INIT(&interrupt_event, internalConID, SIGEV_PULSE_PRIO_INHERIT, PULSE_INTR_ON_PORT0, 0);
	interruptID = InterruptAttachEvent(INTR_GPIO_0, &interrupt_event, 0);
	if(interruptID < 0) {
		throw std::runtime_error("Interrupt was not able to be attached!");
	}

	for(auto pin : pinsList){
		out32((uintptr_t) gpio_bank_0 + GPIO_IRQSTATUS_SET_1, (1 << pin));
	}

	// Set irq event types.
	uint32_t currentConfig;

	//	(for rising edge detection)
	currentConfig = in32((uintptr_t) (gpio_bank_0 + GPIO_RISINGDETECT));//Read current config.
	currentConfig |= inputPins;//Add desired pins.
	out32((uintptr_t) (gpio_bank_0 + GPIO_RISINGDETECT), currentConfig);			//Write new config back.

	// 	(for falling edge detection)
	currentConfig = in32((uintptr_t) (gpio_bank_0 + GPIO_FALLINGDETECT));			//Read current config.
	currentConfig |= inputPins;//Add desired pins.
	out32((uintptr_t) (gpio_bank_0 + GPIO_FALLINGDETECT), currentConfig);			//Write new config back.


	this->startReceiving();
}

//cleanup
Interrupts::~Interrupts() {
	// Detach interrupts.
	int intr_detach_status = InterruptDetach(interruptID);
	if(intr_detach_status != EOK) {
		throw std::runtime_error("Detaching interrupt failed!");
	}
	// Stop receiving thread.
	MsgSendPulse(internalConID, -1, PULSE_STOP_THREAD, 0); //using prio of calling thread.
	receivingThread->join();

	// Reset registers.
		// ONLY IF YOUR THE ONLY PROGRAM WITH INTERRUPTS RUNNING ON THIS MACHINE!

	// Close channel
	int detach_status = ConnectDetach(internalConID);
	if(detach_status != EOK) {
		throw std::runtime_error("Detaching channel failed!");
	}

	int destroy_status = ChannelDestroy(channelID);
	if(destroy_status != EOK) {
		throw std::runtime_error("Destroying channel failed!");
	}
	InterruptDisable();
}

//========================= private functions =========================

// uint32_t Interrupts::bitToRegister(int bit) {
// 	if(bit < 0) {
// 		throw std::runtime_error(std::string(__FUNCTION__) + "bit cannot less than 0");
// 	}
// 	return (1 << bit);
// }
int Interrupts::registerToBit(uint32_t inputRegister) {
	if(inputRegister > 0 && (inputRegister & (inputRegister - 1)) != 0) {
		throw std::runtime_error(std::string(__FUNCTION__) + "Cannot convert register to bit offset, value is not a power of 2");
	}
	double value = std::log2(inputRegister);
	return (int) value;
}

void Interrupts::receivingRoutine(int channelID) {
	ThreadCtl(_NTO_TCTL_IO, 0);	//Request IO privileges
	_pulse msg;
	receivingRunning = true;
	printf("Message thread started.\n");
	while(receivingRunning) {
		int recvid = MsgReceivePulse(channelID, &msg, sizeof(_pulse), nullptr);
		if(recvid < 0) {
			throw std::runtime_error("MsgReceivePulse failed!");
		}
		if(recvid == 0) {	//pulse received.
			//Stop thread while it blocks.
			if(msg.code == PULSE_STOP_THREAD) {
				printf("Thread kill code received!\n");
				receivingRunning = false;
			}
			if(msg.code == PULSE_INTR_ON_PORT0) {
				handleInterrupt();
			}
			// Do not ignore OS pulses!
		}
	}
	printf("Message thread stops...\n");
}



void Interrupts::handleInterrupt(void) {
	//uintptr_t gpioBase = mmap_device_io(GPIO_MMAP_SIZE, GPIO_0);

	uint32_t intrStatusReg = in32(uintptr_t(gpio_bank_0 + GPIO_IRQSTATUS_1));
	//std::cout << "Interrupt Status Register: " << std::bitset<32>(intrStatusReg) << std::endl;

	out32(uintptr_t(gpio_bank_0 + GPIO_IRQSTATUS_1), 0xffffffff);	//clear all interrupts.
	InterruptUnmask(INTR_GPIO_0, interruptID);				//unmask interrupt.

	int causing_pin = registerToBit(intrStatusReg);
	int pin_status = (in32((uintptr_t) gpio_bank_0 + GPIO_DATAIN) >> causing_pin) & 0x1;
	std::printf("Interrupt on pin %d, status: %d\n", causing_pin, pin_status);

	//TODO
	//MsgSendPulse(externalConID,5,code,value);
}


//========================= public functions =========================

void Interrupts::startReceiving() {
	receivingThread = new thread(&Interrupts::receivingRoutine, this, channelID);

}