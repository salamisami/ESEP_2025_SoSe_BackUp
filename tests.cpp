#include "Timer.h"
#include "Context.h"
#include "IdleMode.h"
#include "Mock_PM.h"
#include "Event.h"
#include "ModeHandler.h"
#include "Timer.h"
#include "Logic.h"
#include <gtest/gtest.h>

#define EXPECT_STATE(expected_state) \
    do { \
        WAIT(10); \
        std::string is_state = logic->show_state(); \
        EXPECT_EQ(is_state, expected_state); \
    } while (0)

#define ONE_MILLISECOND 1000

using namespace std;

template <typename InitialState>
class LogicBaseTest : public ::testing::Test {
protected:
    Mock_PM::Receiver* logic_receiver;
    Mock_PM::Sender* remote_control;
    Mock_PM::Receiver* hal_receiver;
    Mock_PM::Sender* logic_sender;
    I_Sender* to_self_sender;
    Logic<InitialState>* logic;
    ContextData* data;

    void SetUp() override {
        cout << "Setting up test fixture..." << endl;
        logic_receiver = new Mock_PM::Receiver();
        remote_control = new Mock_PM::Sender(logic_receiver);
        hal_receiver = new Mock_PM::Receiver();
        logic_sender = new Mock_PM::Sender(hal_receiver);
        to_self_sender = new Mock_PM::Sender(logic_receiver);
        data = new ContextData(logic_sender, to_self_sender);
        logic = new Logic<InitialState>(logic_receiver, logic_sender, to_self_sender, data);

        // Boot sequence
        remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::IS_SWITCH);
    }

    void TearDown() override {
        cout << "Tearing down test fixture..." << endl;
        remote_control->send_event((int8_t) Topic::STOP_THREAD, 0);
        WAIT(10);

        delete logic;
        delete data;
        delete to_self_sender;
        delete logic_sender;
        delete hal_receiver;
        delete remote_control;
        delete logic_receiver;
    }
};

// Test fixture with Boot as initial state
class RealImplementationTesting : public LogicBaseTest<Boot> {
protected:
    void SetUp() override {
        LogicBaseTest<Boot>::SetUp();
    }
};

// Test fixture with IdleMode as initial state
class DeepHistorySetup : public LogicBaseTest<IdleMock> {
protected:
    void SetUp() override {
        LogicBaseTest<IdleMock>::SetUp();
    }
};

// Test fixture with IdleMode as initial state
class MotorControlSetup : public LogicBaseTest<MotorControl> {
protected:
    void SetUp() override {
        LogicBaseTest<MotorControl>::SetUp();
    }
};

TEST_F(DeepHistorySetup, DeepHistoryTest) {
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_START_PRESSED);
    WAIT(10);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_START_RELEASED);
    EXPECT_STATE("Green MotorDisable");
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_START_PRESSED);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_START_RELEASED);
    EXPECT_STATE("Yellow MotorDisable");
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_RESET_PRESSED);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_RESET_RELEASED);
    EXPECT_STATE("Yellow MotorEnable");

    //save history
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_STOP_PRESSED);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_STOP_RELEASED);
    WAIT(500);
    EXPECT_STATE("IdleMock");

    //load history
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_START_PRESSED);
    WAIT(10);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_START_RELEASED);
    EXPECT_STATE("Yellow MotorEnable");

    //modify state
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_START_PRESSED);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_START_RELEASED);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_RESET_PRESSED);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_RESET_RELEASED);
    EXPECT_STATE("Red MotorDisable");

    //save history
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_STOP_PRESSED);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_STOP_RELEASED);
    WAIT(500);
    EXPECT_STATE("IdleMock");

    //load history
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_START_PRESSED);
    WAIT(10);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_START_RELEASED);
    EXPECT_STATE("Red MotorDisable");

    //default exit
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_BACK_BLOCKED);
    WAIT(10);
    EXPECT_STATE("IdleMock");

    //entry with zero deep history
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_START_PRESSED);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_START_RELEASED);
    WAIT(10);
    EXPECT_STATE("Green MotorDisable");

}

