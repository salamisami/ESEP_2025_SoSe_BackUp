#ifndef MOCK_PM_H
#define MOCK_PM_H
#pragma once

#include "QNet.h"
#include "ThreadSafeQueue.h"



union sigval {
	int   sival_int;
	void* sival_ptr;
};

typedef struct {
	int8_t code;
	union sigval value;
} _pulse;


namespace Mock_PM {
	class Receiver : public I_Receiver {
	public:
		Receiver();
		virtual ~Receiver();

	public:
		int receive_event(_pulse* event) override;
		int getchid() override;
		ThreadSafeQueue<_pulse>* getQueue();

	private:
		ThreadSafeQueue<_pulse> queue;

	};

	class Sender : public I_Sender {
	public:
		Sender(Receiver* receiver);
		Sender() = default;
		virtual ~Sender();

	public:
		void send_event(int8_t event_code, int event_value, int priority = 0) override;
		int getcoid() override;
	private:
		ThreadSafeQueue<_pulse>* queue;
	};
}


#endif