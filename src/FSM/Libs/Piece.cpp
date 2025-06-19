#include "Piece.h"

//================================================= constructors & destructors =================================================
Piece::Piece(TimeProfile input_profile_slow, TimeProfile input_profile_fast, uint8_t tick_duration) {
    deadlines = convert_to_deadlines(input_profile_slow, input_profile_fast);
    running = true;
    this->tick_duration = tick_duration;
    piece_thread = std::thread(&Piece::thread_function, this);
}

Piece::~Piece() {
    running = false;
}

//===================================================== private functions =====================================================

// Example Timestamp
// Timestamp: 2000
// Timestamp: 2117
// Timestamp: 3382
// Timestamp: 3874
// Timestamp: 5612
// Timestamp: 4857


Deadlines Piece::convert_to_deadlines(TimeProfile input_timetable_slow, TimeProfile input_timetable_fast) {
    Deadlines deadline;
    deadline.start_adc.fast = input_timetable_fast.timestamp[(int) Timestamp::ADC_BLOCKED];
    deadline.adc.fast = input_timetable_fast.timestamp[(int) Timestamp::ADC_UNBLOCKED] - input_timetable_fast.timestamp[(int) Timestamp::ADC_BLOCKED];
    deadline.adc_gate.fast = input_timetable_fast.timestamp[(int) Timestamp::LASER_GATE_BLOCKED] - input_timetable_fast.timestamp[(int) Timestamp::ADC_UNBLOCKED];
    deadline.gate.fast = input_timetable_fast.timestamp[(int) Timestamp::LASER_GATE_UNBLOCKED] - input_timetable_fast.timestamp[(int) Timestamp::LASER_GATE_BLOCKED];
    deadline.gate_end.fast = input_timetable_fast.timestamp[(int) Timestamp::END] - input_timetable_fast.timestamp[(int) Timestamp::LASER_GATE_UNBLOCKED];

    deadline.start_adc.slow = input_timetable_slow.timestamp[(int) Timestamp::ADC_BLOCKED];
    deadline.adc.slow = input_timetable_slow.timestamp[(int) Timestamp::ADC_UNBLOCKED] - input_timetable_slow.timestamp[(int) Timestamp::ADC_BLOCKED];
    deadline.adc_gate.slow = input_timetable_slow.timestamp[(int) Timestamp::LASER_GATE_BLOCKED] - input_timetable_slow.timestamp[(int) Timestamp::ADC_UNBLOCKED];
    deadline.gate.slow = input_timetable_slow.timestamp[(int) Timestamp::LASER_GATE_UNBLOCKED] - input_timetable_slow.timestamp[(int) Timestamp::LASER_GATE_BLOCKED];
    deadline.gate_end.slow = input_timetable_slow.timestamp[(int) Timestamp::END] - input_timetable_slow.timestamp[(int) Timestamp::LASER_GATE_UNBLOCKED];

    return deadline;
}

Ticks Piece::convert_deadlines_to_ticks(const Deadlines input_deadline) {

}

void Piece::next_area() {
    uint8_t next_area = (uint8_t) current_area + 1;
    current_area = (Area) next_area;
}

void Piece::thread_function() {
    while(running) {
        switch(mode) {
            case 0:
                //stop
                break;
            case 1:
                //slow
                break;
            case 2:
                //fast
                timer.start(deadlines.adc.fast, &Piece::next_area, this);
                break;
            default:
                break;
        }
        WAIT(tick_duration);
    }
}

//===================================================== public functions =====================================================
void Piece::stop() {
    mode = 0;
}
void Piece::slow() {
    mode = 1;
}
void Piece::fast() {
    mode = 2;
}