// TEST_F(RealImplementationTesting, SortingOrderPositiveTest) {
//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_START_PRESSED);
//     WAIT(10);
//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_START_RELEASED);
//     EXPECT_STATE("PieceFlat");
//     data->is_ramp_full = false;
//     data->actual_piece = Piece::FLAT;
//     remote_control->send_event((int8_t) Topic::INTERNAL, (int) Internal_Enum::CHECK_PIECE);
//     EXPECT_STATE("PieceTall");
//     data->is_ramp_full = false;
//     data->actual_piece = Piece::TALL;
//     remote_control->send_event((int8_t) Topic::INTERNAL, (int) Internal_Enum::CHECK_PIECE);
//     EXPECT_STATE("PieceTallWithMetal");
//     data->is_ramp_full = false;
//     data->actual_piece = Piece::TALL_WITH_METAL;
//     remote_control->send_event((int8_t) Topic::INTERNAL, (int) Internal_Enum::CHECK_PIECE);
//     EXPECT_STATE("PieceFlat");
// }

// TEST_F(RealImplementationTesting, SortingOrderNegativeTest) {
//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_START_PRESSED);
//     WAIT(10);
//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_START_RELEASED);

//     //test PieceFlat
//     EXPECT_STATE("PieceFlat");
//     data->is_ramp_full = false;
//     data->actual_piece = Piece::UNKNOWN;
//     remote_control->send_event((int8_t) Topic::INTERNAL, (int) Internal_Enum::CHECK_PIECE);
//     EXPECT_STATE("PieceFlat");

//     //change state to tall
//     data->actual_piece = Piece::FLAT;
//     remote_control->send_event((int8_t) Topic::INTERNAL, (int) Internal_Enum::CHECK_PIECE);
//     EXPECT_STATE("PieceTall");
//     //test PieceTall
//     data->actual_piece = Piece::UNKNOWN;
//     remote_control->send_event((int8_t) Topic::INTERNAL, (int) Internal_Enum::CHECK_PIECE);
//     EXPECT_STATE("PieceTall");

//     //change state to tall metal
//     data->actual_piece = Piece::TALL;
//     remote_control->send_event((int8_t) Topic::INTERNAL, (int) Internal_Enum::CHECK_PIECE);
//     EXPECT_STATE("PieceTallWithMetal");
//     //test PieceWithMetal
//     data->actual_piece = Piece::UNKNOWN;
//     remote_control->send_event((int8_t) Topic::INTERNAL, (int) Internal_Enum::CHECK_PIECE);
//     EXPECT_STATE("PieceTallWithMetal");

//     //change state to flat
//     data->actual_piece = Piece::TALL_WITH_METAL;
//     remote_control->send_event((int8_t) Topic::INTERNAL, (int) Internal_Enum::CHECK_PIECE);
//     EXPECT_STATE("PieceFlat");
//     //test PieceWithMetal
//     data->actual_piece = Piece::UNKNOWN;
//     remote_control->send_event((int8_t) Topic::INTERNAL, (int) Internal_Enum::CHECK_PIECE);
//     EXPECT_STATE("PieceFlat");
// }


/**
 * @brief enter service mode
 */
TEST_F(RealImplementationTesting, ServiceModeFullTest) {
    //go to service mode
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_START_PRESSED);
    WAIT(2100);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_START_RELEASED);
    EXPECT_STATE("IdleSM");

    //put a piece to calibrate the pieces
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_FRONT_BLOCKED);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_FRONT_UNBLOCKED);
    EXPECT_STATE("IdleSMSR IdleSTR");

    // //piece goes to sorting gate
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_BLOCKED);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_UNBLOCKED);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_RAMP_BLOCKED);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_RAMP_UNBLOCKED);
    EXPECT_STATE("IdleSMSR IdleSTR");

    // //assume calibration is done
    remote_control->send_event((int8_t) Topic::ADC, (int) ADC_Enum::ADC_CALIBRATION_DONE);
    //last calibrated piece goes to ramp
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_RAMP_BLOCKED);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_RAMP_UNBLOCKED);
    EXPECT_STATE("ReadyForCDF");

    //calibrate fast mode
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_FRONT_BLOCKED);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_FRONT_UNBLOCKED);
    EXPECT_STATE("StartCDF IdleLPT");
    WAIT(2000);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::ADC_TOP_AREA_BLOCKED);
    WAIT(1000);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::ADC_TOP_AREA_UNBLOCKED);
    WAIT(1000);
    //pieces are let through the gate
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_BLOCKED);
    WAIT(1000);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_UNBLOCKED);
    WAIT(3000);
    // //piece is now at the end of the machine
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_BACK_BLOCKED);
    EXPECT_STATE("EndToGateCRF PusherIdleCRF");

    //the piece goes back
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_BACK_UNBLOCKED);
    WAIT(3000);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_BLOCKED);
    WAIT(1000);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_UNBLOCKED);
    WAIT(1000);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::ADC_TOP_AREA_BLOCKED);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_BLOCKED);
    WAIT(250);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_UNBLOCKED);
    WAIT(750);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_RAMP_BLOCKED);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_RAMP_UNBLOCKED);
    EXPECT_STATE("ReadyForCDS");

    //calibrate slow mode
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_FRONT_BLOCKED);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_FRONT_UNBLOCKED);
    EXPECT_STATE("StartCDS IdleLPT");
    WAIT(2000);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::ADC_TOP_AREA_BLOCKED);
    WAIT(1000);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::ADC_TOP_AREA_UNBLOCKED);
    WAIT(1000);
    //pieces are let through the gate
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_BLOCKED);
    WAIT(1000);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_UNBLOCKED);
    WAIT(3000);
    // //piece is now at the end of the machine
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_BACK_BLOCKED);
    EXPECT_STATE("EndToGateCRS PusherIdleCRS");

    //the piece goes back
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_BACK_UNBLOCKED);
    WAIT(3000);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_BLOCKED);
    WAIT(1000);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_UNBLOCKED);
    WAIT(1000);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::ADC_TOP_AREA_BLOCKED);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_BLOCKED);
    WAIT(250);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_UNBLOCKED);
    WAIT(750);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_RAMP_BLOCKED);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_RAMP_UNBLOCKED);
    EXPECT_STATE("CalibrationFinished");
}

