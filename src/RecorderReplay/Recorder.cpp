/*
 * Recorder.cpp
 *
 *  Created on: 24.06.2025
 *      Author: robin
 */

#include "Recorder.h"

    Recorder::Recorder(I_Receiver* local_receiver, I_Sender* local_sender){
		this->local_receiver = local_receiver;
		this->local_sender = local_sender;
		running = true;
		record_running = false;
		replay_running = false;
		init();
    }
    Recorder::~Recorder() {
    	stop_record();
    	//stop_replay();
    }

    void Recorder::init() {
    	start_time = std::chrono::system_clock::now();
        // Datei anlegen (ggf. vorhandene Datei überschreiben)
    	//mkdir("tmp/ESEP-Team-1-1_25", 0777);
        file.open(RECORDER_CSV, std::ios::out);
        if (!file.is_open()) {
        	THROW("Recorder: Datei konnte nicht geöffnet werden!");
        }
        file << "timestamp,code,value\n";  // CSV-Header
        file.flush();
        RecReplay_thread = std::thread(&Recorder::threadFunction, this);

    }

    void Recorder::threadFunction(){
    	DEBUG("Record thread started");
    	record_running = true;
    	_pulse event;
    	while (record_running) {
    		int status = local_receiver->receive_event(&event);

    		if(status == 0) {
    			RecReplayEnum event_value = (RecReplayEnum) event.value.sival_int;
    			Topic event_code = (Topic) event.code;
    			if(event_code == Topic::REC_REPLAY){
					switch(event_value) {
					DEBUG("Record Replay Event erhalten ");
						case RecReplayEnum::START_REC:start_record();
						break;
						case RecReplayEnum::STOP_REC:
						break;
						case RecReplayEnum::START_REPLAY:start_replay();
						break;
						case RecReplayEnum::STOP_REPLAY:
						break;
					}
				}
    		}
    	}
    }


    void Recorder::start_record() {
        // ... Datei öffnen, Header schreiben, start_time setzen ...

        receiver_thread = std::thread(&Recorder::receiver_loop, this);
        writer_thread = std::thread(&Recorder::writer_loop, this);
    }

    void Recorder::stop_record() {
    	record_running = false;
        queue_cv.notify_all();
        if (receiver_thread.joinable()) receiver_thread.join();
        if (writer_thread.joinable()) writer_thread.join();
        if (file.is_open()) file.close();
    }

    void Recorder::receiver_loop() {
    	DEBUG("Recorder recieve Thread started.");
        _pulse event;
        while (record_running) {
            if (local_receiver->receive_event(&event) == 0) {
            	Topic event_code = (Topic) event.code;
            	if(event_code == Topic::INTERRUPT){
            		DEBUG("Recorder interruped erhalten");
					auto now = std::chrono::system_clock::now();
					auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now - start_time).count();
					// In Queue packen:
					{
						std::lock_guard<std::mutex> lock(queue_mutex);
						event_queue.push({ms, event.code, event.value.sival_int});
					}
					queue_cv.notify_one();
            	}
            }
        }
    }

    void Recorder::writer_loop() {
    	DEBUG("Recorder write Thread started.");
        while (record_running) {
            std::unique_lock<std::mutex> lock(queue_mutex);
            queue_cv.wait(lock, [&]{ return !event_queue.empty() || !record_running; });

            // Schreibe möglichst viele Events auf einmal:
            while (!event_queue.empty()) {
            	DEBUG("Recorder write event");
                const auto& e = event_queue.front();
                file << e.ms << "," << e.code << "," << e.value << "\n";
                event_queue.pop();
            }
            file.flush();
        }
    }

    void Recorder::start_replay() {
    	stop_record();
    	int coid = local_sender->getcoid();
        replay_events.clear();
        replay_running = true;

        // 1. CSV einlesen
        std::ifstream replay_file(RECORDER_CSV);
        if (!replay_file.is_open()) {
            std::cerr << "Replay: Datei konnte nicht geöffnet werden!\n";
            return;
        }
        std::string line;
        std::getline(replay_file, line); // Header überspringen
        while (std::getline(replay_file, line)) {
            std::istringstream iss(line);
            std::string token;
            ReplayEvent evt;
            std::getline(iss, token, ','); evt.ms = std::stoull(token);
            std::getline(iss, token, ','); evt.code = std::stoi(token);
            std::getline(iss, token, ','); evt.value = std::stoi(token);
            evt.timerid = 0;
            replay_events.push_back(evt);
        }
        replay_file.close();

        // 2. Für jeden Event einen QNX-Timer setzen
        for (auto& evt : replay_events) {
            struct sigevent sev{};
            memset(&sev, 0, sizeof(sev));
            sev.sigev_notify = SIGEV_PULSE;
            sev.sigev_coid = coid;
            sev.sigev_code = evt.code;
            sev.sigev_value.sival_int = evt.value;

            if (timer_create(CLOCK_MONOTONIC, &sev, &evt.timerid) == -1) {
                perror("Replay: timer_create");
                evt.timerid = 0;
                continue;
            }

            struct itimerspec its{};
            its.it_value.tv_sec = evt.ms / 1000;
            its.it_value.tv_nsec = (evt.ms % 1000) * 1000000;
            its.it_interval.tv_sec = 0;
            its.it_interval.tv_nsec = 0;

            if (timer_settime(evt.timerid, 0, &its, nullptr) == -1) {
                perror("Replay: timer_settime");
                timer_delete(evt.timerid);
                evt.timerid = 0;
                continue;
            }
        }
    }

    void Recorder::stop_replay() {
        // Alle Timer aufräumen, falls nötig
        for (auto& evt : replay_events) {
            if (evt.timerid != 0) {
                timer_delete(evt.timerid);
                evt.timerid = 0;
            }
        }
        replay_running = false;
    }
