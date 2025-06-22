#include "Timer.h"
#include "Context.h"
#include "IdleMode.h"
#include "Mock_PM.h"
#include "Event.h"
#include "ModeHandler.h"
#include "Timer.h"
#include "Logic.h"
#include <gtest/gtest.h>

#define ONE_MILLISECOND 1000

using namespace std;

class LogicStateTest : public ::testing::Test {
protected:
    Mock_PM::Receiver* logic_receiver;
    Mock_PM::Sender* remote_control;
    Mock_PM::Receiver* hal_receiver;
    Mock_PM::Sender* logic_sender;
    I_Sender* to_self_sender;
    Logic* logic;

    void SetUp() override {
        cout << "Setting up test fixture..." << endl;
        logic_receiver = new Mock_PM::Receiver();
        remote_control = new Mock_PM::Sender(logic_receiver);
        hal_receiver = new Mock_PM::Receiver();
        logic_sender = new Mock_PM::Sender(hal_receiver);
        to_self_sender = new Mock_PM::Sender(logic_receiver);
        logic = new Logic(logic_receiver, logic_sender, to_self_sender);

        // Boot sequence
        remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::IS_SWITCH);
    }

    void TearDown() override {
        cout << "Tearing down test fixture..." << endl;
        remote_control->send_event((int8_t) Topic::STOP_THREAD, 0);
        WAIT(10);

        delete logic;
        delete to_self_sender;
        delete logic_sender;
        delete hal_receiver;
        delete remote_control;
        delete logic_receiver;
    }

    void expect_state(const std::string& expected_state) {
        WAIT(1);
        std::string is_state = logic->show_state();
        EXPECT_EQ(is_state, expected_state); // << "Expected: " << expected_state << " but got: " << is_state;
    }
};

TEST_F(LogicStateTest, PieceTrackingTest) {
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_START_PRESSED);
    WAIT(500);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_START_RELEASED);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_FRONT_BLOCKED);

    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_FRONT_UNBLOCKED);
    WAIT(2000);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::ADC_TOP_AREA_BLOCKED);
    WAIT(100);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::ADC_TOP_AREA_UNBLOCKED);
    WAIT(1500);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_BLOCKED);
    WAIT(400);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_UNBLOCKED);
    WAIT(2000);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_BACK_BLOCKED);
    expect_state("Abc");
}


/**
 * @brief enter service mode
 */
// TEST_F(LogicStateTest, ServiceModeFullTest) {
//     //go to service mode
//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_START_PRESSED);
//     WAIT(2100);
//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_START_RELEASED);
//     expect_state("IdleSM");

//     //put a piece to calibrate the pieces
//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_FRONT_BLOCKED);
//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_FRONT_UNBLOCKED);
//     expect_state("ServiceModeSendRamp");
    
//     // //piece goes to sorting gate
//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_BLOCKED);
//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_UNBLOCKED);
//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_RAMP_BLOCKED);
//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_RAMP_UNBLOCKED);
//     expect_state("ServiceModeSendRamp");

//     // //assume calibration is done
//     remote_control->send_event((int8_t) Topic::ADC, (int) ADC_Enum::ADC_CALIBRATION_DONE);
//     //last calibrated piece goes to ramp
//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_RAMP_BLOCKED);
//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_RAMP_UNBLOCKED);
//     expect_state("ReadyForCDF");

//     //calibrate fast mode
//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_FRONT_BLOCKED);
//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_FRONT_UNBLOCKED);
//     expect_state("CalDistanceFast");
//     WAIT(2000);
//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::ADC_TOP_AREA_BLOCKED);
//     WAIT(1000);
//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::ADC_TOP_AREA_UNBLOCKED);
//     WAIT(1000);
//     //pieces are let through the gate
//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_BLOCKED);
//     WAIT(1000);
//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_UNBLOCKED);
//     WAIT(3000);
//     // //piece is now at the end of the machine
//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_BACK_BLOCKED);
//     expect_state("CalRampFast");

//     //the piece goes back
//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_BACK_UNBLOCKED);
//     WAIT(3000);
//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_BLOCKED);
//     WAIT(1000);
//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_UNBLOCKED);
//     WAIT(1000);
//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::ADC_TOP_AREA_BLOCKED);
//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_BLOCKED);
//     WAIT(250);
//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_UNBLOCKED);
//     WAIT(750);
//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_RAMP_BLOCKED);
//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_RAMP_UNBLOCKED);
//     expect_state("ReadyForCDS");

//     //calibrate slow mode
//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_FRONT_BLOCKED);
//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_FRONT_UNBLOCKED);
//     expect_state("CalDistanceSlow");
//     WAIT(2000);
//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::ADC_TOP_AREA_BLOCKED);
//     WAIT(1000);
//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::ADC_TOP_AREA_UNBLOCKED);
//     WAIT(1000);
//     //pieces are let through the gate
//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_BLOCKED);
//     WAIT(1000);
//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_UNBLOCKED);
//     WAIT(3000);
//     // //piece is now at the end of the machine
//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_BACK_BLOCKED);
//     expect_state("CalRampSlow");

//     //the piece goes back
//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_BACK_UNBLOCKED);
//     WAIT(3000);
//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_BLOCKED);
//     WAIT(1000);
//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_UNBLOCKED);
//     WAIT(1000);
//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::ADC_TOP_AREA_BLOCKED);
//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_BLOCKED);
//     WAIT(250);
//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_UNBLOCKED);
//     WAIT(750);
//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_RAMP_BLOCKED);
//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_RAMP_UNBLOCKED);
//     expect_state("CalibrationFinished");
// }

/**
 * @brief enter adc calibration mode, then estop
 */
TEST_F(LogicStateTest, AdcCalibrationThenEstop) {
    //go to service mode
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_START_PRESSED);
    WAIT(2100);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_START_RELEASED);
    expect_state("IdleSM");

    //put a piece to calibrate the pieces
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_FRONT_BLOCKED);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_FRONT_UNBLOCKED);
    expect_state("ServiceModeSendRamp");
    
    // //piece goes to sorting gate
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_BLOCKED);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_UNBLOCKED);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_RAMP_BLOCKED);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_RAMP_UNBLOCKED);
    expect_state("ServiceModeSendRamp");

    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_ESTOP_PRESSED);
    expect_state("EStopViaLocal");
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_ESTOP_RELEASED);
    expect_state("EStopReleased");
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_RESET_PRESSED);
    expect_state("EStopQuit");
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_RESET_RELEASED);
    expect_state("IdleIM");
}

/**
 * @brief enter operating mode, by pressing start button shortly
 */
TEST_F(LogicStateTest, ShortTimerTest) {
    //go to service mode
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_START_PRESSED);
    expect_state("WaitingIM");
    WAIT(500);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_START_RELEASED);
    expect_state("IdleTest");
}

/**
 * @brief enter adc calibration mode, by long pressing start button
 */
TEST_F(LogicStateTest, LongTimerTest) {
    //go to service mode
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_START_PRESSED);
    expect_state("WaitingIM");
    WAIT(5000);
    expect_state("TimerReceivedIM");
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_START_RELEASED);
    expect_state("IdleSM");
}



int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}