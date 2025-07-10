#include "Timer.h"
#include "Logic.h"
#include "Event.h"
#include "Boot.h"
#include "EStopTest.h"
#include "SimulatePiece.h"
#include "Piece.h"
#include "ReadyForPiece.h"
#include "Fsm.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <unistd.h>
#include <csignal>
#include <atomic>


#define ONE_MILLISECOND 1000
#define COUT(msg) std::cout << msg << std::endl
using namespace std;


#define ONE_MILLISECOND 1000

using namespace std;

int main() {

    //std::thread inputThread(wait_for_enter);

    cout << "Starting Program..." << endl; // prints Hello World!!!

    Mock_PM::Receiver* logic_receiver;
    Mock_PM::Sender* remote_control;
    Mock_PM::Receiver* hal_receiver;
    Mock_PM::Sender* logic_sender;
    I_Sender* to_self_sender;

    ContextData* data;

    logic_receiver = new Mock_PM::Receiver();
    remote_control = new Mock_PM::Sender(logic_receiver);
    hal_receiver = new Mock_PM::Receiver();
    logic_sender = new Mock_PM::Sender(hal_receiver);
    to_self_sender = new Mock_PM::Sender(logic_receiver);
    data = new ContextData(to_self_sender);

    TimeProfile profile = {
        .fast_timestamps = { 2000, 2100, 3600, 4000, 6000, 3800 },
        .slow_timestamps = { 6060, 7183, 10309, 11780, 17207, 10552 }
        // deadlines will be automatically initialized to 0
    };

    TimeProfileManager::save_profile(profile, SAVE_LOCATION_TIMEPROFILE);
    TimeProfileManager::convert_to_deadlines(&profile);

    data->timeprofile = profile;


    auto logic = new Logic<Fsm>(logic_receiver, to_self_sender, data);


    // Boot sequence
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::IS_SWITCH);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_START_PRESSED);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_START_RELEASED);

    WAIT(2000);


    DEBUG(">>>>>>>>>>>>>>>>>>>>>>>>>>> LASER FRONT BLOCKED <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_FRONT_BLOCKED);
    WAIT(1000);
    DEBUG(">>>>>>>>>>>>>>>>>>>>>>>>>>> LASER FRONT UNBLOCKED <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_FRONT_UNBLOCKED);

    WAIT(2000);

    DEBUG(">>>>>>>>>>>>>>>>>>>>>>>>>>> ADC BEGIN <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::ADC_TOP_AREA_BLOCKED);
    remote_control->send_event((int8_t) Topic::ADC, (int) ADC_Enum::ADC_NEW_PIECE);
    WAIT(1123);
    DEBUG(">>>>>>>>>>>>>>>>>>>>>>>>>>> ADC END (PIECE FLAT) <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
    remote_control->send_event((int8_t) Topic::ADC, (int) ADC_Enum::ADC_WF_DETECT);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::ADC_TOP_AREA_UNBLOCKED);


    // DEBUG(">>>>>>>>>>>>>>>>>>>>>>>>>>> [MUST ERROR] LASER BACK BLOCKED <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
    // remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_BACK_BLOCKED);
    // remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_BACK_UNBLOCKED);

    WAIT(1500);
    DEBUG(">>>>>>>>>>>>>>>>>>>>>>>>>>> LASER SORTING BLOCKED <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_BLOCKED);
    WAIT(400);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_UNBLOCKED);
    DEBUG(">>>>>>>>>>>>>>>>>>>>>>>>>>> LASER SORTING UNBLOCKED <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
    WAIT(2000);
    DEBUG(">>>>>>>>>>>>>>>>>>>>>>>>>>> LASER BACK BLOCKED <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_BACK_BLOCKED);

    //wait till piece is picked up
    WAIT(2000);
    DEBUG(">>>>>>>>>>>>>>>>>>>>>>>>>>> LASER BACK UNBLOCKED <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_BACK_UNBLOCKED);
    WAIT(1000);










    DEBUG("SECOND PIECE");









    DEBUG(">>>>>>>>>>>>>>>>>>>>>>>>>>> LASER FRONT BLOCKED <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_FRONT_BLOCKED);
    WAIT(1000);
    DEBUG(">>>>>>>>>>>>>>>>>>>>>>>>>>> LASER FRONT UNBLOCKED <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_FRONT_UNBLOCKED);

    WAIT(2000);

    DEBUG(">>>>>>>>>>>>>>>>>>>>>>>>>>> ADC BEGIN <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::ADC_TOP_AREA_BLOCKED);
    remote_control->send_event((int8_t) Topic::ADC, (int) ADC_Enum::ADC_NEW_PIECE);
    WAIT(1123);
    DEBUG(">>>>>>>>>>>>>>>>>>>>>>>>>>> ADC END (PIECE HOLE) <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
    remote_control->send_event((int8_t) Topic::ADC, (int) ADC_Enum::ADC_W_B_DETECT);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::ADC_TOP_AREA_UNBLOCKED);


    // DEBUG(">>>>>>>>>>>>>>>>>>>>>>>>>>> [MUST ERROR] LASER BACK BLOCKED <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
    // remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_BACK_BLOCKED);
    // remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_BACK_UNBLOCKED);

    WAIT(1500);
    DEBUG(">>>>>>>>>>>>>>>>>>>>>>>>>>> LASER SORTING BLOCKED <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_BLOCKED);
    WAIT(400);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_UNBLOCKED);
    DEBUG(">>>>>>>>>>>>>>>>>>>>>>>>>>> LASER SORTING UNBLOCKED <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
    WAIT(2000);
    DEBUG(">>>>>>>>>>>>>>>>>>>>>>>>>>> LASER BACK BLOCKED <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_BACK_BLOCKED);

    DEBUG(">>>>>>>>>>>>>>>>>>>>>>>>>>>  FBM 2 READY <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
    remote_control->send_event((int8_t) Topic::COM, (int) COM_Enum::FBM_2_READY);

    //wait till piece is picked up
    WAIT(2000);
    DEBUG(">>>>>>>>>>>>>>>>>>>>>>>>>>> TRANSFER DONE <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
    remote_control->send_event((int8_t) Topic::COM, (int) COM_Enum::TRANSFER_DONE);

    WAIT(1000);


    delete logic;
    delete data;
    delete to_self_sender;
    delete logic_sender;
    delete hal_receiver;
    delete remote_control;
    delete logic_receiver;

    cout << "Program Finished." << endl;
    return 0;


}
