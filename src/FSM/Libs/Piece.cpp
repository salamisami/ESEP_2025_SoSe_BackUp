#include "Piece.h"

//================================================= constructors & destructors =================================================
Piece::Piece(TimeProfile input_profile_slow, TimeProfile input_profile_fast) {
    convert_to_deadlines(input_profile_slow, input_profile_fast);
    running = true;
    std::copy(std::begin(input_profile_fast.timestamp), std::end(input_profile_fast.timestamp), std::begin(fast_timestamps));
    std::copy(std::begin(input_profile_slow.timestamp), std::end(input_profile_slow.timestamp), std::begin(slow_timestamps));
    stopwatch.start();
    //piece_thread = std::thread(&Piece::thread_function, this);
    //set_thread_priority(piece_thread.native_handle(), 255);  // Higher priority for main thread
    //piece_thread.detach();
    debug_thread = std::thread(&Piece::debug_function, this);
    //debug_thread.detach();
}

Piece::~Piece() {
    stopwatch.stop();
    running = false;  // Signal threads to stop

    // Wake up threads if they're waiting
    if(piece_thread.joinable()) {
        piece_thread.join();
    }
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

// void Piece::set_thread_priority(pthread_t thread, int priority) {
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


void Piece::convert_to_deadlines(const TimeProfile& input_timetable_slow, const TimeProfile& input_timetable_fast) {
    slow_deadlines[0] = input_timetable_slow.timestamp[(int) Timestamp::ADC_BLOCKED];
    slow_deadlines[1] = input_timetable_slow.timestamp[(int) Timestamp::ADC_UNBLOCKED] - input_timetable_slow.timestamp[(int) Timestamp::ADC_BLOCKED];
    slow_deadlines[2] = input_timetable_slow.timestamp[(int) Timestamp::LASER_GATE_BLOCKED] - input_timetable_slow.timestamp[(int) Timestamp::ADC_UNBLOCKED];
    slow_deadlines[3] = input_timetable_slow.timestamp[(int) Timestamp::LASER_GATE_UNBLOCKED] - input_timetable_slow.timestamp[(int) Timestamp::LASER_GATE_BLOCKED];
    slow_deadlines[4] = input_timetable_slow.timestamp[(int) Timestamp::END] - input_timetable_slow.timestamp[(int) Timestamp::LASER_GATE_UNBLOCKED];
    slow_deadlines[5] = input_timetable_slow.timestamp[(int) Timestamp::LASER_RAMP_BLOCKED] - input_timetable_slow.timestamp[(int) Timestamp::LASER_GATE_BLOCKED];

    fast_deadlines[0] = input_timetable_fast.timestamp[(int) Timestamp::ADC_BLOCKED];
    fast_deadlines[1] = input_timetable_fast.timestamp[(int) Timestamp::ADC_UNBLOCKED] - input_timetable_fast.timestamp[(int) Timestamp::ADC_BLOCKED];
    fast_deadlines[2] = input_timetable_fast.timestamp[(int) Timestamp::LASER_GATE_BLOCKED] - input_timetable_fast.timestamp[(int) Timestamp::ADC_UNBLOCKED];
    fast_deadlines[3] = input_timetable_fast.timestamp[(int) Timestamp::LASER_GATE_UNBLOCKED] - input_timetable_fast.timestamp[(int) Timestamp::LASER_GATE_BLOCKED];
    fast_deadlines[4] = input_timetable_fast.timestamp[(int) Timestamp::END] - input_timetable_fast.timestamp[(int) Timestamp::LASER_GATE_UNBLOCKED];
    fast_deadlines[5] = input_timetable_fast.timestamp[(int) Timestamp::LASER_RAMP_BLOCKED] - input_timetable_fast.timestamp[(int) Timestamp::LASER_GATE_BLOCKED];
}


void Piece::debug_function() {
    while(running) {
        update();
        std::cout << "Area: " << (int) current_area << ", " << "Position: " << (double) current_position << " Mode: " << (int) current_mode << std::endl;
        WAIT(100);
    }
}
//===================================================== public functions =====================================================

//TODO send piece to ramps

//updates area and pos
std::pair<Area, double> Piece::calculate_area_pos(const Area& input_area, const double& input_pos, const uint8_t& mode) {
    long* selected_timestamps;
    switch(mode) {
        case 0:
            //stop
            //do nothing
            return std::make_pair(input_area, input_pos);
        case 1:
            //slow
            selected_timestamps = slow_timestamps;
            break;
        case 2:
            //fast
            selected_timestamps = fast_timestamps;
            break;
        default:
            break;
    }
    Area area;
    double position;
    const long current_time = stopwatch.peek_time();

    for(int i = (int) input_area; i < TIMESTAMP_LENGTH - 1; i++) {
        if(current_time < selected_timestamps[i]) {
            area = (Area) i;
            position = (double) current_time / selected_timestamps[i] * 100;
            return std::make_pair(area, position);
        }
    }
    area = Area::GATE_END;
    position = 100;
    return std::make_pair(area, position);
}

void Piece::update() {
    auto result = calculate_area_pos(current_area, current_position, current_mode);
    //TODO on speed change, stopwatch must be re-calculated
    stopwatch.start();
    current_area = result.first;
    current_position = result.second;
}


void Piece::fast() {
    update();
    current_mode = 2;
}

void Piece::slow() {
    update();
    current_mode = 1;
}

void Piece::stop() {
    update();
    current_mode = 0;
}


void Piece::reset() {
    stopwatch.reset();
    current_mode = 0;
    current_area = Area::START_ADC;
    current_position = 0;
}

void Piece::debug_mode(bool debug) {
    this->debug = debug;
}

Area Piece::getArea() {
    update();
    return current_area;
}

double Piece::getPosition() {
    update();
    return current_position;
}

bool Piece::send_to_ramp() {
    if(current_area == Area::GATE) {
        current_area = Area::GATE_RAMP;
        current_position = 0;
        return true;
    }
    return false;
}