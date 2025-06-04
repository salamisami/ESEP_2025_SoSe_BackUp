#include "TrafficUtility.h"
#include <chrono>
#include <iostream>
#include "Thread_COM.h"
#include "Event.h"
#include "EventPriority.h"

std::mutex TrafficUtility::instanceMutex_;
std::unique_ptr<TrafficUtility> TrafficUtility::instance_;

TrafficUtility::TrafficUtility(I_Sender* sender) {
	if(nullptr == sender) {
		throw std::runtime_error{ "Sender not initialized." };
	}
	//TODO TrafficUtility should be capsulated inside Actuator. Therefore sending event to dispatcher and therefore back to HAL is not a good idea :) see "Diagramms Combined for more info"
	traffic_sender = sender;
}
TrafficUtility::TrafficUtility(Mailbox<_pulse>* mailbox) {
	if(nullptr == mailbox) {
		throw std::runtime_error{ "mailbox not initialized." };
	}
	this->mailbox = mailbox;
}

TrafficUtility::TrafficUtility() {
	traffic_sender = new Thread_COM::Sender(FBM_1_DISPATCHER);
}

TrafficUtility& TrafficUtility::getInstance(Mailbox<_pulse>* mailbox) {
	std::lock_guard<std::mutex> lock(instanceMutex_);
	if(!instance_) {
		if(nullptr == mailbox) {
			throw std::runtime_error{ "mailbox not initialized." };
		}
		instance_.reset(new TrafficUtility(mailbox));
	}
	return *instance_;
}

TrafficUtility& TrafficUtility::getInstance(I_Sender* sender) {
	std::lock_guard<std::mutex> lock(instanceMutex_);
	if(!instance_) {
		if(nullptr == sender) {
			throw std::runtime_error{ "Sender not initialized." };
		}
		instance_.reset(new TrafficUtility(sender));
	}
	return *instance_;
}

TrafficUtility& TrafficUtility::getInstance() {
	std::lock_guard<std::mutex> lock(instanceMutex_);
	if(!instance_) {
		instance_.reset(new TrafficUtility());
	}
	return *instance_;
}

TrafficUtility::~TrafficUtility() {
	stopAll();
}

void TrafficUtility::sendLightPulse(ActuatorEnum state) {
	try {
		_pulse event;
		event.code = (int8_t) Topic::ACTUATOR;
		event.value.sival_int = (int) state;

		mailbox->put(event);
		//traffic_sender->send_event((int8_t) Topic::ACTUATOR, static_cast<int8_t>(state));
	} catch(...) {
		std::cerr << "Failed to send pulse for light state: "
			<< static_cast<int>(state) << std::endl;
	}
}

void TrafficUtility::trafficGreen(double frequency) {
	if(frequency <= 0) {
		throw std::invalid_argument("Frequency must be positive");
	}

	std::unique_lock<std::mutex> lock(green_.mutex);
	if(green_.running) {
		lock.unlock();
		stopGreen();
		lock.lock();
	}

	green_.frequency = frequency;
	green_.stopFlag = false;
	green_.running = true;
	green_.worker = std::thread(&TrafficUtility::greenWorker, this);
}

void TrafficUtility::trafficYellow(double frequency) {
	if(frequency <= 0) {
		throw std::invalid_argument("Frequency must be positive");
	}
	std::unique_lock<std::mutex> lock(yellow_.mutex);
	if(yellow_.running) {
		lock.unlock();
		stopYellow();
		lock.lock();
	}
	yellow_.frequency = frequency;
	yellow_.stopFlag = false;
	yellow_.running = true;
	yellow_.worker = std::thread(&TrafficUtility::yellowWorker, this);
}

void TrafficUtility::trafficRed(double frequency) {
	if(frequency <= 0) {
		throw std::invalid_argument("Frequency must be positive");
	}
	std::unique_lock<std::mutex> lock(red_.mutex);
	if(red_.running) {
		lock.unlock();
		stopRed();
		lock.lock();
	}
	red_.frequency = frequency;
	red_.stopFlag = false;
	red_.running = true;
	red_.worker = std::thread(&TrafficUtility::redWorker, this);
}

void TrafficUtility::stopGreen() {
	if(!green_.running) return;
	std::unique_lock<std::mutex> lock(green_.mutex);
	

	green_.stopFlag = true;
	green_.cv.notify_all();

	// Release lock before joining to prevent deadlock
	lock.unlock();

	if(green_.worker.joinable()) {
		green_.worker.join();
	}

	lock.lock();
	green_.running = false;
}

