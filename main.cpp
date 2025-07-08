#include "HAL.h"
#include "Dispatcher.h"
#include "Thread_COM.h"
#include "Recorder.h"
#include "COM.h"
#include "Timer.h"
#include "Logic.h"
#include "Event.h"
#include "Remote_Controller.h"
#include "Boot.h"
#include "EStopTest.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <unistd.h>
#include <csignal>
#include <atomic>

#include "inc/MQTT/MQTT_Utilities.h"
#define ONE_MILLISECOND 1000
#define COUT(msg) std::cout << msg << std::endl
using namespace std;

int main()
{

    // std::thread inputThread(wait_for_enter);

    cout << "Starting Program..." << endl; // prints Hello World!!!
    system("slay gns");
#ifdef FBM_1
    system("gns -s ");
#else
    system("gns -c");
#endif

    Dispatcher *dispatcher = new Dispatcher();
    std::thread dispatcher_thread = std::thread(&Dispatcher::run_dispatcher, dispatcher);

     Thread_COM::Receiver* fsm_receiver = new Thread_COM::Receiver(FBM_N_FSM);
    Thread_COM::Sender *fsm_sender = new Thread_COM::Sender(FBM_N_DISPATCHER);
    // Thread_COM::Receiver* recorder_receiver = new Thread_COM::Receiver(FBM_N_RECORDER); //comment this to test without recorder
    // Thread_COM::Sender* recorder_sender = new Thread_COM::Sender(FBM_N_DISPATCHER);

    // Thread_COM::Receiver* RemCon_receiver = new Thread_COM::Receiver(FBM_N_REMOTE); //comment this to test without RC
    // Thread_COM::Sender* RemCon_sender = new Thread_COM::Sender(FBM_N_DISPATCHER);

    Thread_COM::Sender *com_sender_local = new Thread_COM::Sender(FBM_N_DISPATCHER);
    Thread_COM::Receiver *com_external_receiver = new Thread_COM::Receiver(FBM_N_COM);
    Thread_COM::Receiver *com_receiver_local = new Thread_COM::Receiver(FBM_N_COM_RECEIVER);

    // Thread_COM::Receiver* hal_receiver = new Thread_COM::Receiver(FBM_N_HAL);
    // Thread_COM::Sender* hal_sender = new Thread_COM::Sender(FBM_N_DISPATCHER);

    // auto logic = new Logic<Boot>(fsm_receiver, fsm_sender);
    // Recorder* rec = new Recorder(recorder_receiver, recorder_sender);
    // Remote_Controller* remcon = new Remote_Controller(RemCon_receiver, RemCon_sender); //comment this to test without RC
    COM *externCommunication = new COM(com_external_receiver, FBM_N_COM_EXT, com_receiver_local, com_sender_local);
    externCommunication->start();
    // HAL* hal = new HAL(hal_receiver, hal_sender);

    // while(Remote_Controller::Main_running) {
    // 	//std::this_thread::sleep_for(std::chrono::milliseconds(100));
    // }

   
class SenderThread {
public:
    std::atomic<int> sent_count{0};
    bool running = false;
    std::thread thread;
    I_Sender *fsm_sender;
    explicit SenderThread(I_Sender *send) : fsm_sender(send) {}

    void start() {
        running = true;
        thread = std::thread([this](){ run(); });
    }

    void stop() {
        running = false;
        if (thread.joinable()) thread.join();
    }

private:
    void run() {
        while (running) {
            {
                // Example send
                fsm_sender->send_event(
                    static_cast<int8_t>(Topic::INTERRUPT),
                    static_cast<int>(InterruptEnum::BUTTON_START_PRESSED));
                sent_count++;

                // Add short delay between events (simulate processing time)
                std::this_thread::sleep_for(std::chrono::microseconds(50)); // 50μs

                fsm_sender->send_event(
                    static_cast<int8_t>(Topic::INTERRUPT),
                    static_cast<int>(InterruptEnum::BUTTON_START_RELEASED));
                sent_count++;
                std::this_thread::sleep_for(std::chrono::microseconds(50));

                // Send COM events
                fsm_sender->send_event(
                    static_cast<int8_t>(Topic::COM),
                    static_cast<int>(COM_Enum::BUTTON_ESTOP_PRESSED));
                sent_count++;
                std::this_thread::sleep_for(std::chrono::microseconds(50));

                // Send INTERNAL events
                fsm_sender->send_event(
                    static_cast<int8_t>(Topic::INTERNAL),
                    static_cast<int>(Internal_Enum::SORT_OUT));

                // Main loop delay - adjust based on processor speed
                std::this_thread::sleep_for(std::chrono::milliseconds(10)); // 10ms (100Hz)
                sent_count++;
            }
        }
    };
};
    
class ReceiverThread {
public:
    std::atomic<int> received_count{0};
    bool running = false;
    std::thread thread;
    I_Receiver *receiver;

    explicit ReceiverThread(I_Receiver *recv) : receiver(recv) {}

    void start() {
        running = true;
        thread = std::thread([this](){ run(); });
    }

    void stop() {
        running = false;
        if (thread.joinable()) thread.join();
    }

private:
    void run() {
        _pulse event;
        while (running) {
            if (receiver->receive_event(&event) >= 0) {
                received_count++;
            }
            std::this_thread::sleep_for(std::chrono::microseconds(100));
        }
    }
};
    SenderThread sender(fsm_sender);
    ReceiverThread receiver(fsm_receiver);

    sender.start();
    receiver.start();

    // Let it run for some time
    std::this_thread::sleep_for(std::chrono::seconds(5));

    sender.stop();
    receiver.stop();

    std::cout << "Stats:\n"
              << "  Sent: " << sender.sent_count << " messages\n"
              << "  Received: " << receiver.received_count << " messages\n";
              

// delete hal;
// delete rec;
// delete logic;
delete externCommunication;
// delete remcon;

// delete RemCon_receiver;
// delete RemCon_sender;
// delete recorder_receiver;
// delete recorder_sender;
// delete hal_sender;
delete fsm_sender;
// delete fsm_receiver;
// delete hal_receiver;

cout << "Program Finished." << endl;
return 0;
}
