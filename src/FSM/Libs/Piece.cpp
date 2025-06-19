#include "Piece.h"

//================================================= constructors & destructors =================================================
Piece::Piece(TimeProfile input_profile_slow, TimeProfile input_profile_fast, uint8_t tick_duration) {
    deadlines = convert_to_deadlines(input_profile_slow, input_profile_fast);
    running = true;
    this->tick_duration = tick_duration;
    this->speed = convert_deadlines_to_speed(this->deadlines);
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

    deadline.slow[0] = input_timetable_slow.timestamp[(int) Timestamp::ADC_BLOCKED];
    deadline.slow[1] = input_timetable_slow.timestamp[(int) Timestamp::ADC_UNBLOCKED] - input_timetable_slow.timestamp[(int) Timestamp::ADC_BLOCKED];
    deadline.slow[2] = input_timetable_slow.timestamp[(int) Timestamp::LASER_GATE_BLOCKED] - input_timetable_slow.timestamp[(int) Timestamp::ADC_UNBLOCKED];
    deadline.slow[3] = input_timetable_slow.timestamp[(int) Timestamp::LASER_GATE_UNBLOCKED] - input_timetable_slow.timestamp[(int) Timestamp::LASER_GATE_BLOCKED];
    deadline.slow[4] = input_timetable_slow.timestamp[(int) Timestamp::END] - input_timetable_slow.timestamp[(int) Timestamp::LASER_GATE_UNBLOCKED];
    deadline.slow[5] = input_timetable_slow.timestamp[(int) Timestamp::LASER_RAMP_BLOCKED] - input_timetable_slow.timestamp[(int) Timestamp::LASER_GATE_BLOCKED];

    deadline.fast[0] = input_timetable_fast.timestamp[(int) Timestamp::ADC_BLOCKED];
    deadline.fast[1] = input_timetable_fast.timestamp[(int) Timestamp::ADC_UNBLOCKED] - input_timetable_fast.timestamp[(int) Timestamp::ADC_BLOCKED];
    deadline.fast[2] = input_timetable_fast.timestamp[(int) Timestamp::LASER_GATE_BLOCKED] - input_timetable_fast.timestamp[(int) Timestamp::ADC_UNBLOCKED];
    deadline.fast[3] = input_timetable_fast.timestamp[(int) Timestamp::LASER_GATE_UNBLOCKED] - input_timetable_fast.timestamp[(int) Timestamp::LASER_GATE_BLOCKED];
    deadline.fast[4] = input_timetable_fast.timestamp[(int) Timestamp::END] - input_timetable_fast.timestamp[(int) Timestamp::LASER_GATE_UNBLOCKED];
    deadline.fast[5] = input_timetable_fast.timestamp[(int) Timestamp::LASER_RAMP_BLOCKED] - input_timetable_fast.timestamp[(int) Timestamp::LASER_GATE_BLOCKED];


    return deadline;
}

Speed Piece::convert_deadlines_to_speed(const Deadlines input_deadline) {
    Speed output_speed;
    for(int i = 0; i < TIMESTAMP_LENGTH; i++) {
        output_speed.slow_speed[i] = (double) 100 * tick_duration / input_deadline.slow[i];
        output_speed.fast_speed[i] = (double) 100 * tick_duration / input_deadline.fast[i];
    }
    return output_speed;
}

Area Piece::step(Area initial_area) {
    if(initial_area == Area::GATE_END) {
        return Area::GATE_END;
    }
    uint8_t next_area = (uint8_t) initial_area + 1;
    return (Area) next_area;
}

void Piece::thread_function() {
    //TODO check if the piece should go to the ramp
    while(running) {
        if(current_position >= 100 && (current_area == Area::GATE_END || current_area == Area::GATE_RAMP)) {
            return;
        } else if(current_position >= 100) {
            current_area = step(current_area);
            current_position = 0;
        }
        switch(mode) {
            case 0:
                //stop
                break;
            case 1:
                //slow
                 current_position += speed.slow_speed[(int) current_area];
                break;
            case 2:
                //fast
                current_position += speed.fast_speed[(int) current_area];
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

Area Piece::getArea(){
    return current_area;
}

double Piece::getPosition(){
    return current_position;
}

bool Piece::send_to_ramp(){
    if(current_area == Area::GATE){
        current_area = Area::GATE_RAMP;
        current_position = 0;
        return true;
    }
    return false;
}