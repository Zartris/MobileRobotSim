#pragma once

#include <memory>

namespace mobilerobotsim {

// Forward declarations
class SystemState;
class MobileRobotBase;
class EnvironmentElement;

/**
 * @brief Observer interface for simulation events.
 * 
 * The SimulationObserver acts as an interface for components that need to be
 * notified about various events occurring during simulation, such as
 * time steps, collisions, and special events like robots reaching merge points.
 */
class SimulationObserver {
 public:
  /**
   * @brief Virtual destructor for proper cleanup of derived classes.
   */
  virtual ~SimulationObserver() = default;

  /**
   * @brief Called when a simulation step is completed.
   * 
   * This method is invoked by the SimulationEngine after each simulation step
   * is completed, allowing observers to process or visualize the updated state.
   * 
   * @param state Reference to the current state of the simulation
   */
  virtual void onStep(const SystemState& state) = 0;

  /**
   * @brief Called when a collision is detected.
   * 
   * This method is invoked when a collision is detected between a robot and
   * another object (which may be another robot or an environment element).
   * 
   * @param robot Pointer to the robot involved in the collision
   * @param object Pointer to the object involved in the collision
   */
  virtual void onCollision(const MobileRobotBase* robot, 
                          const void* object) = 0;

  /**
   * @brief Called when a robot reaches a merge point.
   * 
   * This method is invoked when a robot reaches a designated merge point
   * in the environment, allowing observers to track merging behavior.
   * 
   * @param robot Pointer to the robot that reached the merge point
   * @param mergePoint Pointer to the merge point that was reached
   */
  virtual void onMergePoint(const MobileRobotBase* robot, 
                           const EnvironmentElement* mergePoint) = 0;
};

} // namespace mobilerobotsim
