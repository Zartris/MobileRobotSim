#include <gtest/gtest.h>
#include "mobilerobotsim/environment.h"

namespace mobilerobotsim {
namespace testing {

// Basic test for environment creation
TEST(EnvironmentTest, Creation) {
  auto env = std::make_unique<Environment>();
  EXPECT_TRUE(env != nullptr);
  
  // Get state should return a valid state
  auto state = env->GetState();
  EXPECT_TRUE(state != nullptr);
  EXPECT_EQ(state->GetElementStateCount(), 0);
}

// Test environment state handling
TEST(EnvironmentTest, StateManagement) {
  EnvironmentState state;
  
  // Add some element states
  state.AddElementState("TestElement1", "State1");
  state.AddElementState("TestElement2", "State2");
  
  EXPECT_EQ(state.GetElementStateCount(), 2);
  
  // Retrieve and check element states
  std::string typeId, elementState;
  EXPECT_TRUE(state.GetElementState(0, typeId, elementState));
  EXPECT_EQ(typeId, "TestElement1");
  EXPECT_EQ(elementState, "State1");
  
  EXPECT_TRUE(state.GetElementState(1, typeId, elementState));
  EXPECT_EQ(typeId, "TestElement2");
  EXPECT_EQ(elementState, "State2");
  
  // Out of bounds check
  EXPECT_FALSE(state.GetElementState(2, typeId, elementState));
}

// Test serialization (basic functionality)
TEST(EnvironmentTest, Serialization) {
  EnvironmentState state;
  state.AddElementState("TestElement", "TestState");
  
  std::string serialized = state.Serialize();
  EXPECT_FALSE(serialized.empty());
  
  EnvironmentState newState;
  EXPECT_TRUE(newState.Deserialize(serialized));
}

} // namespace testing
} // namespace mobilerobotsim
