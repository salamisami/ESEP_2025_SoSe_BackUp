#include "HAL.h"
#include <iostream>

#define ONE_MILLISECOND 1000

using namespace std;


void wait(int seconds) {
	usleep(ONE_MILLISECOND * 1000 * seconds);
}

int main() {
	cout << "Starting Program..." << endl; // prints Hello World!!!
	
	HAL* hal = new HAL("Dispatcher");
	std::cout << "Festo is gate: " << std::boolalpha << hal->isGate() << std::endl;

	//hal->test_outs();
	hal->test_ins();

	delete hal;

	cout << "Program Finished." << endl;
	return 0;
}
