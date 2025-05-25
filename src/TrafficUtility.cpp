#include "TrafficUtility.h"
#include <chrono>
#include <iostream>
#include "Thread_COM.h"
#include "Event.h"

std::mutex TrafficUtility::instanceMutex_;
std::unique_ptr<TrafficUtility> TrafficUtility::instance_;

TrafficUtility::TrafficUtility(int chid)
    : coid_(0)
{
    name_attach_t* attach = nullptr;
    if (Thread_COM::setup_thread_communication(nullptr, attach, &coid_) != 0) {
        throw std::runtime_error("Failed to initialize communication");
    }
}

TrafficUtility& TrafficUtility::getInstance(int chid) {
    static TrafficUtility instance(chid);
    return instance;
}
TrafficUtility::~TrafficUtility() {
	stopAll();
}

void TrafficUtility::sendLightPulse(ActuatorEnum state) {
	try {
		Thread_COM::send_event(coid_, static_cast<int8_t>(state), 1, 0);

		// Debug output
		const char* color = "";
		switch (state) {
		case ActuatorEnum::TRAFFIC_YELLOW_OFF:
			color = "YELLOW";
			break;
		default:
			color = "UNKNOWN";
			break;
		}
		std::cout << "Sent pulse: " << color << " light" << std::endl;
	} catch (...) {
		std::cerr << "Failed to send pulse for light state: "
				<< static_cast<int>(state) << std::endl;
	}
}

void TrafficUtility::trafficGreen(double frequency) {
	if (frequency <= 0) {
		throw std::invalid_argument("Frequency must be positive");
	}
	std::lock_guard<std::mutex> lock(green_.mutex);
	if (green_.running)
		stopGreen();

	green_.frequency = frequency;
	green_.stopFlag = false;
	green_.running = true;
	green_.worker = std::thread(&TrafficUtility::greenWorker, this);
}

void TrafficUtility::trafficYellow(double frequency) {
	if (frequency <= 0) {
		throw std::invalid_argument("Frequency must be positive");
	}
	std::lock_guard<std::mutex> lock(yellow_.mutex);
	if (yellow_.running)
		stopYellow();

	yellow_.frequency = frequency;
	yellow_.stopFlag = false;
	yellow_.running = true;
	yellow_.worker = std::thread(&TrafficUtility::yellowWorker, this);
}

void TrafficUtility::trafficRed(double frequency) {
	if (frequency <= 0) {
		throw std::invalid_argument("Frequency must be positive");
	}
	std::lock_guard<std::mutex> lock(red_.mutex);
	if (red_.running)
		stopRed();

	red_.frequency = frequency;
	red_.stopFlag = false;
	red_.running = true;
	red_.worker = std::thread(&TrafficUtility::redWorker, this);
}

void TrafficUtility::stopGreen() {
	{
		std::lock_guard<std::mutex> lock(green_.mutex);
		if (!green_.running)
			return;
		green_.stopFlag = true;
		green_.cv.notify_all();
	}
	if (green_.worker.joinable())
		green_.worker.join();
	green_.running = false;
}

void TrafficUtility::stopYellow() {
	{
		std::lock_guard<std::mutex> lock(yellow_.mutex);
		if (!yellow_.running)
			return;
		yellow_.stopFlag = true;
		yellow_.cv.notify_all();
	}
	if (yellow_.worker.joinable())
		yellow_.worker.join();
	yellow_.running = false;
}

void TrafficUtility::stopRed() {
	{
		std::lock_guard<std::mutex> lock(red_.mutex);
		if (!red_.running)
			return;
		red_.stopFlag = true;
		red_.cv.notify_all();
	}
	if (red_.worker.joinable())
		red_.worker.join();
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
	bool lightOn = false; // Track current light state

	while (!green_.stopFlag.load(std::memory_order_acquire)) {
		auto start = std::chrono::steady_clock::now();

		{
			std::unique_lock<std::mutex> lock(green_.mutex);

			// Alternate between on and off states
			if (lightOn) {
				sendLightPulse(ActuatorEnum::TRAFFIC_GREEN_OFF);
			} else {
				sendLightPulse (ActuatorEnum::TRAFFIC_GREEN_ON);
			}
			lightOn = !lightOn; // Toggle state

			// Calculate wait time (half period for blinking effect)
			auto halfPeriod = std::chrono::milliseconds(
					static_cast<int>(500.0 / green_.frequency));
			green_.cv.wait_for(lock,
					halfPeriod - (std::chrono::steady_clock::now() - start),
					[this] {return green_.stopFlag.load(std::memory_order_acquire);});
		}
	}
	sendLightPulse (ActuatorEnum::TRAFFIC_YELLOW_OFF);
}

void TrafficUtility::yellowWorker() {
	bool lightOn = false; // Track current light state

	while (!yellow_.stopFlag.load(std::memory_order_acquire)) {
		auto start = std::chrono::steady_clock::now();

		{
			std::unique_lock<std::mutex> lock(yellow_.mutex);

			// Alternate between on and off states
			if (lightOn) {
				sendLightPulse(ActuatorEnum::TRAFFIC_YELLOW_OFF);
			} else {
				sendLightPulse (ActuatorEnum::TRAFFIC_YELLOW_ON);
			}
			lightOn = !lightOn; // Toggle state

			// Calculate wait time (half period for blinking effect)
			auto halfPeriod = std::chrono::milliseconds(
					static_cast<int>(500.0 / yellow_.frequency));
			yellow_.cv.wait_for(lock,
					halfPeriod - (std::chrono::steady_clock::now() - start),
					[this] {return yellow_.stopFlag.load(std::memory_order_acquire);});
		}
	}
	sendLightPulse (ActuatorEnum::TRAFFIC_YELLOW_OFF);
}

void TrafficUtility::redWorker() {
	bool lightOn = false; // Track current light state

	while (!red_.stopFlag.load(std::memory_order_acquire)) {
		auto start = std::chrono::steady_clock::now();

		{
			std::unique_lock<std::mutex> lock(red_.mutex);

			// Alternate between on and off states
			if (lightOn) {
				sendLightPulse(ActuatorEnum::TRAFFIC_RED_OFF);
			} else {
				sendLightPulse (ActuatorEnum::TRAFFIC_RED_ON);
			}
			lightOn = !lightOn; // Toggle state

			// Calculate wait time (half period for blinking effect)
			auto halfPeriod = std::chrono::milliseconds(
					static_cast<int>(500.0 / red_.frequency));
			red_.cv.wait_for(lock,
					halfPeriod - (std::chrono::steady_clock::now() - start),
					[this] {return red_.stopFlag.load(std::memory_order_acquire);});
		}
	}
	sendLightPulse (ActuatorEnum::TRAFFIC_YELLOW_OFF);
}

