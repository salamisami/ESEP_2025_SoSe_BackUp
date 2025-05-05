#include <gtest/gtest.h>
#include "FBM.h"
#include "memory_utils.h" // Your make_unique implementation

class StateMachineTest : public ::testing::Test {
protected:
    void SetUp() override {
        fbm = make_unique<FBM>();
    }

    std::unique_ptr<FBM> fbm;
};

TEST_F(StateMachineTest, InitialStateIsRuheModus) {
    EXPECT_TRUE(fbm->isInRuheModus());
    // EXPECT_TRUE Blinken Grün 0.5Hz
}
TEST_F(StateMachineTest, RuheToServiceTransition) {
    // Initial state
    EXPECT_TRUE(fbm->isInRuheModus());
    fbm->buttonStartUp(true, false);
    EXPECT_TRUE(fbm->isInServiceModus());
    // EXPECT_TRUE Blinken Grün 0.5Hz
}

TEST_F(StateMachineTest, ServiceToRuheTransition) {
    // Set initial state to ServiceModus
    fbm->buttonStartUp(true, false); // From Ruhe to Service
    EXPECT_TRUE(fbm->isInServiceModus());
    
    // Trigger transition back to Ruhe
    fbm->buttonStop();
    
    // Verify state
    EXPECT_TRUE(fbm->isInRuheModus());
}

TEST_F(StateMachineTest, RuheToBetriebsTransition) {
    // Initial state
    EXPECT_TRUE(fbm->isInRuheModus());
    
    // Trigger transition (long press, no errors)
    fbm->buttonStartUp(false, false);
    
    // Verify new state
    EXPECT_TRUE(fbm->isInBetriebsModus());
    // Add verification for solid green light
}

TEST_F(StateMachineTest, BetriebsToRuheTransition) {
    // Set initial state to BetriebsModus
    fbm->buttonStartUp(false, false);
    EXPECT_TRUE(fbm->isInBetriebsModus());
    
    // Trigger transition back to Ruhe
    fbm->buttonStop(); // Short press or error
    
    // Verify state
    EXPECT_TRUE(fbm->isInRuheModus());
}

TEST_F(StateMachineTest, Flow) {
    // 1. Initial state - RuheModus
    EXPECT_TRUE(fbm->isInRuheModus());
    
    // 2. Ruhe -> Service
    fbm->buttonStartUp(true, false);
    EXPECT_TRUE(fbm->isInServiceModus());
    
    // 3. Service -> Ruhe
    fbm->buttonStop();
    EXPECT_TRUE(fbm->isInRuheModus());
    
    // 4. Ruhe -> Betriebs (long press, no errors)
    fbm->buttonStartUp(false, false);
    EXPECT_TRUE(fbm->isInBetriebsModus());
    
    // 5. Betriebs -> Ruhe (short press or error)
    fbm->buttonStop();
    EXPECT_TRUE(fbm->isInRuheModus());
}
