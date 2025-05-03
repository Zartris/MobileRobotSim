#include <gtest/gtest.h>
#include "mobilerobotsim/simulation_engine.h"
#include "mobilerobotsim/point_robot.h"

namespace mobilerobotsim {
namespace testing {

// Basic test to check if SimulationEngine can be created
TEST(SimulationEngineTest, Creation) {
  auto engine = std::make_unique<SimulationEngine>();
  EXPECT_TRUE(engine != nullptr);
  EXPECT_EQ(engine->GetTime(), 0.0);
  EXPECT_EQ(engine->GetRobotCount(), 0);
}

// Test adding a robot to the simulation
TEST(SimulationEngineTest, AddRobot) {
  auto engine = std::make_unique<SimulationEngine>();
  engine->AddRobot(std::make_unique<PointRobot>(0.0, 0.0));
  EXPECT_EQ(engine->GetRobotCount(), 1);
}

// Test stepping the simulation
TEST(SimulationEngineTest, Step) {
  auto engine = std::make_unique<SimulationEngine>();
  double dt = 0.1;
  engine->Step(dt);
  EXPECT_EQ(engine->GetTime(), dt);
}

// Test state saving and loading
TEST(SimulationEngineTest, StateManagement) {
  auto engine = std::make_unique<SimulationEngine>();
  engine->AddRobot(std::make_unique<PointRobot>(1.0, 2.0));
  
  auto state = engine->GetState();
  EXPECT_TRUE(state != nullptr);
  EXPECT_EQ(state->GetTime(), 0.0);
  EXPECT_EQ(state->GetRobotStateCount(), 1);
}

} // namespace testing
} // namespace mobilerobotsim
