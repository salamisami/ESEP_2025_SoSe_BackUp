#include "Recorder.h"


Recorder::Recorder(I_Receiver* local_receiver, I_Sender* local_sender)
    : local_receiver(local_receiver), local_sender(local_sender),
      running(true), record_running(false), replay_running(false)
{
    RecReplay_thread = std::thread(&Recorder::threadFunction, this);
    std::cout << "Recorder: Main-Thread gestartet" << std::endl;
}

Recorder::~Recorder() {
    running = false;
    stop_record();
    stop_replay();
    if (RecReplay_thread.joinable()) RecReplay_thread.join();
    if (writer_thread.joinable()) writer_thread.join();
    if (replay_thread.joinable()) replay_thread.join();
}

void Recorder::threadFunction() {
    DEBUG("Record thread started");
    _pulse event;
    while (running) {
        int status = local_receiver->receive_event(&event);

        if (status == 0) {
            RecReplayEnum event_value = (RecReplayEnum)event.value.sival_int;
            Topic event_code = (Topic)event.code;
            if (event_code == Topic::REC_REPLAY) {
            	DEBUG("[MAIN RecReplay event erhalten]");
                switch (event_value) {
                    case RecReplayEnum::START_REC: start_record(); break;
                    case RecReplayEnum::STOP_REC: stop_record(); break;
                    case RecReplayEnum::START_REPLAY: start_replay(); break;
                    case RecReplayEnum::STOP_REPLAY: stop_replay(); break;
                }
            }
            if ((event_code == Topic::INTERRUPT || event_code == Topic::COM) && record_running){

				Topic Inter_event_code = (Topic)event.code;
				Topic OM_event_code = (Topic)event.code;

				if (Inter_event_code == Topic::INTERRUPT) {

					DEBUG("Recorder interruped erhalten");
					auto now = std::chrono::system_clock::now();
					auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now - start_time).count();
					{
						std::lock_guard<std::mutex> lock(queue_mutex);
						event_queue.push({ms, event.code, event.value.sival_int});
					}
					queue_cv.notify_one();
				}
            }
        }
    }
}

void Recorder::start_record() {
	int8_t ActuatorCode = (int8_t) Topic::ACTUATOR;
	local_sender->send_event(ActuatorCode, (int) ActuatorEnum::LED_Q1_ON);
    std::lock_guard<std::mutex> lock(rec_mutex);
    if (record_running) {
        DEBUG("Record already running!");
        return;
    }
    stop_replay();
    record_running = true; // **jetzt erst true**

    writer_thread = std::thread(&Recorder::writer_loop, this);
    // kurz warten, bis writer_ready ist
    while (!writer_ready) std::this_thread::yield();
}

void Recorder::stop_record() {
	int8_t ActuatorCode = (int8_t) Topic::ACTUATOR;
	local_sender->send_event(ActuatorCode, (int) ActuatorEnum::LED_Q1_OFF);
    std::lock_guard<std::mutex> lock(rec_mutex);
    if (!record_running) return;
    record_running = false;

    queue_cv.notify_all();
    if (writer_thread.joinable()) writer_thread.join();
    if (file.is_open()) file.close();
    DEBUG("Recorder: Recording gestoppt");
}

void Recorder::writer_loop() {
    DEBUG("Recorder write Thread started.");
    file.open(RECORDER_CSV, std::ios::out);

    if (!file.is_open() || file.fail()) {
        std::cerr << "Recorder: Datei konnte nicht geöffnet werden!" << std::endl;
        writer_ready = true; // Damit Main nicht ewig wartet
        return;
    }
    file << "timestamp,code,value,Event Name\n";
    file.flush();
    start_time = std::chrono::system_clock::now();
    writer_ready = true; // <<<<<< Jetzt signalisiere "bereit"

    while (record_running) {
        std::unique_lock<std::mutex> lock(queue_mutex);
        queue_cv.wait(lock, [&] { return !event_queue.empty() || !record_running; });

        while (!event_queue.empty()) {
            const auto& e = event_queue.front();
            file << e.ms << "," << e.code << "," << e.value << "," << interruptEnumToString(e.value) << "\n";
            event_queue.pop();
        }
        file.flush();
    }
    file.close();
    DEBUG("Recorder write Thread stopped.");
}