void TrafficUtility::stopYellow() {
	if(!yellow_.running) return;
	std::unique_lock<std::mutex> lock(yellow_.mutex);
	

	yellow_.stopFlag = true;
	yellow_.cv.notify_all();

	// Release lock before joining to prevent deadlock
	lock.unlock();

	if(yellow_.worker.joinable()) {
		yellow_.worker.join();
	}

	lock.lock();
	yellow_.running = false;
}

void TrafficUtility::stopRed() {
	if(!red_.running) return;
	std::unique_lock<std::mutex> lock(red_.mutex);
	

	red_.stopFlag = true;
	red_.cv.notify_all();

	// Release lock before joining to prevent deadlock
	lock.unlock();

	if(red_.worker.joinable()) {
		red_.worker.join();
	}

	lock.lock();
	red_.running = false;
}

void TrafficUtility::stopAll() {
	stopGreen();
	stopYellow();
	stopRed();
}

bool TrafficUtility::isGreenRunning() const {
	return green_.running;
}
bool TrafficUtility::isYellowRunning() const {
	return yellow_.running;
}
bool TrafficUtility::isRedRunning() const {
	return red_.running;
}

void TrafficUtility::greenWorker() {
	bool lightOn = false;

	while(!green_.stopFlag.load(std::memory_order_acquire)) {
		// Get frequency under lock
		double frequency;
		{
			std::lock_guard<std::mutex> lock(green_.mutex);
			frequency = green_.frequency;
		}

		// Send pulse
		if(lightOn) {
			std::cout << "traffic green off" << std::endl;
			sendLightPulse(ActuatorEnum::TRAFFIC_GREEN_OFF);
		} else {
			std::cout << "traffic green on" << std::endl;
			sendLightPulse(ActuatorEnum::TRAFFIC_GREEN_ON);
		}
		lightOn = !lightOn;

		// Wait with timeout
		{
			std::unique_lock<std::mutex> lock(green_.mutex);
			auto halfPeriod = std::chrono::milliseconds(
				static_cast<int>(500.0 / frequency)
			);
			green_.cv.wait_for(lock, halfPeriod, [this] {
				return green_.stopFlag.load(std::memory_order_acquire);
				});
		}
	}
	sendLightPulse(ActuatorEnum::TRAFFIC_GREEN_OFF);
}

void TrafficUtility::yellowWorker() {
	bool lightOn = false; // Track current light state

	while(!yellow_.stopFlag.load(std::memory_order_acquire)) {
		auto start = std::chrono::steady_clock::now();

		{
			std::unique_lock<std::mutex> lock(yellow_.mutex);

			// Alternate between on and off states
			if(lightOn) {
				std::cout << "traffic yellow off" << std::endl;
				sendLightPulse(ActuatorEnum::TRAFFIC_YELLOW_OFF);
			} else {
				std::cout << "traffic yellow on" << std::endl;
				sendLightPulse(ActuatorEnum::TRAFFIC_YELLOW_ON);
			}
			lightOn = !lightOn; // Toggle state

			// Calculate wait time (half period for blinking effect)
			auto halfPeriod = std::chrono::milliseconds(
				static_cast<int>(500.0 / yellow_.frequency));
			yellow_.cv.wait_for(lock,
				halfPeriod - (std::chrono::steady_clock::now() - start),
				[this] {return yellow_.stopFlag.load(std::memory_order_acquire); });
		}
	}
	sendLightPulse(ActuatorEnum::TRAFFIC_YELLOW_OFF);
}

void TrafficUtility::redWorker() {
	bool lightOn = false; // Track current light state

	while(!red_.stopFlag.load(std::memory_order_acquire)) {
		auto start = std::chrono::steady_clock::now();

		{
			std::unique_lock<std::mutex> lock(red_.mutex);

			// Alternate between on and off states
			if(lightOn) {
				std::cout << "traffic red off" << std::endl;
				sendLightPulse(ActuatorEnum::TRAFFIC_RED_OFF);
			} else {
				std::cout << "traffic red on" << std::endl;
				sendLightPulse(ActuatorEnum::TRAFFIC_RED_ON);
			}
			lightOn = !lightOn; // Toggle state

			// Calculate wait time (half period for blinking effect)
			auto halfPeriod = std::chrono::milliseconds(
				static_cast<int>(500.0 / red_.frequency));
			red_.cv.wait_for(lock,
				halfPeriod - (std::chrono::steady_clock::now() - start),
				[this] {return red_.stopFlag.load(std::memory_order_acquire); });
		}
	}
	sendLightPulse(ActuatorEnum::TRAFFIC_YELLOW_OFF);
}

