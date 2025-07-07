#include "Timer.h"
#include "Context.h"
#include "Mock_PM.h"
#include "Event.h"
#include "Modehandler.h"

#include "Timer.h"
#include "Logic.h"
#include "Boot.h"
#include "SimulatePiece.h"
#include "Piece.h"

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
    long slow_profile[TIMESTAMP_LENGTH] = { 6000, 7200, 10309, 11780, 17207, 10552 };
    for(int i = 0; i < TIMESTAMP_LENGTH; i++) {
        both_profiles.slow_timestamps[i] = slow_profile[i];
    }

    // Save the profile
    TimeProfileManager::save_profile(both_profiles, SAVE_LOCATION_TIMEPROFILE);
    TimeProfileManager::convert_to_deadlines(&both_profiles);

    Piece* piece = new Piece(&both_profiles);
    piece->piece_tracker->print_distance();
    piece->piece_tracker->fast();
    for(int i = 0; i < 20; i++){
        piece->piece_tracker->print_distance();
        WAIT(100);
    }
    piece->piece_tracker->slow();
    for(int i = 0; i < 12; i++){
        piece->piece_tracker->print_distance();
        WAIT(100);
    }
    piece->piece_tracker->fast();
    for(int i = 0; i < 26; i++){
        piece->piece_tracker->print_distance();
        WAIT(100);
    }
    piece->piece_tracker->stop();
    for(int i = 0; i < 3; i++){
        piece->piece_tracker->print_distance();
        WAIT(1000);
    }
    piece->piece_tracker->fast();
    for(int i = 0; i < 13; i++){
        piece->piece_tracker->print_distance();
        WAIT(100);
    }
    
    piece->piece_tracker->print_distance();
    WAIT(1000);
    piece->piece_tracker->print_distance();



    piece->piece_tracker->reset();
    piece->piece_tracker->fast();
    for(int i = 0; i < 20; i++){
        piece->piece_tracker->print_distance();
        WAIT(100);
    }
    piece->piece_tracker->slow();
    for(int i = 0; i < 12; i++){
        piece->piece_tracker->print_distance();
        WAIT(100);
    }
    piece->piece_tracker->fast();
    for(int i = 0; i < 26; i++){
        piece->piece_tracker->print_distance();
        WAIT(100);
    }
    DEBUG("resetting to gate, 0...");
    piece->piece_tracker->update_distance_force(Area::ADC_GATE, 0);
    //piece->piece_tracker->fast();
    for(int i = 0; i < 13; i++){
        piece->piece_tracker->print_distance();
        WAIT(100);
    }
    
    piece->piece_tracker->print_distance();
    WAIT(1000);
    piece->piece_tracker->print_distance();

    delete piece;
    cout << "Program Finished." << endl;
    return 0;


}
