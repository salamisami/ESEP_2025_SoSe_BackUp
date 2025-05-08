#include "HAL.h"
#include <iostream>

#define ONE_MILLISECOND 1000

using namespace std;


void wait(int seconds) {
	usleep(ONE_MILLISECOND * 1000 * seconds);
}

int main() {
	cout << "Starting Program..." << endl; // prints Hello World!!!
	int globalChannelID = ChannelCreate(0);
	int globalConID = ConnectAttach(0, 0, globalChannelID, _NTO_SIDE_CHANNEL, 0);

	HAL* hal = new HAL(globalConID);
	std::cout << "Festo is gate: " << std::boolalpha << hal->isGate() << std::endl;
	//schläger:50600801
	//weiche   50600801
	//hal->test_outs();
	hal->test_ins(globalChannelID);

	delete hal;

	cout << "Program Finished." << endl;
	return 0;
}
