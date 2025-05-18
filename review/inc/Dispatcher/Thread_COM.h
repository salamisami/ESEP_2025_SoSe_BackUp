#ifndef THREAD_COM_H
#define THREAD_COM_H
#pragma once

#include <stdint.h>
#include <sys/dispatch.h>

class Thread_COM {
public: //============================================ contructors & destructors ============================================
	Thread_COM() = delete;
	Thread_COM(const Thread_COM&) = delete;
	Thread_COM& operator = (const Thread_COM&) = delete;
	virtual ~Thread_COM() = delete;
	

public: //================================================ public functions ================================================
	static void send_event(int rcvid, int8_t event_code, int event_value, int priority = SIGEV_PULSE_PRIO_INHERIT);
	static _pulse receive_event(name_attach_t connection);
	static void setup_thread_communication(const char* gns_name, name_attach_t* connection, int* rcvid);

    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction();
	
};

#endif