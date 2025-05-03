#include <gtest/gtest.h>
#include "mobilerobotsim/system_state.h"
#include "mobilerobotsim/robot_state.h"
#include "mobilerobotsim/environment.h"

namespace mobilerobotsim {
namespace testing {

// Simple test RobotState implementation for testing
class TestRobotState : public RobotState {
 public:
  TestRobotState(int id) : id_(id) {}
  ~TestRobotState() override = default;
  
  std::string GetTypeId() const override { return "TestRobotState"; }
  std::unique_ptr<RobotState> Clone() const override {
    return std::make_unique<TestRobotState>(id_);
  }
  std::string Serialize() const override { return "{}"; }
  bool Deserialize(const std::string& serialized) override { return true; }
  
  int GetId() const { return id_; }
  
 private:
  int id_;
};

// Basic test for SystemState creation
TEST(SystemStateTest, Creation) {
  SystemState state;
  EXPECT_DOUBLE_EQ(state.GetTime(), 0.0);
  EXPECT_EQ(state.GetRobotStateCount(), 0);
  EXPECT_EQ(state.GetEnvironmentState(), nullptr);
  
  SystemState state2(5.0);
  EXPECT_DOUBLE_EQ(state2.GetTime(), 5.0);
}

// Test adding robot states
TEST(SystemStateTest, AddRobotState) {
  SystemState state;
  
  // Add a robot state
  state.AddRobotState(std::make_unique<TestRobotState>(1));
  EXPECT_EQ(state.GetRobotStateCount(), 1);
  EXPECT_NE(state.GetRobotState(0), nullptr);
  
  // Add another robot state
  state.AddRobotState(std::make_unique<TestRobotState>(2));
  EXPECT_EQ(state.GetRobotStateCount(), 2);
  
  // Try to get a robot state that doesn't exist
  EXPECT_EQ(state.GetRobotState(2), nullptr);
}

// Test setting the environment state
TEST(SystemStateTest, SetEnvironmentState) {
  SystemState state;
  
  // Initially, there is no environment state
  EXPECT_EQ(state.GetEnvironmentState(), nullptr);
  
  // Set the environment state
  state.SetEnvironmentState(std::make_unique<EnvironmentState>());
  EXPECT_NE(state.GetEnvironmentState(), nullptr);
}

// Test copy constructor and assignment operator
TEST(SystemStateTest, CopyAndMove) {
  SystemState state1(10.0);
  state1.AddRobotState(std::make_unique<TestRobotState>(1));
  
  // Test copy constructor
  SystemState state2(state1);
  EXPECT_DOUBLE_EQ(state2.GetTime(), 10.0);
  EXPECT_EQ(state2.GetRobotStateCount(), 1);
  
  // Test assignment operator
  SystemState state3;
  state3 = state1;
  EXPECT_DOUBLE_EQ(state3.GetTime(), 10.0);
  EXPECT_EQ(state3.GetRobotStateCount(), 1);
  
  // Test move constructor
  SystemState state4(std::move(state2));
  EXPECT_DOUBLE_EQ(state4.GetTime(), 10.0);
  EXPECT_EQ(state4.GetRobotStateCount(), 1);
  
  // state2 should now be in a valid but unspecified state after move
  
  // Test move assignment
  SystemState state5;
  state5 = std::move(state3);
  EXPECT_DOUBLE_EQ(state5.GetTime(), 10.0);
  EXPECT_EQ(state5.GetRobotStateCount(), 1);
  
  // state3 should now be in a valid but unspecified state after move
}

} // namespace testing
} // namespace mobilerobotsim
