#ifndef TIMEPROFILE_H
#define TIMEPROFILE_H
#pragma once

#include <cstdint>

#define TIMESTAMP_LENGTH 6

enum class Timestamp : uint8_t {
    ADC_BLOCKED = 0,
    ADC_UNBLOCKED,
    LASER_GATE_BLOCKED,
    LASER_GATE_UNBLOCKED,
    END,
    LASER_RAMP_BLOCKED
};

class TimeProfile {
public:
    long fast_timestamps[TIMESTAMP_LENGTH];
    long slow_timestamps[TIMESTAMP_LENGTH];

    long fast_deadlines[TIMESTAMP_LENGTH];
    long slow_deadlines[TIMESTAMP_LENGTH];
};

#endif
