#include "FBM.h"
#include <iostream>

#define ONE_MILLISECOND 1000

using namespace std;

int main() {
	cout << "Starting Program..." << endl;
try{
	FBM stateMachine;
	stateMachine.buttonStartUp(true, false);
	stateMachine.buttonStop();
} catch(const std::exception& e) {
    cout << "CRASH: " << e.what() << endl;
}
	cout << "Program Finished." << endl;
	return 0;
}