/**
 * @brief enter adc calibration mode, then estop
 */
TEST_F(RealImplementationTesting, AdcCalibrationThenEstop) {
    //go to service mode
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_START_PRESSED);
    WAIT(2100);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_START_RELEASED);
    EXPECT_STATE("IdleSM");

    //put a piece to calibrate the pieces
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_FRONT_BLOCKED);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_FRONT_UNBLOCKED);
    EXPECT_STATE("IdleSMSR IdleSTR");

    // //piece goes to sorting gate
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_BLOCKED);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_UNBLOCKED);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_RAMP_BLOCKED);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_RAMP_UNBLOCKED);
    EXPECT_STATE("IdleSMSR IdleSTR");

    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_ESTOP_PRESSED);
    EXPECT_STATE("EStopViaLocal");
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_ESTOP_RELEASED);
    EXPECT_STATE("EStopReleased");
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_RESET_PRESSED);
    EXPECT_STATE("EStopQuit");
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_RESET_RELEASED);
    EXPECT_STATE("IdleIM");
}

/**
 * @brief enter operating mode, by pressing start button shortly
 */
TEST_F(RealImplementationTesting, ShortTimerTest) {
    //go to service mode
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_START_PRESSED);
    EXPECT_STATE("WaitingIM");
    WAIT(500);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_START_RELEASED);
    EXPECT_STATE("PseudoState");
}

/**
 * @brief enter adc calibration mode, by long pressing start button
 */
TEST_F(RealImplementationTesting, LongTimerTest) {
    //go to service mode
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_START_PRESSED);
    EXPECT_STATE("WaitingIM");
    WAIT(5000);
    EXPECT_STATE("TimerReceivedIM");
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_START_RELEASED);
    EXPECT_STATE("IdleSM");
}

/**
 * @brief Test workpiece state tracking with motor control events
 * Tests that workpiece IDs in motor control events are properly tracked
 */
