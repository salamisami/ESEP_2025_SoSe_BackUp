/*
 * Recorder.h
 *
 *  Created on: 24.06.2025
 *      Author: robin
 */

#ifndef SRC_RECORDERREPLAY_RECORDER_H_
#define SRC_RECORDERREPLAY_RECORDER_H_

#include "Thread_COM.h"
#include "Event.h"
#include "Macros.h"
#include "QNet.h"
#include "PulseMsg.h"

#include <vector>
#include <time.h> // für timer_t
#include <queue>
#include <mutex>
#include <condition_variable>
#include <unistd.h>
#include <sys/dispatch.h>
#include <fstream>
#include <thread>
#include <chrono>
#include <iostream>
#include <atomic>
#include <fstream>
#include <sstream>
#include <sys/neutrino.h>
#include <cstring> // für memset

#define RECORDER_CSV "ESEP-Team-1-1_25/events.csv"

class Recorder {
public: //============================================ contructors & destructors ============================================

	Recorder(I_Receiver* local_receiver, I_Sender* local_sender);
	virtual ~Recorder();


	public: //================================================ public functions ================================================

	void start_record();   // Startet das Recording
	void stop_record();    // Stoppt das Recording

	void start_replay();
	void stop_replay();


	private: //================================================ private variables ================================================
		struct EventEntry {
			long long ms;
			int code;
			int value;
		};

		struct ReplayEvent {
		    uint64_t ms;
		    int code;
		    int value;
		    timer_t timerid;
		};

		I_Receiver* local_receiver;
		I_Sender* local_sender;

		std::thread receiver_thread;
		std::thread writer_thread;
		std::thread RecReplay_thread;

	    std::ofstream file;

		bool record_running;
		bool replay_running;
		bool running;
		std::chrono::system_clock::time_point start_time;
		//const std::string filename = "tmp/ESEP-Team-1-1_25/events.csv";

		std::queue<EventEntry> event_queue;
		std::mutex queue_mutex;
		std::condition_variable queue_cv;

		std::vector<ReplayEvent> replay_events;



	private: //================================================ private functions ================================================

		void init();
		void threadFunction();
		void receiver_loop();
		void writer_loop();

	};


#endif /* SRC_RECORDERREPLAY_RECORDER_H_ */

