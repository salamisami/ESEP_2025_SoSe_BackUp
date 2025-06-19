#include "Timer.h"
#include "Context.h"
#include "IdleMode.h"
#include "Mock_PM.h"
#include "Event.h"
#include "ModeHandler.h"

#include "Timer.h"
#include "Logic.h"
#include "Piece.h"

#include <iostream>

#define ONE_MILLISECOND 1000

using namespace std;




int main() {
    cout << "Starting Program..." << endl; // prints Hello World!!!

    // Timestamp fast: 2165
    // Timestamp fast: 2560
    // Timestamp fast: 3651
    // Timestamp fast: 4150
    // Timestamp fast: 5908
    // Timestamp fast: 4050

    // Timestamp slow: 6707
    // Timestamp slow: 7987
    // Timestamp slow: 11583
    // Timestamp slow: 13239
    // Timestamp slow: 19122
    // Timestamp slow: 11847
    TimeProfile fast_profile = { {2165, 2560, 3651, 4150, 5908, 4050} };
    TimeProfile slow_profile = { {6707, 7987, 11583, 13239, 19122, 11847} };

    int tick_duration = 10;
    Piece* piece = new Piece(slow_profile, fast_profile, tick_duration);
    piece->slow();
    while(true){
        std::cout << "Area: " << (int) piece->getArea() << ", " << "Position: " << (double) piece->getPosition() << std::endl;
        WAIT(500);
    }

    
    cout << "Program Finished." << endl;
    return 0;


}