TEST_F(MotorControlSetup, MotorControlWorkpieceTrackingTest) {

    
    // Test MOTOR_FAST with workpiece ID 1
    remote_control->send_event((int8_t) Topic::MOTOR_FAST, 1); // ID 1
    WAIT(10);
    
    // Verify workpiece 1 is tracked in FAST state
    EXPECT_TRUE(data->workpieceList.contains(1));
    EXPECT_EQ(data->workpieceList.getState(1), MotorPieceState::FAST);
    EXPECT_FALSE(data->workpieces); // List not empty
    EXPECT_EQ(data->workpieceList.size(), 1);
    
    // Test MOTOR_SLOW with workpiece ID 2 - should add new workpiece and update all to SLOW
    remote_control->send_event((int8_t) Topic::MOTOR_SLOW, 2); // ID 2
    WAIT(10);
    
    // Verify both workpieces are in SLOW state
    EXPECT_TRUE(data->workpieceList.contains(1));
    EXPECT_TRUE(data->workpieceList.contains(2));
    EXPECT_EQ(data->workpieceList.getState(1), MotorPieceState::SLOW);
    EXPECT_EQ(data->workpieceList.getState(2), MotorPieceState::SLOW);
    EXPECT_EQ(data->workpieceList.size(), 2);
    
    // Test MOTOR_STOP_FSM with workpiece ID 3 - should add new workpiece and update ALL to STOPPED
    remote_control->send_event((int8_t) Topic::MOTOR_STOP_FSM, 3); // ID 3
    WAIT(10);
    
    // Verify all three workpieces are now in STOPPED state
    EXPECT_TRUE(data->workpieceList.contains(1));
    EXPECT_TRUE(data->workpieceList.contains(2));
    EXPECT_TRUE(data->workpieceList.contains(3));
    EXPECT_EQ(data->workpieceList.getState(1), MotorPieceState::STOPPED);
    EXPECT_EQ(data->workpieceList.getState(2), MotorPieceState::STOPPED);
    EXPECT_EQ(data->workpieceList.getState(3), MotorPieceState::STOPPED);
    EXPECT_EQ(data->workpieceList.size(), 3);
    
    // Test DELETE_W_MOTOR with specific ID - should only remove that workpiece
    remote_control->send_event((int8_t) Topic::DELETE_W_MOTOR, 2); // Remove ID 2
    WAIT(10);
    
    // Verify workpiece 2 was removed, others remain in STOPPED state
    EXPECT_TRUE(data->workpieceList.contains(1));
    EXPECT_FALSE(data->workpieceList.contains(2)); // Removed
    EXPECT_TRUE(data->workpieceList.contains(3));
    EXPECT_EQ(data->workpieceList.getState(1), MotorPieceState::STOPPED);
    EXPECT_EQ(data->workpieceList.getState(3), MotorPieceState::STOPPED);
    EXPECT_EQ(data->workpieceList.size(), 2);
    
    // Test transition back to FAST with new workpiece
    remote_control->send_event((int8_t) Topic::MOTOR_FAST, 4); // ID 4
    WAIT(10);
    
    // Verify all workpieces (including new one) are now in FAST state
    EXPECT_TRUE(data->workpieceList.contains(1));
    EXPECT_TRUE(data->workpieceList.contains(3));
    EXPECT_TRUE(data->workpieceList.contains(4));
    EXPECT_EQ(data->workpieceList.getState(1), MotorPieceState::FAST);
    EXPECT_EQ(data->workpieceList.getState(3), MotorPieceState::FAST);
    EXPECT_EQ(data->workpieceList.getState(4), MotorPieceState::FAST);
    EXPECT_EQ(data->workpieceList.size(), 3);
}

/**
 * @brief Test complete workpiece lifecycle with motor control
 */
TEST_F(RealImplementationTesting, WorkpieceLifecycleTest) {
    // Enter operating mode
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_START_PRESSED);
    WAIT(500);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_START_RELEASED);
    EXPECT_STATE("PseudoState");
    
    // Simulate complete workpiece lifecycle:
    // 1. Workpiece enters system -> FAST
    remote_control->send_event((int8_t) Topic::MOTOR_FAST, 100);
    WAIT(10);
    EXPECT_TRUE(data->workpieceList.contains(100));
    EXPECT_EQ(data->workpieceList.getState(100), MotorPieceState::FAST);
    
    // 2. System slows down -> SLOW
    remote_control->send_event((int8_t) Topic::MOTOR_SLOW, 100);
    WAIT(10);
    EXPECT_EQ(data->workpieceList.getState(100), MotorPieceState::SLOW);
    
    // 3. System needs to stop -> STOPPED
    remote_control->send_event((int8_t) Topic::MOTOR_STOP_FSM, 100);
    WAIT(10);
    EXPECT_EQ(data->workpieceList.getState(100), MotorPieceState::STOPPED);
    
    // 4. System resumes -> FAST
    remote_control->send_event((int8_t) Topic::MOTOR_FAST, 100);
    WAIT(10);
    EXPECT_EQ(data->workpieceList.getState(100), MotorPieceState::FAST);
    
    // 5. Workpiece leaves system -> DELETE
    remote_control->send_event((int8_t) Topic::DELETE_W_MOTOR, 100);
    WAIT(10);
    EXPECT_FALSE(data->workpieceList.contains(100));
    EXPECT_TRUE(data->workpieceList.isEmpty());
    EXPECT_TRUE(data->workpieces); // Should be true when list is empty
}

/**
 * @brief Test multiple workpieces with overlapping motor control events
 */
