#include "DistanceTracker.h"

//================================================= constructors & destructors =================================================


DistanceTracker::DistanceTracker(TimeProfile* time_profile, bool debug) :time_profile(time_profile) {
    reset();
    if(debug) {
        start_debug_thread();
    }
}

DistanceTracker::~DistanceTracker() {
    stop();
    running = false;
    if(debug_thread.joinable()) {
        debug_thread.join();
    }
}

//===================================================== private functions =====================================================

// Example Timestamp
// Timestamp: 2000
// Timestamp: 2117
// Timestamp: 3382
// Timestamp: 3874
// Timestamp: 5612
// Timestamp: 4857


//piece_thread = std::thread(&DistanceTracker::thread_function, this);
//set_thread_priority(piece_thread.native_handle(), 255);  // Higher priority for main thread
//piece_thread.detach();
// void DistanceTracker::set_thread_priority(pthread_t thread, int priority) {
//     struct sched_param param;
//     param.sched_priority = priority;

//     // Set FIFO scheduling policy with specified priority
//     if (pthread_setschedparam(thread, SCHED_FIFO, &param) != 0) {
//         std::cerr << "Failed to set thread priority: " << strerror(errno) << std::endl;
//     }

//     // Optional: Set thread CPU affinity
//     // cpu_set_t cpuset;
//     // CPU_ZERO(&cpuset);
//     // CPU_SET(0, &cpuset);  // Pin to CPU 0
//     // pthread_setaffinity_np(thread, sizeof(cpu_set_t), &cpuset);
// }


std::pair<Area, double> DistanceTracker::timestamp_to_area_pos(const long& timestamp, const uint8_t& mode) {
    const long* timestamps = (mode == 1) ? time_profile->slow_timestamps : time_profile->fast_timestamps;

    if(timestamp < timestamps[0]) {
        return { Area::START_ADC, (timestamp * 100.0) / timestamps[0] };
    }

    for(int i = 1; i < TIMESTAMP_LENGTH - 1; ++i) {
        if(timestamp < timestamps[i]) {
            double pos = (timestamp - timestamps[i - 1]) * 100.0 / (timestamps[i] - timestamps[i - 1]);
            return { static_cast<Area>(i), pos };
        }
    }

    return { Area::OUT_OF_RANGE, 0 };
}

long DistanceTracker::area_pos_to_timestamp(const Area& area, const double& pos, const uint8_t& mode) {
    if(mode == 0 || area == Area::OUT_OF_RANGE) {
        return 0;
    }

    const long* timestamps = (mode == 1) ? time_profile->slow_timestamps : time_profile->fast_timestamps;
    const long* deadlines = (mode == 1) ? time_profile->slow_deadlines : time_profile->fast_deadlines;

    if(area == Area::START_ADC) {
        return (timestamps[0] * pos) / 100;
    }

    return timestamps[static_cast<int>(area) - 1] + (deadlines[static_cast<int>(area)] * pos) / 100;
}


void DistanceTracker::debug_function() {
    while(running) {
        if(log) {
            update();
//            std::cout << "Area: " << static_cast<int>(current_area)
//                << ", Position: " << current_position
//                << ", Mode: " << static_cast<int>(current_mode) << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(250));  // Print every 250ms
        } else {
            // Print once when stopped
            //std::cout << "Stopped. Last Area: " << static_cast<int> (current_area) << "Last Pos: " << current_position << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));  // Avoid busy-waiting
        }
    }
}

void DistanceTracker::start_debug_thread() {
    running = true;
    debug_thread = std::thread(&DistanceTracker::debug_function, this);
}
//===================================================== public functions =====================================================



//updates area and pos from the last time.
std::pair<Area, double> DistanceTracker::calculate_area_pos(const Area& last_area, const double& last_pos, const uint8_t& mode) {
    if(mode == (int) 0) {
        stopwatch.reset();
        stopwatch.start();
        return std::make_pair(last_area, last_pos);
    }
    if(last_area == Area::OUT_OF_RANGE) {
        return std::make_pair(last_area, 0);
    }
    long last_position_in_ms = (long) area_pos_to_timestamp(last_area, last_pos, mode);
    long current_position_in_ms = stopwatch.peek_time() + last_position_in_ms;
    stopwatch.reset();
    stopwatch.start();
    return timestamp_to_area_pos(current_position_in_ms, mode);
}

void DistanceTracker::update() {
    auto result = calculate_area_pos(current_area, current_position, current_mode);
    stopwatch.reset();
    stopwatch.start();
    current_area = result.first;
    current_position = result.second;
}

void DistanceTracker::update_distance_force(const Area& area, const double& position) {
    current_area = area;
    current_position = position;
    stopwatch.reset();
    stopwatch.start();
}



void DistanceTracker::fast() {
    log = true;
    DEBUG("Piece_Fast_called!");
    update();
    current_mode = 2;
}

void DistanceTracker::slow() {
    log = true;
    DEBUG("Piece_slow_called!");
    update();
    current_mode = 1;
}

void DistanceTracker::stop() {
    log = false;
    DEBUG("Piece_stop_called!");
    update();
    current_mode = 0;
}


void DistanceTracker::reset() {
    DEBUG("Piece_reset called!");
    //stop();
    stopwatch.reset();
    current_mode = 0;
    current_area = Area::START_ADC;
    current_position = 0;
}

// Area DistanceTracker::getArea() {
//     return get_distance().first;
// }

// double DistanceTracker::getPosition() {
//     update();
//     return current_position;
// }

std::pair<Area, double> DistanceTracker::get_distance() {
    update();
    return {current_area, current_position};
}

void DistanceTracker::print_distance() {
    update();
    std::cout << "Area: " << (int) current_area << ", " << "Position: " << (double) current_position << " Mode: " << (int) current_mode << std::endl;
}
