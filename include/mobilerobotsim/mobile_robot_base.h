#pragma once

#include <memory>
#include <Eigen/Dense>

namespace mobilerobotsim {

// Forward declarations
class RobotState;

/**
 * @brief Abstract base class for mobile robots.
 * 
 * MobileRobotBase defines the common interface for all robot types in the simulation.
 * It provides methods for updating the robot's state, accessing the robot's state,
 * and loading a robot's state from a saved state object.
 */
class MobileRobotBase {
 public:
  /**
   * @brief Virtual destructor for proper cleanup of derived classes.
   */
  virtual ~MobileRobotBase() = default;

  /**
   * @brief Updates the robot's state based on the current time step.
   * 
   * This method is called by the simulation engine during each time step to
   * update the robot's internal state (position, orientation, velocity, etc.)
   * based on its control algorithms and the time step size.
   * 
   * @param dt Time step size in seconds
   */
  virtual void UpdateState(double dt) = 0;

  /**
   * @brief Returns the current state of the robot.
   * 
   * This method returns a representation of the robot's current state, including
   * position, orientation, velocity, and any robot-specific state variables.
   * The returned state object can be used for visualization, serialization,
   * or state saving/loading.
   * 
   * @return A unique pointer to a RobotState object representing the current state
   */
  virtual std::unique_ptr<RobotState> GetState() const = 0;

  /**
   * @brief Loads a previously saved state.
   * 
   * This method reconstructs the robot's internal state from a previously saved
   * state object. This allows for state loading, time travel debugging, and
   * scenario replays.
   * 
   * @param state The state to load
   * @return True if the state was successfully loaded, false otherwise
   */
  virtual bool LoadState(const RobotState& state) = 0;

 protected:
  /**
   * @brief Protected constructor to prevent direct instantiation.
   * 
   * MobileRobotBase is an abstract class and should not be instantiated directly.
   * Derived classes should call this constructor from their own constructors.
   */
  MobileRobotBase() = default;
};

} // namespace mobilerobotsim
