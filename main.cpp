#include "Timer.h"
#include "Context.h"
#include "Idle.h"
#include "Mock_PM.h"
#include <iostream>

#define ONE_MILLISECOND 1000

using namespace std;




int main() {
    cout << "Starting Program..." << endl; // prints Hello World!!!
    I_Receiver* local_receiver = new Mock_PM::Receiver();
    I_Sender* local_sender = new Mock_PM::Sender(local_receiver);
    ContextData data = ContextData(local_sender, local_receiver);
    Context<Idle> fsm = Context<Idle>(&data);

    delete local_sender;
    delete local_receiver;
    cout << "Program Finished." << endl;
    return 0;
}
