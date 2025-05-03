#include <gtest/gtest.h>
#include "mobilerobotsim/point_robot.h"

namespace mobilerobotsim {
namespace testing {

// Basic test for point robot creation
TEST(PointRobotTest, Creation) {
  // Create a robot at the origin
  auto robot = std::make_unique<PointRobot>();
  double x, y;
  robot->GetPosition(x, y);
  EXPECT_DOUBLE_EQ(x, 0.0);
  EXPECT_DOUBLE_EQ(y, 0.0);
  EXPECT_DOUBLE_EQ(robot->GetOrientation(), 0.0);
  
  // Create a robot at a specific position
  auto robot2 = std::make_unique<PointRobot>(2.0, 3.0);
  robot2->GetPosition(x, y);
  EXPECT_DOUBLE_EQ(x, 2.0);
  EXPECT_DOUBLE_EQ(y, 3.0);
  
  // Create a robot with full specification
  auto robot3 = std::make_unique<PointRobot>(4.0, 5.0, 1.0, 0.5, 0.5);
  robot3->GetPosition(x, y);
  EXPECT_DOUBLE_EQ(x, 4.0);
  EXPECT_DOUBLE_EQ(y, 5.0);
  EXPECT_DOUBLE_EQ(robot3->GetOrientation(), 1.0);
  double vx, vy;
  robot3->GetVelocity(vx, vy);
  EXPECT_DOUBLE_EQ(vx, 0.5);
  EXPECT_DOUBLE_EQ(vy, 0.5);
}

// Test robot state management
TEST(PointRobotTest, StateManagement) {
  auto robot = std::make_unique<PointRobot>(1.0, 2.0);
  
  // Get state
  auto state = robot->GetState();
  EXPECT_TRUE(state != nullptr);
  
  // Create a new robot and load the state
  auto newRobot = std::make_unique<PointRobot>();
  EXPECT_TRUE(newRobot->LoadState(*state));
  
  // Check that the state was properly loaded
  double x, y;
  newRobot->GetPosition(x, y);
  EXPECT_DOUBLE_EQ(x, 1.0);
  EXPECT_DOUBLE_EQ(y, 2.0);
}

// Test robot movement
TEST(PointRobotTest, Movement) {
  auto robot = std::make_unique<PointRobot>(0.0, 0.0);
  
  // Set target velocity
  robot->SetTargetVelocity(1.0, 0.0);
  
  // Update for 1 second
  robot->UpdateState(1.0);
  
  // Check new position
  double x, y;
  robot->GetPosition(x, y);
  EXPECT_NEAR(x, 1.0, 0.001);
  EXPECT_NEAR(y, 0.0, 0.001);
  
  // Check orientation (should be facing along the velocity vector)
  EXPECT_NEAR(robot->GetOrientation(), 0.0, 0.001);
}

} // namespace testing
} // namespace mobilerobotsim