void Recorder::start_replay() {
	int8_t ErrorCode = (int8_t) Topic::ERROR;
	int8_t ActuatorCode = (int8_t) Topic::ACTUATOR;
	local_sender->send_event(ActuatorCode, (int) ActuatorEnum::LED_Q1_ON);
    std::lock_guard<std::mutex> lock(rep_mutex);
    if (replay_running) {
        DEBUG("Replay already running!");
        return;
    }
    stop_record(); // Parallelbetrieb vermeiden!
    replay_events.clear();
    replay_running = true;

    if (!FILE_EXISTS(RECORDER_CSV)) {
    	local_sender->send_event(ErrorCode, (int) ErrorEnum::CANT_FIND_REP_CONF);
        std::cerr << "Replay: Datei existiert nicht!\n";
        replay_running = false;
        return;
    }
    std::ifstream replay_file(RECORDER_CSV);
    if (!replay_file.is_open() || replay_file.fail()) {
        std::cerr << "Replay: Datei konnte nicht geöffnet werden!\n";
        replay_running = false;
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
        replay_events.push_back(evt);
        DEBUG(("Replay: Event gelesen ms=" + std::to_string(evt.ms) +
               " code=" + std::to_string(evt.code) +
               " value=" + std::to_string(evt.value)).c_str());
    }
    replay_file.close();
    replay_thread = std::thread(&Recorder::replay_loop, this);
    DEBUG("Replay Thread gestartet");
}

void Recorder::stop_replay() {
	int8_t ActuatorCode = (int8_t) Topic::ACTUATOR;
	local_sender->send_event(ActuatorCode, (int) ActuatorEnum::LED_Q1_OFF);
    std::lock_guard<std::mutex> lock(rep_mutex);
    if (!replay_running) return;
    replay_running = false;
    if (replay_thread.joinable()) replay_thread.join();
    DEBUG("Replay Thread gestoppt");
}

void Recorder::replay_loop() {
    DEBUG("Replay thread started.");
    if (replay_events.empty()) return;
    auto replay_start = std::chrono::steady_clock::now();
    size_t idx = 0;
    while (replay_running && idx < replay_events.size()) {
        auto now = std::chrono::steady_clock::now();
        long long elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now - replay_start).count();
        long long wait_ms = replay_events[idx].ms - elapsed_ms;
        if (wait_ms > 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(wait_ms));
        }
        local_sender->send_event(replay_events[idx].code, replay_events[idx].value);
        idx++;
    }
    DEBUG("Replay thread finished.");
}

std::string Recorder::interruptEnumToString(int value) {
    switch(static_cast<InterruptEnum>(value)) {
        case InterruptEnum::LASER_FRONT_BLOCKED: return "LASER_FRONT_BLOCKED";
        case InterruptEnum::LASER_FRONT_UNBLOCKED: return "LASER_FRONT_UNBLOCKED";
        case InterruptEnum::LASER_BACK_BLOCKED: return "LASER_BACK_BLOCKED";
        case InterruptEnum::LASER_BACK_UNBLOCKED: return "LASER_BACK_UNBLOCKED";
        case InterruptEnum::BUTTON_START_PRESSED: return "BUTTON_START_PRESSED";
        case InterruptEnum::BUTTON_START_RELEASED: return "BUTTON_START_RELEASED";
        case InterruptEnum::BUTTON_STOP_PRESSED: return "BUTTON_STOP_PRESSED";
        case InterruptEnum::BUTTON_STOP_RELEASED: return "BUTTON_STOP_RELEASED";
        case InterruptEnum::BUTTON_RESET_PRESSED: return "BUTTON_RESET_PRESSED";
        case InterruptEnum::BUTTON_RESET_RELEASED: return "BUTTON_RESET_RELEASED";
        case InterruptEnum::BUTTON_ESTOP_PRESSED: return "BUTTON_ESTOP_PRESSED";
        case InterruptEnum::BUTTON_ESTOP_RELEASED: return "BUTTON_ESTOP_RELEASED";
        case InterruptEnum::METAL_DETECTED: return "METAL_DETECTED";
        case InterruptEnum::METAL_NOT_DETECTED: return "METAL_NOT_DETECTED";
        case InterruptEnum::LASER_SORTING_GATE_BLOCKED: return "LASER_SORTING_GATE_BLOCKED";
        case InterruptEnum::LASER_SORTING_GATE_UNBLOCKED: return "LASER_SORTING_GATE_UNBLOCKED";
        case InterruptEnum::LASER_RAMP_BLOCKED: return "LASER_RAMP_BLOCKED";
        case InterruptEnum::LASER_RAMP_UNBLOCKED: return "LASER_RAMP_UNBLOCKED";
        case InterruptEnum::ADC_TOP_AREA_BLOCKED: return "ADC_TOP_AREA_BLOCKED";
        case InterruptEnum::ADC_TOP_AREA_UNBLOCKED: return "ADC_TOP_AREA_UNBLOCKED";
        case InterruptEnum::ADC_SIDE_AREA_BLOCKED: return "ADC_SIDE_AREA_BLOCKED";
        case InterruptEnum::ADC_SIDE_AREA_UNBLOCKED: return "ADC_SIDE_AREA_UNBLOCKED";
        case InterruptEnum::IS_SWITCH: return "IS_SWITCH";
        case InterruptEnum::IS_PUSHER: return "IS_PUSHER";
        default: return "UNKNOWN";
    }
}