TEST_F(RealImplementationTesting, MultipleWorkpiecesOverlappingTest) {
    // Enter operating mode
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_START_PRESSED);
    WAIT(500);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_START_RELEASED);
    EXPECT_STATE("PseudoState");
    
    // Add workpieces at different times
    remote_control->send_event((int8_t) Topic::MOTOR_FAST, 201);
    WAIT(10);
    
    remote_control->send_event((int8_t) Topic::MOTOR_FAST, 202);
    WAIT(10);
    
    remote_control->send_event((int8_t) Topic::MOTOR_SLOW, 203); // This should change ALL to SLOW
    WAIT(10);
    
    // Verify all workpieces are in SLOW state
    EXPECT_EQ(data->workpieceList.getState(201), MotorPieceState::SLOW);
    EXPECT_EQ(data->workpieceList.getState(202), MotorPieceState::SLOW);
    EXPECT_EQ(data->workpieceList.getState(203), MotorPieceState::SLOW);
    
    // Add more workpieces while in SLOW
    remote_control->send_event((int8_t) Topic::MOTOR_SLOW, 204);
    WAIT(10);
    
    // All should still be SLOW
    EXPECT_EQ(data->workpieceList.getState(201), MotorPieceState::SLOW);
    EXPECT_EQ(data->workpieceList.getState(202), MotorPieceState::SLOW);
    EXPECT_EQ(data->workpieceList.getState(203), MotorPieceState::SLOW);
    EXPECT_EQ(data->workpieceList.getState(204), MotorPieceState::SLOW);
    
    // Remove some workpieces
    remote_control->send_event((int8_t) Topic::DELETE_W_MOTOR, 202);
    WAIT(10);
    remote_control->send_event((int8_t) Topic::DELETE_W_MOTOR, 204);
    WAIT(10);
    
    // Verify correct workpieces removed
    EXPECT_TRUE(data->workpieceList.contains(201));
    EXPECT_FALSE(data->workpieceList.contains(202));
    EXPECT_TRUE(data->workpieceList.contains(203));
    EXPECT_FALSE(data->workpieceList.contains(204));
    EXPECT_EQ(data->workpieceList.size(), 2);
    
    // Change to STOPPED
    remote_control->send_event((int8_t) Topic::MOTOR_STOP_FSM, 205); // Add new and change all
    WAIT(10);
    
    // Verify all remaining workpieces are STOPPED
    EXPECT_EQ(data->workpieceList.getState(201), MotorPieceState::STOPPED);
    EXPECT_EQ(data->workpieceList.getState(203), MotorPieceState::STOPPED);
    EXPECT_EQ(data->workpieceList.getState(205), MotorPieceState::STOPPED);
    EXPECT_EQ(data->workpieceList.size(), 3);
}

/**
 * @brief Test edge cases in motor control workpiece management
 */
TEST_F(RealImplementationTesting, MotorControlEdgeCasesTest) {
    // Enter operating mode
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_START_PRESSED);
    WAIT(500);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_START_RELEASED);
    EXPECT_STATE("PseudoState");
    
    // Test adding same ID multiple times (should not duplicate)
    remote_control->send_event((int8_t) Topic::MOTOR_FAST, 1);
    WAIT(10);
    
    // Try to add same ID again with different state
    remote_control->send_event((int8_t) Topic::MOTOR_SLOW, 1);
    WAIT(10);
    
    // Should only have one instance, in SLOW state
    EXPECT_TRUE(data->workpieceList.contains(1));
    EXPECT_EQ(data->workpieceList.getState(1), MotorPieceState::SLOW);
    EXPECT_EQ(data->workpieceList.size(), 1);
    
    // Test deleting non-existent ID (should not crash)
    remote_control->send_event((int8_t) Topic::DELETE_W_MOTOR, 999); // Non-existent ID
    WAIT(10);
    
    // Original workpiece should still be there
    EXPECT_TRUE(data->workpieceList.contains(1));
    EXPECT_EQ(data->workpieceList.size(), 1);
    
    // Test empty list behavior
    remote_control->send_event((int8_t) Topic::DELETE_W_MOTOR, 1);
    WAIT(10);
    
    // List should be empty
    EXPECT_TRUE(data->workpieceList.isEmpty());
    EXPECT_TRUE(data->workpieces);
    EXPECT_EQ(data->workpieceList.size(), 0);
    
    // Test state transitions with empty list
    remote_control->send_event((int8_t) Topic::MOTOR_FAST, 2);
    WAIT(10);
    
    // Should add new workpiece
    EXPECT_TRUE(data->workpieceList.contains(2));
    EXPECT_EQ(data->workpieceList.getState(2), MotorPieceState::FAST);
    EXPECT_FALSE(data->workpieces); // No longer empty
    EXPECT_EQ(data->workpieceList.size(), 1);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
