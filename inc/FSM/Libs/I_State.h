#ifndef I_STATE_H
#define I_STATE_H
#pragma once

#include "Event.h"

class I_State {
public: //============================================ contructors & destructors ============================================
    virtual ~I_State() = default;
	

public: //================================================ public functions ================================================
    virtual void entry() = 0;
    virtual void exit() = 0;

    virtual I_State* clone() = 0;

    virtual I_State* laser_front_blocked() = 0;
    virtual I_State* laser_front_unblocked() = 0;
    virtual I_State* laser_back_blocked() = 0;
    virtual I_State* laser_back_unblocked() = 0;
    virtual I_State* button_start_pressed() = 0;
    virtual I_State* button_start_released() = 0;
    virtual I_State* button_stop_pressed() = 0;
    virtual I_State* button_stop_released() = 0;
    virtual I_State* button_reset_pressed() = 0;
    virtual I_State* button_reset_released() = 0;
    virtual I_State* button_estop_pressed() = 0;
    virtual I_State* button_estop_released() = 0;
    virtual I_State* metal_detected() = 0;
    virtual I_State* metal_not_detected() = 0;
    virtual I_State* laser_sorting_gate_blocked() = 0;
    virtual I_State* laser_sorting_gate_unblocked() = 0;
    virtual I_State* laser_ramp_blocked() = 0;
    virtual I_State* laser_ramp_unblocked() = 0;
    virtual I_State* adc_top_area_blocked() = 0;
    virtual I_State* adc_top_area_unblocked() = 0;
    virtual I_State* adc_side_area_blocked() = 0;     //unused
    virtual I_State* adc_side_area_unblocked() = 0;   //unused

    virtual I_State* com_button_estop_pressed() = 0;
    virtual I_State* com_button_estop_released() = 0;

    virtual I_State* is_pusher() = 0;
    virtual I_State* is_switch() = 0;


    virtual I_State* adc_calibration_done() = 0;
    virtual I_State* adc_new_piece() = 0;

    virtual I_State* timer(TIMER_ID id) = 0;
    


private: //================================================ private variables ================================================
	//classes, STL containers, and structs
	//pointers
	//primitive types
	//bool and char
   
	

private: //================================================ private functions ================================================
	//void privateFunction() = 0;
	
};

#endif