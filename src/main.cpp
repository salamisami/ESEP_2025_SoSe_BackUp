#include "HAL.h"
#include <iostream>

#define ONE_MILLISECOND 1000

using namespace std;


void wait(){
	usleep(ONE_MILLISECOND * 1000);
}

int main() {
	cout << "Starting Program..." << endl; // prints Hello World!!!


	IHAL* hal = new HAL();

	hal->traffic_red_on();
	wait();
	hal->traffic_red_off();

	hal->traffic_yellow_on();
	wait();
	hal->traffic_yellow_off();

	hal->traffic_green_on();
	wait();
	hal->traffic_green_off();

	hal->motor_slow_on();
	hal->motor_right_on();
	wait();
	hal->motor_slow_off();
	wait();
	hal->motor_right_off();

	hal->motor_slow_on();
	hal->motor_left_on();
	wait();
	hal->motor_slow_off();
	wait();
	hal->motor_left_off();

	hal->sorting_on();
	wait();
	hal->sorting_off();

	hal->led_start_on();
	wait();
	hal->led_reset_on();
	wait();
	hal->led_q1_on();
	wait();
	hal->led_q2_on();
	wait();

	hal->led_start_off();
	hal->led_reset_off();
	hal->led_q1_off();
	hal->led_q2_off();



	delete hal;
	cout << "Program Finished." << endl;
	return 0;
}
