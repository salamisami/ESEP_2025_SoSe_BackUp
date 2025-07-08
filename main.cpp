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
#include "ReadyForPiece.h"
#include <gtest/gtest.h>

#include <iostream>

#define ONE_MILLISECOND 1000

#define EXPECT_STATE(expected_state) \
    do { \
        WAIT(50); \
        std::string is_state = logic->show_state(); \
        EXPECT_EQ(is_state, expected_state); \
    } while (0)

#define EXPECT_STATE_CONTAINS(expected_state) \
    do { \
        WAIT(50); \
        std::string is_state = logic->show_state(); \
        EXPECT_NE(is_state.find(expected_state), std::string::npos) \
            << "Expected state to contain: '" << expected_state \
            << "' but got: '" << is_state << "'"; \
    } while (0)


#define EXPECT_STATE_INSTANT(expected_state) \
    do { \
        WAIT(10); \
        std::string is_state = logic->show_state(); \
        EXPECT_EQ(is_state, expected_state); \
    } while (0)

#define ONE_MILLISECOND 1000

using namespace std;



int main() {
    cout << "Starting Program..." << endl; // prints Hello World!!!

    TimeProfile* timeprofile = new TimeProfile();
    TimeProfileManager::load_profile(timeprofile, SAVE_LOCATION_TIMEPROFILE);


    DistanceTracker* tracker = new DistanceTracker(timeprofile, true);
    tracker->fast();
    WAIT(20000);
    cout << "Program Finished." << endl;
    return 0;


}
