#pragma once

#include <memory>
#include <string>

#include "mobile_robot_base.h"

namespace mobilerobotsim {

// Forward declarations
class PointRobotState;

/**
 * @brief Implementation of a point robot.
 *
 * PointRobot represents a simple holonomic robot that is modeled as a point
 * with position, orientation, and velocity. It provides a concrete implementation
 * of the MobileRobotBase interface.
 */
class PointRobot : public MobileRobotBase {
 public:
  /**
   * @brief Default constructor.
   *
   * Creates a point robot at the origin with zero orientation and velocity.
   */
  PointRobot();

  /**
   * @brief Constructor with initial position.
   *
   * Creates a point robot at the specified position with zero orientation and velocity.
   *
   * @param x Initial x-coordinate
   * @param y Initial y-coordinate
   */
  PointRobot(double x, double y);

  /**
   * @brief Constructor with initial position, orientation, and velocity.
   *
   * @param x Initial x-coordinate
   * @param y Initial y-coordinate
   * @param orientation Initial orientation in radians
   * @param vx Initial x velocity
   * @param vy Initial y velocity
   */
  PointRobot(double x, double y, double orientation, double vx, double vy);

  /**
   * @brief Destructor.
   */
  ~PointRobot() override;

  /**
   * @brief Updates the robot's state based on the current time step.
   *
   * @param dt Time step size in seconds
   */
  void updateState(double dt) override;

  /**
   * @brief Returns the current state of the robot.
   *
   * @return A unique pointer to a RobotState object
   */
  std::unique_ptr<RobotState> getState() const override;

  /**
   * @brief Loads a previously saved state.
   *
   * @param state The state to load
   * @return True if the state was successfully loaded, false otherwise
   */
  bool loadState(const RobotState& state) override;

  /**
   * @brief Sets the target velocity for the robot.
   *
   * @param vx Target x velocity
   * @param vy Target y velocity
   */
  void setTargetVelocity(double vx, double vy);

  /**
   * @brief Gets the current position of the robot.
   *
   * @param x Output parameter for x-coordinate
   * @param y Output parameter for y-coordinate
   */
  void getPosition(double& x, double& y) const;

  /**
   * @brief Gets the current orientation of the robot.
   *
   * @return The current orientation in radians
   */
  double getOrientation() const;

  /**
   * @brief Gets the current velocity of the robot.
   *
   * @param vx Output parameter for x velocity
   * @param vy Output parameter for y velocity
   */
  void getVelocity(double& vx, double& vy) const;

 private:
  Eigen::Vector2d position_;        ///< The current position of the robot
  double orientation_;              ///< The current orientation of the robot in radians
  Eigen::Vector2d velocity_;        ///< The current velocity of the robot
  Eigen::Vector2d targetVelocity_;  ///< The target velocity of the robot
  double maxAcceleration_;          ///< The maximum acceleration of the robot
  double maxVelocity_;              ///< The maximum velocity of the robot
  double minVelocity_;              ///< The minimum velocity of the robot
  double acceleration_;             ///< The current acceleration of the robot
};

}  // namespace mobilerobotsim
