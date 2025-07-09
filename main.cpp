#include "Timer.h"
#include "Context.h"
#include "Mock_PM.h"
#include "Event.h"
#include "Modehandler.h"

#include "Timer.h"
#include "Logic.h"
#include "Boot.h"
#include "SimulatePiece.h"
#include "Piece.h"
#include "ReadyForPiece.h"
#include "Fsm.h"

#include <iostream>

#define ONE_MILLISECOND 1000

#define EXPECT_STATE(expected_state) \
    do { \
        WAIT(50); \
        std::string is_state = logic->show_state(); \
        EXPECT_EQ(is_state, expected_state); \
    } while (0)

#define EXPECT_STATE_CONTAINS(expected_state) \
    do { \
        WAIT(50); \
        std::string is_state = logic->show_state(); \
        EXPECT_NE(is_state.find(expected_state), std::string::npos) \
            << "Expected state to contain: '" << expected_state \
            << "' but got: '" << is_state << "'"; \
    } while (0)


#define EXPECT_STATE_INSTANT(expected_state) \
    do { \
        WAIT(10); \
        std::string is_state = logic->show_state(); \
        EXPECT_EQ(is_state, expected_state); \
    } while (0)

#define ONE_MILLISECOND 1000

using namespace std;



int main() {
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

    //wait till piece is picked up
    WAIT(2000);
    DEBUG(">>>>>>>>>>>>>>>>>>>>>>>>>>> LASER BACK UNBLOCKED <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_BACK_UNBLOCKED);
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
