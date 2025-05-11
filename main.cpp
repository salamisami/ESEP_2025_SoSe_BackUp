#include "FBM.h"
#include <iostream>

#define ONE_MILLISECOND 1000

using namespace std;

int main() {
	cout << "Starting Program..." << endl; // prints Hello World!!!


	FBM stateMachine;
	stateMachine.buttonStartUp(true, false);
	stateMachine.buttonStop();

	cout << "Program Finished." << endl;
	return 0;
}
