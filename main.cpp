#include "HAL.h"
#include "Timer.h"
#include <iostream>

#define ONE_MILLISECOND 1000

using namespace std;




int main() {
    cout << "Starting Program..." << endl; // prints Hello World!!!

    HAL* hal = new HAL();
    hal->test_ins_ADC();
    
    delete hal;

    cout << "Program Finished." << endl;
    return 0;
}
