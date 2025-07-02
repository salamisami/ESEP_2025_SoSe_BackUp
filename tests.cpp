#include "Timer.h"
#include "Context.h"
#include "IdleMode.h"
#include "Mock_PM.h"
#include "Event.h"
#include "ModeHandler.h"
#include "Timer.h"
#include "Logic.h"
#include "SortingOrder.h"
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

class SubRealImplementationTesting : public LogicBaseTest<SortingOrder> {
protected:
    void SetUp() override {
        LogicBaseTest<SortingOrder>::SetUp();
    }
};

// Test fixture with IdleMode as initial state
class DeepHistorySetup : public LogicBaseTest<IdleMock> {
protected:
    void SetUp() override {
        LogicBaseTest<IdleMock>::SetUp();
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

TEST_F(SubRealImplementationTesting, SortingOrderPositiveTest) {
    EXPECT_STATE("PieceFlat");
    data->is_ramp_full = false;
    remote_control->send_event((int8_t) Topic::CHECK_PIECE, (int) CheckPiece_Enum::FLAT);
    EXPECT_STATE("PieceTall");
    data->is_ramp_full = false;
    
    remote_control->send_event((int8_t) Topic::CHECK_PIECE, (int) CheckPiece_Enum::TALL);
    EXPECT_STATE("PieceTallWithMetal");
    data->is_ramp_full = false;
    remote_control->send_event((int8_t) Topic::CHECK_PIECE, (int) CheckPiece_Enum::TALL_WITH_METAL);
    EXPECT_STATE("PieceFlat");
}

TEST_F(SubRealImplementationTesting, SortingOrderNegativeTest) {
    //test PieceFlat
    EXPECT_STATE("PieceFlat");
    data->is_ramp_full = false;
    remote_control->send_event((int8_t) Topic::CHECK_PIECE, (int) CheckPiece_Enum::UNKNOWN);
    EXPECT_STATE("PieceFlat");

    //change state to tall
    remote_control->send_event((int8_t) Topic::CHECK_PIECE, (int) CheckPiece_Enum::FLAT);
    EXPECT_STATE("PieceTall");
    //test PieceTall
    remote_control->send_event((int8_t) Topic::CHECK_PIECE, (int) CheckPiece_Enum::UNKNOWN);
    EXPECT_STATE("PieceTall");

    //change state to tall metal
    remote_control->send_event((int8_t) Topic::CHECK_PIECE, (int) CheckPiece_Enum::TALL);
    EXPECT_STATE("PieceTallWithMetal");
    //test PieceWithMetal
    remote_control->send_event((int8_t) Topic::CHECK_PIECE, (int) CheckPiece_Enum::UNKNOWN);
    EXPECT_STATE("PieceTallWithMetal");

    //change state to flat
    remote_control->send_event((int8_t) Topic::CHECK_PIECE, (int) CheckPiece_Enum::TALL_WITH_METAL);
    EXPECT_STATE("PieceFlat");
    //test PieceWithMetal
    remote_control->send_event((int8_t) Topic::CHECK_PIECE, (int) CheckPiece_Enum::UNKNOWN);
    EXPECT_STATE("PieceFlat");
}


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



int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}