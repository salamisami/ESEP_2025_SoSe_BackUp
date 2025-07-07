#include "Timer.h"
#include "Context.h"
#include "Mock_PM.h"
#include "MotorControl.h"
#include "PieceControllerFBM1.h"
#include "Event.h"
#include "Modehandler.h"
#include "Timer.h"
#include "Logic.h"
#include "SortingOrder.h"
#include "SimulatePiece.h"
#include "ReadyForPiece.h"
#include "CalibNoWarning.h"
#include "COMNoError.h"
#include "ValidMeasure.h"
#include "MQTTNoError.h"
#include "PieceAppearedNoError.h"
#include "PieceLostNoError.h"
#include "RampNoError.h"
#include "ReplayNoWarning.h"
#include "IdleMock.h"
#include <gtest/gtest.h>

#define EXPECT_STATE(expected_state) \
    do { \
        WAIT(20); \
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

        // Initialize time profiles
        TimeProfile both_profiles;

        // Set fast timestamps
        long fast_profile[TIMESTAMP_LENGTH] = { 2000, 2100, 3600, 4000, 6000, 3800 };
        for(int i = 0; i < TIMESTAMP_LENGTH; i++) {
            both_profiles.fast_timestamps[i] = fast_profile[i];
        }

        // Set slow timestamps
        long slow_profile[TIMESTAMP_LENGTH] = { 6060, 7183, 10309, 11780, 17207, 10552 };
        for(int i = 0; i < TIMESTAMP_LENGTH; i++) {
            both_profiles.slow_timestamps[i] = slow_profile[i];
        }

        // Save the profile
        TimeProfileManager::save_profile(both_profiles, SAVE_LOCATION_TIMEPROFILE);
        TimeProfileManager::convert_to_deadlines(&both_profiles);


        logic_receiver = new Mock_PM::Receiver();
        remote_control = new Mock_PM::Sender(logic_receiver);
        hal_receiver = new Mock_PM::Receiver();
        logic_sender = new Mock_PM::Sender(hal_receiver);
        to_self_sender = new Mock_PM::Sender(logic_receiver);
        data = new ContextData(to_self_sender);
        logic = new Logic<InitialState>(logic_receiver, to_self_sender, data);

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
class RealImplementationSetup : public LogicBaseTest<Boot> {
protected:
    void SetUp() override {
        LogicBaseTest<Boot>::SetUp();
    }
};

class SortingOrderSetup : public LogicBaseTest<SortingOrder> {
protected:
    void SetUp() override {
        LogicBaseTest<SortingOrder>::SetUp();
    }
};

class PieceTrackingFBM1Setup : public LogicBaseTest<PieceControllerFBM1> {
protected:
    void SetUp() override {
        LogicBaseTest<PieceControllerFBM1>::SetUp();
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

class PieceTrackerSetup : public LogicBaseTest<PieceControllerFBM1> {
protected:
    void SetUp() override {
        LogicBaseTest<PieceControllerFBM1>::SetUp();
    }
};

// Test FBM2-Setup
class FBM2Setup : public LogicBaseTest<ReadyForPiece> {
protected:
    void SetUp() override {
        LogicBaseTest<ReadyForPiece>::SetUp();
    }
};



//Tests-Setups für ErrorHandler
class CalibrationFileWarningHandlerSetup : public LogicBaseTest<CalibNoWarning> {
protected:
    void SetUp() override {
        LogicBaseTest<CalibNoWarning>::SetUp();
    }
};

class COMErrorHandlerSetup : public LogicBaseTest<COMNoError> {
protected:
    void SetUp() override {
        LogicBaseTest<COMNoError>::SetUp();
    }
};

class InvalidMeasurementHandlerSetup : public LogicBaseTest<ValidMeasure> {
protected:
    void SetUp() override {
        LogicBaseTest<ValidMeasure>::SetUp();
    }
};

class MQTTErrorHandlerSetup : public LogicBaseTest<MQTTNoError> {
protected:
    void SetUp() override {
        LogicBaseTest<MQTTNoError>::SetUp();
    }
};

class PieceAppearedHandlerSetup : public LogicBaseTest<PieceAppearedNoError> {
protected:
    void SetUp() override {
        LogicBaseTest<PieceAppearedNoError>::SetUp();
    }
};

class PieceLostHandlerSetup : public LogicBaseTest<PieceLostNoError> {
protected:
    void SetUp() override {
        LogicBaseTest<PieceLostNoError>::SetUp();
    }
};

class RampErrorHandlerSetup : public LogicBaseTest<RampNoError> {
protected:
    void SetUp() override {
        LogicBaseTest<RampNoError>::SetUp();
    }
};

class ReplayFileWarningHandlerSetup : public LogicBaseTest<ReplayNoWarning> {
protected:
    void SetUp() override {
        LogicBaseTest<ReplayNoWarning>::SetUp();
    }
};

/* TEST_F(PieceTrackerSetup, PieceTrackerTest){
    EXPECT_STATE("PieceControllerFBM1");
    remote_control->send_event((int8_t) Topic::INTERNAL, (int) Internal_Enum::NEW_PIECE);
    EXPECT_STATE("Start_PT1");
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_FRONT_UNBLOCKED);
    EXPECT_STATE("StartADC_PT1");
}
    */

    // TEST_F(LogicBaseTest, PieceTrackingTest) {
    //     data->piece_tracker.debug = true;
    //     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_FRONT_BLOCKED);
    //     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_FRONT_UNBLOCKED);
    //     WAIT(2000);
    //     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::ADC_TOP_AREA_BLOCKED);
    //     WAIT(100);
    //     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::ADC_TOP_AREA_UNBLOCKED);
    //     WAIT(1500);
    //     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_BLOCKED);
    //     WAIT(400);
    //     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_UNBLOCKED);
    //     WAIT(2000);
    //     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_BACK_BLOCKED);    
    //     WAIT(1000);
    //     auto distance = data->piece_tracker.get_distance();
    //     EXPECT_EQ(distance.first, Area::GATE_END);
    //     EXPECT_GT(distance.second, 95);
    // }

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

    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_BACK_BLOCKED);
    EXPECT_STATE("Red");
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_FRONT_BLOCKED);
    EXPECT_STATE("IdleMock");
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_START_PRESSED);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_START_RELEASED);
    EXPECT_STATE("Green MotorDisable");
}

