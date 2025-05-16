#include "Actuator.h"
#include "Interrupt.h"
#include <iostream>

#define ONE_MILLISECOND 1000

using namespace std;


void wait(int seconds) {
    usleep(ONE_MILLISECOND * 1000 * seconds);
}

void test_ins() {
    std::cout << "Testing Inputs... Please put Piece on the front laser" << std::endl;
    QNet::Sender sender("Actuator");
    QNet::Receiver receiver("Dispatcher");
    bool running = true;
    int8_t code = (int8_t) Topic::INTERRUPT;
    while(running) {
        _pulse msg = receiver.receive();
        InterruptEnum event = (InterruptEnum) msg.value.sival_int;
        switch(event) {
            case InterruptEnum::LASER_FRONT_BLOCKED:
                std::cout << "Thanks!" << std::endl;
                sender.send(code, (int) ActuatorEnum::TRAFFIC_GREEN_ON);
                sender.send(code, (int) ActuatorEnum::MOTOR_RIGHT_START);
                break;
            case InterruptEnum::LASER_BACK_BLOCKED:
                sender.send(code, (int) ActuatorEnum::MOTOR_STOP);
                sender.send(code, (int) ActuatorEnum::TRAFFIC_GREEN_OFF);
                sender.send(code, (int) ActuatorEnum::TRAFFIC_RED_ON);
                break;
            case InterruptEnum::LASER_BACK_UNBLOCKED:
                sender.send(code, (int) ActuatorEnum::TRAFFIC_RED_OFF);
                sender.send(code, (int) ActuatorEnum::TRAFFIC_YELLOW_OFF);
                sender.send(code, (int) ActuatorEnum::TRAFFIC_GREEN_OFF);
                //running = false;
                break;
            case InterruptEnum::METAL_DETECTED:
                sender.send(code, (int) ActuatorEnum::SORTING_ON);
                wait(0.5);
                sender.send(code, (int) ActuatorEnum::SORTING_OFF);
                break;
            case InterruptEnum::BUTTON_ESTOP_PRESSED:
                running = false;
                break;
            case InterruptEnum::BUTTON_STOP_PRESSED:
                running = false;
                break;
            case InterruptEnum::ADC_TOP_AREA_BLOCKED:
                sender.send(code, (int) ActuatorEnum::MOTOR_SLOW_ON);
                sender.send(code, (int) ActuatorEnum::TRAFFIC_YELLOW_ON);
                break;
            case InterruptEnum::ADC_TOP_AREA_UNBLOCKED:
                sender.send(code, (int) ActuatorEnum::MOTOR_SLOW_OFF);
                sender.send(code, (int) ActuatorEnum::TRAFFIC_YELLOW_OFF);
                break;
            default:
                break;
        }
    }
    std::cout << "Testing Input done." << std::endl;
}


int main() {
    cout << "Starting Program..." << endl; // prints Hello World!!!

    system("gns -c");

    //QNet::Receiver* interrupt_buffer = new QNet::Receiver("Dispatcher");
    Interrupt* interrupt = new Interrupt("Dispatcher");
    Actuator* actuator = new Actuator("Actuator");

    std::cout << "Festo is gate: " << std::boolalpha << actuator->isGate() << std::endl;
    actuator->test_outs();

    test_ins();
    //wait(10);
    delete actuator;
    delete interrupt;
    //delete interrupt_buffer;

    cout << "Program Finished." << endl;
    return 0;
}
