#include "Timer.h"
#include "Context.h"
#include "IdleMode.h"
#include "Mock_PM.h"
#include "Event.h"
#include "ModeHandler.h"

#include "Timer.h"
#include "Logic.h"
#include "Boot.h"
#include "SimulatePiece.h"

#include <iostream>

#define ONE_MILLISECOND 1000

using namespace std;




int main() {
    cout << "Starting Program..." << endl; // prints Hello World!!!

    // Initialize time profiles
    TimeProfile both_profiles;
    // Set fast timestamps
    long fast_profile[TIMESTAMP_LENGTH] = { 2000, 2100, 3600, 4000, 6000, 3800 };
    for(int i = 0; i < TIMESTAMP_LENGTH; i++) {
        both_profiles.fast_timestamps[i] = fast_profile[i];
    }
    // Set slow timestamps
    long slow_profile[TIMESTAMP_LENGTH] = { 6060, 7183, 10309, 11780, 17207, 10552 };
    for(int i = 0; i < TIMESTAMP_LENGTH; i++) {
        both_profiles.slow_timestamps[i] = slow_profile[i];
    }

    // Save the profile
    TimeProfileManager::save_profile(both_profiles, SAVE_LOCATION_TIMEPROFILE);
    TimeProfileManager::convert_to_deadlines(&both_profiles);


    Mock_PM::Receiver* logic_receiver = new Mock_PM::Receiver();
    Mock_PM::Sender* remote_control = new Mock_PM::Sender(logic_receiver);

    Mock_PM::Receiver* hal_receiver = new Mock_PM::Receiver();
    Mock_PM::Sender* logic_sender = new Mock_PM::Sender(hal_receiver);
    I_Sender* to_self_sender = new Mock_PM::Sender(logic_receiver);



    auto logic = new Logic<SimulatePiece>(logic_receiver, to_self_sender);
    //boot
    WAIT(500);
    //remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::IS_SWITCH);

    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_FRONT_BLOCKED);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_FRONT_UNBLOCKED);
    WAIT(2000);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::ADC_TOP_AREA_BLOCKED);
    WAIT(100);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::ADC_TOP_AREA_UNBLOCKED);
    WAIT(1500);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_BLOCKED);
    WAIT(400);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_UNBLOCKED);
    WAIT(2000);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_BACK_BLOCKED);
    WAIT(1000);

    delete logic;
    delete to_self_sender;
    delete logic_sender;
    delete hal_receiver;
    delete remote_control;
    delete logic_receiver;
    cout << "Program Finished." << endl;
    return 0;


}