//TODO sporadisch funktioniert
TEST_F(RealImplementationSetup, PutNewPiece) {
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_START_PRESSED);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_START_RELEASED);
    EXPECT_STATE("PieceControllerFBM1 Idle PieceFlat StartingAreaUnblocked PieceAppearedNoError PieceLostNoError MQTTNoError COMNoError ValidMeasure RampNoError CalibNoWarning ReplayNoWarning RampNotFull NoRampFull");
    DEBUG(">>>>>>>>>>>>>>>>>>>>>>>>>>> LASER FRONT BLOCKED <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_FRONT_BLOCKED);
    EXPECT_STATE("Start_PT1 Fast PieceFlat StartingAreaBlocked PieceAppearedNoError PieceLostNoError MQTTNoError COMNoError ValidMeasure RampNoError CalibNoWarning ReplayNoWarning RampNotFull NoRampFull");

    DEBUG(">>>>>>>>>>>>>>>>>>>>>>>>>>> LASER FRONT UNBLOCKED <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_FRONT_UNBLOCKED);
    EXPECT_STATE("StartADC_PT1 Fast PieceFlat StartingAreaBlocked PieceAppearedNoError PieceLostNoError MQTTNoError COMNoError ValidMeasure RampNoError CalibNoWarning ReplayNoWarning RampNotFull NoRampFull");
    WAIT(2000);
    EXPECT_STATE("ADC_PT1 Slow PieceFlat StartingAreaUnblocked PieceAppearedNoError PieceLostNoError MQTTNoError COMNoError ValidMeasure RampNoError CalibNoWarning ReplayNoWarning RampNotFull NoRampFull");
    DEBUG(">>>>>>>>>>>>>>>>>>>>>>>>>>> ADC BEGIN <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::ADC_TOP_AREA_BLOCKED);
    remote_control->send_event((int8_t) Topic::ADC, (int) ADC_Enum::ADC_NEW_PIECE);
    WAIT(1123);
    DEBUG(">>>>>>>>>>>>>>>>>>>>>>>>>>> ADC END <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
    remote_control->send_event((int8_t) Topic::ADC, (int) ADC_Enum::ADC_WF_DETECT);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::ADC_TOP_AREA_UNBLOCKED);
    EXPECT_STATE("ADCGate_PT1 Fast PieceFlat StartingAreaUnblocked PieceAppearedNoError PieceLostNoError MQTTNoError COMNoError ValidMeasure RampNoError CalibNoWarning ReplayNoWarning RampNotFull NoRampFull");

    WAIT(1500);
    DEBUG(">>>>>>>>>>>>>>>>>>>>>>>>>>> LASER SORTING BLOCKED <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_BLOCKED);
    EXPECT_STATE("GateEnd_PT1 Fast PieceTall StartingAreaUnblocked PieceAppearedNoError PieceLostNoError MQTTNoError COMNoError ValidMeasure RampNoError CalibNoWarning ReplayNoWarning RampNotFull NoRampFull");
    WAIT(400);
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_UNBLOCKED);
    DEBUG(">>>>>>>>>>>>>>>>>>>>>>>>>>> LASER SORTING UNBLOCKED <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
    WAIT(2000);
    DEBUG(">>>>>>>>>>>>>>>>>>>>>>>>>>> LASER BACK BLOCKED <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_BACK_BLOCKED);   
    EXPECT_STATE("PendingTransferRequest_PT1 Stop PieceTall StartingAreaUnblocked PieceAppearedNoError PieceLostNoError MQTTNoError COMNoError ValidMeasure RampNoError CalibNoWarning ReplayNoWarning RampNotFull NoRampFull");

    //wait till fbm2 ready
    WAIT(2000);
    DEBUG(">>>>>>>>>>>>>>>>>>>>>>>>>>> FBM 2 READY <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
    remote_control->send_event((int8_t) Topic::COM, (int) COM_Enum::FBM_2_READY);
    EXPECT_STATE("Transfer_PT1 Fast PieceTall StartingAreaUnblocked PieceAppearedNoError PieceLostNoError MQTTNoError COMNoError ValidMeasure RampNoError CalibNoWarning ReplayNoWarning RampNotFull NoRampFull");
    WAIT(1000);
    DEBUG(">>>>>>>>>>>>>>>>>>>>>>>>>>> TRANSFER DONE <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
    remote_control->send_event((int8_t) Topic::COM, (int) COM_Enum::TRANSFER_DONE);
    EXPECT_STATE("PieceControllerFBM1 Idle PieceTall StartingAreaUnblocked PieceAppearedNoError PieceLostNoError MQTTNoError COMNoError ValidMeasure RampNoError CalibNoWarning ReplayNoWarning RampNotFull NoRampFull"); //TODO if one state exits, that state should be deleted
}


TEST_F(SortingOrderSetup, SortingOrderPositiveTest) {
    EXPECT_STATE("PieceFlat");
    data->is_ramp_full = false;
    remote_control->send_event((int8_t) Topic::CHECK_PIECE, (int) PieceEnum::FLAT);
    EXPECT_STATE("PieceTall");
    data->is_ramp_full = false;

    remote_control->send_event((int8_t) Topic::CHECK_PIECE, (int) PieceEnum::TALL);
    EXPECT_STATE("PieceTallWithMetal");
    data->is_ramp_full = false;
    remote_control->send_event((int8_t) Topic::CHECK_PIECE, (int) PieceEnum::TALL_WITH_METAL);
    EXPECT_STATE("PieceFlat");
}

TEST_F(SortingOrderSetup, SortingOrderNegativeTest) {
    //test PieceFlat
    EXPECT_STATE("PieceFlat");
    data->is_ramp_full = false;
    remote_control->send_event((int8_t) Topic::CHECK_PIECE, (int) PieceEnum::UNKNOWN);
    EXPECT_STATE("PieceFlat");

    //change state to tall
    remote_control->send_event((int8_t) Topic::CHECK_PIECE, (int) PieceEnum::FLAT);
    EXPECT_STATE("PieceTall");
    //test PieceTall
    remote_control->send_event((int8_t) Topic::CHECK_PIECE, (int) PieceEnum::UNKNOWN);
    EXPECT_STATE("PieceTall");

    //change state to tall metal
    remote_control->send_event((int8_t) Topic::CHECK_PIECE, (int) PieceEnum::TALL);
    EXPECT_STATE("PieceTallWithMetal");
    //test PieceWithMetal
    remote_control->send_event((int8_t) Topic::CHECK_PIECE, (int) PieceEnum::UNKNOWN);
    EXPECT_STATE("PieceTallWithMetal");

    //change state to flat
    remote_control->send_event((int8_t) Topic::CHECK_PIECE, (int) PieceEnum::TALL_WITH_METAL);
    EXPECT_STATE("PieceFlat");
    //test PieceWithMetal
    remote_control->send_event((int8_t) Topic::CHECK_PIECE, (int) PieceEnum::UNKNOWN);
    EXPECT_STATE("PieceFlat");
}


/**
 * @brief enter service mode
 */
//  TEST_F(RealImplementationSetup, ServiceModeFullTest) {
//      //go to service mode
//      remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_START_PRESSED);
//      WAIT(2100);
//      remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_START_RELEASED);
//      EXPECT_STATE("IdleSM");

//      //put a piece to calibrate the pieces
//      remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_FRONT_BLOCKED);
//      remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_FRONT_UNBLOCKED);
//      EXPECT_STATE("IdleSMSR IdleSTR");

//      // //piece goes to sorting gate
//      remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_BLOCKED);
//      remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_UNBLOCKED);
//      remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_RAMP_BLOCKED);
//      remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_RAMP_UNBLOCKED);
//      EXPECT_STATE("IdleSMSR IdleSTR");

//      // //assume calibration is done
//      remote_control->send_event((int8_t) Topic::ADC, (int) ADC_Enum::ADC_CALIBRATION_DONE);
//      //last calibrated piece goes to ramp
//      remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_RAMP_BLOCKED);
//      remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_RAMP_UNBLOCKED);
//      EXPECT_STATE("ReadyForCDF");

//      //calibrate fast mode
//      remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_FRONT_BLOCKED);
//      remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_FRONT_UNBLOCKED);
//      EXPECT_STATE("StartCDF IdleLPT");
//      WAIT(2000);
//      remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::ADC_TOP_AREA_BLOCKED);
//      WAIT(1000);
//      remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::ADC_TOP_AREA_UNBLOCKED);
//      WAIT(1000);
//      //pieces are let through the gate
//      remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_BLOCKED);
//      WAIT(1000);
//      remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_UNBLOCKED);
//      WAIT(3000);
//      // //piece is now at the end of the machine
//      remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_BACK_BLOCKED);
//      EXPECT_STATE("EndToGateCRF PusherIdleCRF");

//      //the piece goes back
//      remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_BACK_UNBLOCKED);
//      WAIT(3000);
//      remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_BLOCKED);
//      WAIT(1000);
//      remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_UNBLOCKED);
//      WAIT(1000);
//      remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::ADC_TOP_AREA_BLOCKED);
//      remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_BLOCKED);
//      WAIT(250);
//      remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_UNBLOCKED);
//      WAIT(750);
//      remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_RAMP_BLOCKED);
//      remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_RAMP_UNBLOCKED);
//      EXPECT_STATE("ReadyForCDS");

//      //calibrate slow mode
//      remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_FRONT_BLOCKED);
//      remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_FRONT_UNBLOCKED);
//      EXPECT_STATE("StartCDS IdleLPT");
//      WAIT(2000);
//      remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::ADC_TOP_AREA_BLOCKED);
//      WAIT(1000);
//      remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::ADC_TOP_AREA_UNBLOCKED);
//      WAIT(1000);
//      //pieces are let through the gate
//      remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_BLOCKED);
//      WAIT(1000);
//      remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_UNBLOCKED);
//      WAIT(3000);
//      // //piece is now at the end of the machine
//      remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_BACK_BLOCKED);
//      EXPECT_STATE("EndToGateCRS PusherIdleCRS");

//      //the piece goes back
//      remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_BACK_UNBLOCKED);
//      WAIT(3000);
//      remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_BLOCKED);
//      WAIT(1000);
//      remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_UNBLOCKED);
//      WAIT(1000);
//      remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::ADC_TOP_AREA_BLOCKED);
//      remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_BLOCKED);
//      WAIT(250);
//      remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_UNBLOCKED);
//      WAIT(750);
//      remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_RAMP_BLOCKED);
//      remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_RAMP_UNBLOCKED);
//      EXPECT_STATE("CalibrationFinished");
//  }

//  /**
//   * @brief enter adc calibration mode, then estop
//   */
// TEST_F(RealImplementationSetup, AdcCalibrationThenEstop) {
//     //go to service mode
//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_START_PRESSED);
//     WAIT(2100);
//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_START_RELEASED);
//     EXPECT_STATE("IdleSM");

//     //put a piece to calibrate the pieces
//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_FRONT_BLOCKED);
//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_FRONT_UNBLOCKED);
//     EXPECT_STATE("IdleSMSR IdleSTR");

//     // //piece goes to sorting gate
//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_BLOCKED);
//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_SORTING_GATE_UNBLOCKED);
//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_RAMP_BLOCKED);
//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_RAMP_UNBLOCKED);
//     EXPECT_STATE("IdleSMSR IdleSTR");

//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_ESTOP_PRESSED);
//     EXPECT_STATE("EStopViaLocal");
//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_ESTOP_RELEASED);
//     EXPECT_STATE("EStopReleased");
//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_RESET_PRESSED);
//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_RESET_RELEASED);
//     EXPECT_STATE("WaitingForComReset");
//     remote_control->send_event((int8_t) Topic::COM, (int) COM_Enum::BUTTON_RESET_PRESSED);
//     EXPECT_STATE("IdleIM");
// }

// /**
//  * @brief enter operating mode, by pressing start button shortly
//  */
// TEST_F(RealImplementationSetup, ShortTimerTest) {
//     //go to service mode
//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_START_PRESSED);
//     EXPECT_STATE("WaitingIM");
//     WAIT(500);
//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_START_RELEASED);
//     //EXPECT_STATE("PseudoState");
// }

// /**
//  * @brief enter adc calibration mode, by long pressing start button
//  */
// TEST_F(RealImplementationSetup, LongTimerTest) {
//     //go to service mode
//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_START_PRESSED);
//     EXPECT_STATE("WaitingIM");
//     WAIT(5000);
//     EXPECT_STATE("TimerReceivedIM");
//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int) InterruptEnum::BUTTON_START_RELEASED);
//     EXPECT_STATE("IdleSM");
// }

/**
 * @brief Test workpiece state tracking with motor control events
 * Tests that workpiece IDs in motor control events are properly tracked
 */
TEST_F(MotorControlSetup, MotorControlWorkpieceTrackingTest) {
    // Start in Idle state
    EXPECT_STATE("Idle");

    // Test MOTOR_FAST with workpiece ID 1 - should transition to Fast
    remote_control->send_event((int8_t) Topic::MOTOR_FAST, 1); // ID 1
    WAIT(10);
    EXPECT_STATE("Fast");

    //     // 2. System slows down -> SLOW
    //     remote_control->send_event((int8_t) Topic::MOTOR_SLOW, 100);
    //     WAIT(10);
    //     EXPECT_STATE("Slow");
    //     EXPECT_EQ(data->workpieceList.getState(100), MotorPieceState::SLOW);

        // Test MOTOR_SLOW with workpiece ID 2 - should transition to Slow and update all to SLOW
    remote_control->send_event((int8_t) Topic::MOTOR_SLOW, 2); // ID 2
    WAIT(10);
    EXPECT_STATE("Slow");

    //     // 4. System resumes -> FAST
    //     remote_control->send_event((int8_t) Topic::MOTOR_FAST, 100);
    //     WAIT(10);
    //     EXPECT_STATE("Fast");
    //     EXPECT_EQ(data->workpieceList.getState(100), MotorPieceState::FAST);

        // Test MOTOR_STOP_FSM with workpiece ID 3 - should transition to Stop and update ALL to STOPPED
    remote_control->send_event((int8_t) Topic::MOTOR_STOP_FSM, 3); // ID 3
    WAIT(10);
    EXPECT_STATE("Stop");

    // Verify all three workpieces are now in STOPPED state
    EXPECT_TRUE(data->workpieceList.contains(1));
    EXPECT_TRUE(data->workpieceList.contains(2));
    EXPECT_TRUE(data->workpieceList.contains(3));
    EXPECT_EQ(data->workpieceList.getState(1), MotorPieceState::STOPPED);
    EXPECT_EQ(data->workpieceList.getState(2), MotorPieceState::STOPPED);
    EXPECT_EQ(data->workpieceList.getState(3), MotorPieceState::STOPPED);
    EXPECT_EQ(data->workpieceList.size(), 3);

    // Test DELETE_W_MOTOR with specific ID - should stay in Stop (workpieces remain)
    remote_control->send_event((int8_t) Topic::DELETE_W_MOTOR, 2); // Remove ID 2
    WAIT(10);
    EXPECT_STATE("Stop"); // Should remain in Stop since workpieces still exist

    // Verify workpiece 2 was removed, others remain in STOPPED state
    EXPECT_TRUE(data->workpieceList.contains(1));
    EXPECT_FALSE(data->workpieceList.contains(2)); // Removed
    EXPECT_TRUE(data->workpieceList.contains(3));
    EXPECT_EQ(data->workpieceList.getState(1), MotorPieceState::STOPPED);
    EXPECT_EQ(data->workpieceList.getState(3), MotorPieceState::STOPPED);
    EXPECT_EQ(data->workpieceList.size(), 2);

    // Test transition back to FAST with new workpiece - should go to Fast
    remote_control->send_event((int8_t) Topic::MOTOR_FAST, 4); // ID 4
    WAIT(10);
    EXPECT_STATE("Fast");

    // Verify all workpieces (including new one) are now in FAST state
    EXPECT_TRUE(data->workpieceList.contains(1));
    EXPECT_TRUE(data->workpieceList.contains(3));
    EXPECT_TRUE(data->workpieceList.contains(4));
    EXPECT_EQ(data->workpieceList.getState(1), MotorPieceState::FAST);
    EXPECT_EQ(data->workpieceList.getState(3), MotorPieceState::FAST);
    EXPECT_EQ(data->workpieceList.getState(4), MotorPieceState::FAST);
    EXPECT_EQ(data->workpieceList.size(), 3);

    // Test removing all workpieces to trigger transition to Idle
    remote_control->send_event((int8_t) Topic::DELETE_W_MOTOR, 1);
    WAIT(10);
    EXPECT_STATE("Fast"); // Still has workpieces

    remote_control->send_event((int8_t) Topic::DELETE_W_MOTOR, 3);
    WAIT(10);
    EXPECT_STATE("Fast"); // Still has workpieces

    remote_control->send_event((int8_t) Topic::DELETE_W_MOTOR, 4); // Remove last workpiece
    WAIT(10);
    EXPECT_STATE("Idle"); // Should transition to Idle when no workpieces remain

    // Verify list is empty
    EXPECT_TRUE(data->workpieceList.isEmpty());
    EXPECT_FALSE(data->workpieces);
}

/**
 * @brief Test complete workpiece lifecycle with motor control
 */
TEST_F(MotorControlSetup, WorkpieceLifecycleTest) {
    // Start in Idle state
    EXPECT_STATE("Idle");

    // Simulate complete workpiece lifecycle:
    // 1. Workpiece enters system -> FAST
    remote_control->send_event((int8_t) Topic::MOTOR_FAST, 100);
    WAIT(10);
    EXPECT_STATE("Fast");
    EXPECT_TRUE(data->workpieceList.contains(100));
    EXPECT_EQ(data->workpieceList.getState(100), MotorPieceState::FAST);

    // 2. System slows down -> SLOW
    remote_control->send_event((int8_t) Topic::MOTOR_SLOW, 100);
    WAIT(10);
    EXPECT_STATE("Slow");
    EXPECT_EQ(data->workpieceList.getState(100), MotorPieceState::SLOW);

    // 3. System needs to stop -> STOPPED
    remote_control->send_event((int8_t) Topic::MOTOR_STOP_FSM, 100);
    WAIT(10);
    EXPECT_STATE("Stop");
    EXPECT_EQ(data->workpieceList.getState(100), MotorPieceState::STOPPED);

    // 4. System resumes -> FAST
    remote_control->send_event((int8_t) Topic::MOTOR_FAST, 100);
    WAIT(10);
    EXPECT_STATE("Fast");
    EXPECT_EQ(data->workpieceList.getState(100), MotorPieceState::FAST);

    // 5. Workpiece leaves system -> DELETE
    remote_control->send_event((int8_t) Topic::DELETE_W_MOTOR, 100);
    WAIT(10);
    EXPECT_STATE("Idle"); // Should return to Idle when no workpieces remain
    EXPECT_FALSE(data->workpieceList.contains(100));
    EXPECT_TRUE(data->workpieceList.isEmpty());
    EXPECT_FALSE(data->workpieces); // Should be false when list is empty
}

/**
 * @brief Test multiple workpieces with overlapping motor control events
 */
TEST_F(MotorControlSetup, MultipleWorkpiecesOverlappingTest) {
    // Start in Idle state
    EXPECT_STATE("Idle");

    // Add workpieces at different times
    remote_control->send_event((int8_t) Topic::MOTOR_FAST, 201);
    WAIT(10);
    EXPECT_STATE("Fast");

    remote_control->send_event((int8_t) Topic::MOTOR_FAST, 202);
    WAIT(10);
    EXPECT_STATE("Fast"); // Should remain in Fast

    remote_control->send_event((int8_t) Topic::MOTOR_SLOW, 203); // This should change ALL to SLOW
    WAIT(10);
    EXPECT_STATE("Slow");

    // Verify all workpieces are in SLOW state
    EXPECT_EQ(data->workpieceList.getState(201), MotorPieceState::SLOW);
    EXPECT_EQ(data->workpieceList.getState(202), MotorPieceState::SLOW);
    EXPECT_EQ(data->workpieceList.getState(203), MotorPieceState::SLOW);

    // Add more workpieces while in SLOW
    remote_control->send_event((int8_t) Topic::MOTOR_SLOW, 204);
    WAIT(10);
    EXPECT_STATE("Slow"); // Should remain in Slow

    // All should still be SLOW
    EXPECT_EQ(data->workpieceList.getState(201), MotorPieceState::SLOW);
    EXPECT_EQ(data->workpieceList.getState(202), MotorPieceState::SLOW);
    EXPECT_EQ(data->workpieceList.getState(203), MotorPieceState::SLOW);
    EXPECT_EQ(data->workpieceList.getState(204), MotorPieceState::SLOW);

    // Remove some workpieces
    remote_control->send_event((int8_t) Topic::DELETE_W_MOTOR, 202);
    WAIT(10);
    EXPECT_STATE("Slow"); // Should remain in Slow (still has workpieces)

    remote_control->send_event((int8_t) Topic::DELETE_W_MOTOR, 204);
    WAIT(10);
    EXPECT_STATE("Slow"); // Should remain in Slow (still has workpieces)

    // Verify correct workpieces removed
    EXPECT_TRUE(data->workpieceList.contains(201));
    EXPECT_FALSE(data->workpieceList.contains(202));
    EXPECT_TRUE(data->workpieceList.contains(203));
    EXPECT_FALSE(data->workpieceList.contains(204));
    EXPECT_EQ(data->workpieceList.size(), 2);

    // Change to STOPPED
    remote_control->send_event((int8_t) Topic::MOTOR_STOP_FSM, 205); // Add new and change all
    WAIT(10);
    EXPECT_STATE("Stop");

    // Verify all remaining workpieces are STOPPED
    EXPECT_EQ(data->workpieceList.getState(201), MotorPieceState::STOPPED);
    EXPECT_EQ(data->workpieceList.getState(203), MotorPieceState::STOPPED);
    EXPECT_EQ(data->workpieceList.getState(205), MotorPieceState::STOPPED);
    EXPECT_EQ(data->workpieceList.size(), 3);
}

/**
 * @brief Test edge cases in motor control workpiece management
 */
TEST_F(MotorControlSetup, MotorControlEdgeCasesTest) {
    EXPECT_STATE("Idle");

    // Test adding same ID multiple times (should not duplicate)
    remote_control->send_event((int8_t) Topic::MOTOR_FAST, 1);
    WAIT(10);

    // Try to add same ID again with different state
    EXPECT_STATE("Fast");
    remote_control->send_event((int8_t) Topic::MOTOR_SLOW, 1);
    WAIT(10);
    EXPECT_STATE("Slow");

    // Test deleting non-existent ID (should not crash)
    remote_control->send_event((int8_t) Topic::DELETE_W_MOTOR, 999); // Non-existent ID
    WAIT(10);
    EXPECT_STATE("Slow");


    // Test empty list behavior
    remote_control->send_event((int8_t) Topic::DELETE_W_MOTOR, 1);
    WAIT(10);
    EXPECT_STATE("Idle");
    // List should be empty
    EXPECT_TRUE(data->workpieceList.isEmpty());
    EXPECT_FALSE(data->workpieces);
    EXPECT_EQ(data->workpieceList.size(), 0);

    // Test state transitions with empty list
    remote_control->send_event((int8_t) Topic::MOTOR_FAST, 2);
    WAIT(10);
    EXPECT_STATE("Fast");
    // Should add new workpiece
    EXPECT_TRUE(data->workpieceList.contains(2));
    EXPECT_EQ(data->workpieceList.getState(2), MotorPieceState::FAST);
    EXPECT_TRUE(data->workpieces); // No longer empty
    EXPECT_EQ(data->workpieceList.size(), 1);
}

// TEST_F(PieceControllerSetup, PieceTrackingFBM1){
//     EXPECT_STATE("PieceTracking");
//     //1. Test multiple new pieces.
//     //new_piece should transition to PieceTracking
//     remote_control->send_event((int) Internal_Enum::NEW_PIECE, 1);
//     WAIT(10);
//     EXPECT_STATE("PieceTracking");
// }

TEST_F(PieceTrackingFBM1Setup, FlatPieceCorrectFBM1) {
   // Start state
     // Verify initial state
    std::cout << "Initial state: " << logic->show_state() << std::endl;
    EXPECT_STATE("PieceControllerFBM1");

    // DEBUG: Print available transitions
 
    // 1. Send NEW_PIECE event with verification
    std::cout << "Sending NEW_PIECE..." << std::endl;
    remote_control->send_event((int8_t) Topic::INTERNAL, (int) Internal_Enum::NEW_PIECE, 1);
    WAIT(10);

    for (auto& pair : *data->pieces_map) {
      Piece* piece = pair.second;  // pair.second is the value (Piece*)
      piece->piece_tracker.fast();               // Call fast() on the Piece*
    }

    EXPECT_STATE("Start_PT1");
    std::cout << "State after NEW_PIECE: " << logic->show_state() << std::endl;
    
    // Laser front unblocked
    
    remote_control->send_event( (int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_FRONT_UNBLOCKED, 1);
    WAIT(10);
    std::cout << "State after Start_PT1: " << logic->show_state() << std::endl;
    EXPECT_STATE("StartADC_PT1");
    
    // After 100ms
    WAIT(2200);
    std::cout << "State after StartADC_PT1: " << logic->show_state() << std::endl;

    EXPECT_STATE("ADC_PT1");
      for (auto& pair : *data->pieces_map) {
      Piece* piece = pair.second;  // pair.second is the value (Piece*)
      piece->piece_tracker.slow();               // Call slow() on the Piece*
    }
    
    // ADC detects new piece
    remote_control->send_event((int8_t) Topic::ADC, (int) ADC_Enum::ADC_NEW_PIECE, 1);
      
    for (auto& pair : *data->pieces_map) {
      Piece* piece = pair.second;  // pair.second is the value (Piece*)
      piece->piece_tracker.fast();               // Call fast() on the Piece*
    }

    WAIT(10);
    EXPECT_STATE("Measuring_PT1");
    
    // ADC detects flat piece
    remote_control->send_event((int8_t) Topic::ADC, (int) ADC_Enum::ADC_WF_DETECT, 1);
    EXPECT_STATE("ADCGate_PT1");
    
    // After 100ms
    WAIT(1000);
    // Should stay in ADCGate_PT1 as we need to check gate status
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int)InterruptEnum::LASER_SORTING_GATE_BLOCKED, 1);
    WAIT(10);
    EXPECT_STATE("Gate_PT1");
    
    // Check piece type (flat)
    // This should let_through
    remote_control->send_event((int8_t)Topic::CHECK_PIECE, (int)PieceEnum::FLAT);
    remote_control->send_event((int8_t)Topic::INTERNAL, (int)Internal_Enum::LET_THROUGH, 1);
    WAIT(10);
    EXPECT_STATE("GateEnd_PT1");

    WAIT(2000);
    remote_control->send_event((int8_t)Topic::INTERRUPT, (int)InterruptEnum::LASER_BACK_BLOCKED, 1);
    for (auto& pair : *data->pieces_map) {
      Piece* piece = pair.second;  // pair.second is the value (Piece*)
      piece->piece_tracker.stop();               // Call stop() on the Piece*
    }
    WAIT(10);
    EXPECT_STATE("PendingTransferRequest_PT1");
}

TEST_F(PieceTrackingFBM1Setup, PieceMissingAfterADC) {
    
   // Start state
     // Verify initial state
    std::cout << "Initial state: " << logic->show_state() << std::endl;
    EXPECT_STATE("PieceControllerFBM1");

    // DEBUG: Print available transitions
 
    // 1. Send NEW_PIECE event with verification
    std::cout << "Sending NEW_PIECE..." << std::endl;
    remote_control->send_event((int8_t) Topic::INTERNAL, (int) Internal_Enum::NEW_PIECE, 1);
    WAIT(10);

    for (auto& pair : *data->pieces_map) {
      Piece* piece = pair.second;  // pair.second is the value (Piece*)
      piece->piece_tracker.fast();               // Call fast() on the Piece*
    }

    EXPECT_STATE("Start_PT1");
    std::cout << "State after NEW_PIECE: " << logic->show_state() << std::endl;
    
    // Laser front unblocked
    
    remote_control->send_event( (int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_FRONT_UNBLOCKED, 1);
    WAIT(10);
    std::cout << "State after Start_PT1: " << logic->show_state() << std::endl;
    EXPECT_STATE("StartADC_PT1");
    
    // After 100ms
    WAIT(2300);
    std::cout << "State after StartADC_PT1: " << logic->show_state() << std::endl;

    EXPECT_STATE("ADC_PT1");
      for (auto& pair : *data->pieces_map) {
      Piece* piece = pair.second;  // pair.second is the value (Piece*)
      piece->piece_tracker.slow();               // Call slow() on the Piece*
    }
    
    // ADC timeout occurs
    remote_control->send_event((int8_t)Topic::ADC, (int)ADC_Enum::ADC_TIMEOUT);
    WAIT(10);
    EXPECT_STATE("PieceControllerFBM1");
    
    // Verify error handling and state reset
    // Should transition to end state after handling
}

TEST_F(PieceTrackingFBM1Setup, MetalPieceDetection) {
   // Start state
     // Verify initial state
    std::cout << "Initial state: " << logic->show_state() << std::endl;
    EXPECT_STATE("PieceControllerFBM1");

    // DEBUG: Print available transitions
 
    // 1. Send NEW_PIECE event with verification
    std::cout << "Sending NEW_PIECE..." << std::endl;
    remote_control->send_event((int8_t) Topic::INTERNAL, (int) Internal_Enum::NEW_PIECE, 1);
    WAIT(10);

    for (auto& pair : *data->pieces_map) {
      Piece* piece = pair.second;  // pair.second is the value (Piece*)
      piece->piece_tracker.fast();               // Call fast() on the Piece*
    }

    EXPECT_STATE("Start_PT1");
    std::cout << "State after NEW_PIECE: " << logic->show_state() << std::endl;
    
    // Laser front unblocked
    
    remote_control->send_event( (int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_FRONT_UNBLOCKED, 1);
    WAIT(10);
    std::cout << "State after Start_PT1: " << logic->show_state() << std::endl;
    EXPECT_STATE("StartADC_PT1");
    
    // After 100ms
    WAIT(2200);
    std::cout << "State after StartADC_PT1: " << logic->show_state() << std::endl;

    EXPECT_STATE("ADC_PT1");
      for (auto& pair : *data->pieces_map) {
      Piece* piece = pair.second;  // pair.second is the value (Piece*)
      piece->piece_tracker.slow();               // Call slow() on the Piece*
    }
    
    // ADC detects new piece
    remote_control->send_event((int8_t) Topic::ADC, (int) ADC_Enum::ADC_NEW_PIECE, 1);
      
    for (auto& pair : *data->pieces_map) {
      Piece* piece = pair.second;  // pair.second is the value (Piece*)
      piece->piece_tracker.fast();               // Call fast() on the Piece*
    }

    WAIT(10);
    EXPECT_STATE("Measuring_PT1");
    
    // ADC detects flat piece
    remote_control->send_event((int8_t) Topic::ADC, (int) ADC_Enum::ADC_W_B_DETECT, 1);
    EXPECT_STATE("ADCGate_PT1");
    
    // After 100ms
    WAIT(1000);
    // Should stay in ADCGate_PT1 as we need to check gate status
    
    remote_control->send_event((int8_t) Topic::INTERRUPT, (int)InterruptEnum::METAL_DETECTED, 1);
    WAIT(10);
    EXPECT_STATE("IsMetal_PT1");
    
    // Continue with sorting...
}

// TEST_F(PieceTrackingFBM1Setup, TransferToFBM2Flow) {

//       // Start state
//      // Verify initial state
//     std::cout << "Initial state: " << logic->show_state() << std::endl;
//     EXPECT_STATE("PieceControllerFBM1");

//     // DEBUG: Print available transitions
 
//     // 1. Send NEW_PIECE event with verification
//     std::cout << "Sending NEW_PIECE..." << std::endl;
//     remote_control->send_event((int8_t) Topic::INTERNAL, (int) Internal_Enum::NEW_PIECE, 1);
//     WAIT(10);

//     for (auto& pair : *data->pieces_map) {
//       Piece* piece = pair.second;  // pair.second is the value (Piece*)
//       piece->piece_tracker.fast();               // Call fast() on the Piece*
//     }

//     EXPECT_STATE("Start_PT1");
//     std::cout << "State after NEW_PIECE: " << logic->show_state() << std::endl;
    
//     // Laser front unblocked
    
//     remote_control->send_event( (int8_t) Topic::INTERRUPT, (int) InterruptEnum::LASER_FRONT_UNBLOCKED, 1);
//     WAIT(10);
//     std::cout << "State after Start_PT1: " << logic->show_state() << std::endl;
//     EXPECT_STATE("StartADC_PT1");
    
//     // After 100ms
//     WAIT(2200);
//     std::cout << "State after StartADC_PT1: " << logic->show_state() << std::endl;

//     EXPECT_STATE("ADC_PT1");
//       for (auto& pair : *data->pieces_map) {
//       Piece* piece = pair.second;  // pair.second is the value (Piece*)
//       piece->piece_tracker.slow();               // Call slow() on the Piece*
//     }
    
//     WAIT(10);
//     // ADC detects new piece
//     remote_control->send_event((int8_t) Topic::ADC, (int) ADC_Enum::ADC_NEW_PIECE, 1);
      
//     for (auto& pair : *data->pieces_map) {
//       Piece* piece = pair.second;  // pair.second is the value (Piece*)
//       piece->piece_tracker.fast();               // Call fast() on the Piece*
//     }

//     EXPECT_STATE("Measuring_PT1");
    
//     // ADC detects flat piece
//     remote_control->send_event((int8_t) Topic::ADC, (int) ADC_Enum::ADC_WF_DETECT, 1);
//     EXPECT_STATE("ADCGate_PT1");
    
//     // After 100ms
//     WAIT(1000);
//     // Should stay in ADCGate_PT1 as we need to check gate status
    
//     // Sorting gate blocked (expected)
//     remote_control->send_event((int8_t) Topic::INTERRUPT, (int)InterruptEnum::LASER_SORTING_GATE_BLOCKED, 1);
//     EXPECT_STATE("Gate_PT1");

//     // Let through to FBM2
//     remote_control->send_event((int8_t) Topic::INTERNAL, (int)Internal_Enum::LET_THROUGH, 1);
//     EXPECT_STATE("GateEnd_PT1");
    
//     // After 100ms
//     WAIT(100);
//     // Should check position
    
//     // Laser back blocked (expected)
//     remote_control->send_event((int)InterruptEnum::LASER_BACK_BLOCKED, 1);
//     EXPECT_STATE("PendingTransferRequest_PT1");
    
//     // FBM2 ready
//     remote_control->send_event((int)COM_Enum::FBM_2_READY, 1);
//     EXPECT_STATE("Transfer_PT1");
    
//     // Transfer done
//     remote_control->send_event((int)COM_Enum::TRANSFER_DONE, 1);
//     // Should reach end state
// }

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
