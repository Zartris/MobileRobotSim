#pragma once

#include <vector>
#include <memory>
#include <string>

namespace mobilerobotsim {

// Forward declarations
class RobotState;
class EnvironmentState;

/**
 * @brief Class representing the complete state of the simulation system.
 * 
 * SystemState encapsulates the entire state of the simulation at a specific point in time,
 * including the states of all robots, the environment, and the simulation time.
 * This class serves as the primary interface for visualization and serialization.
 */
class SystemState {
 public:
  /**
   * @brief Default constructor.
   */
  SystemState();

  /**
   * @brief Constructor with initial time.
   * 
   * @param time The simulation time in seconds
   */
  explicit SystemState(double time);

  /**
   * @brief Copy constructor.
   * 
   * @param other The SystemState to copy
   */
  SystemState(const SystemState& other);

  /**
   * @brief Move constructor.
   * 
   * @param other The SystemState to move from
   */
  SystemState(SystemState&& other) noexcept;

  /**
   * @brief Copy assignment operator.
   * 
   * @param other The SystemState to copy
   * @return Reference to this SystemState
   */
  SystemState& operator=(const SystemState& other);

  /**
   * @brief Move assignment operator.
   * 
   * @param other The SystemState to move from
   * @return Reference to this SystemState
   */
  SystemState& operator=(SystemState&& other) noexcept;

  /**
   * @brief Destructor.
   */
  ~SystemState();

  /**
   * @brief Gets the simulation time.
   * 
   * @return The current simulation time in seconds
   */
  double GetTime() const;

  /**
   * @brief Sets the simulation time.
   * 
   * @param time The simulation time in seconds
   */
  void SetTime(double time);

  /**
   * @brief Adds a robot state to the system state.
   * 
   * @param robotState The robot state to add
   */
  void AddRobotState(std::unique_ptr<RobotState> robotState);

  /**
   * @brief Gets the robot state at the specified index.
   * 
   * @param index The index of the robot state to get
   * @return const pointer to the robot state
   */
  const RobotState* GetRobotState(size_t index) const;

  /**
   * @brief Gets the number of robot states.
   * 
   * @return The number of robot states
   */
  size_t GetRobotStateCount() const;

  /**
   * @brief Sets the environment state.
   * 
   * @param environmentState The environment state to set
   */
  void SetEnvironmentState(std::unique_ptr<EnvironmentState> environmentState);

  /**
   * @brief Gets the environment state.
   * 
   * @return const pointer to the environment state
   */
  const EnvironmentState* GetEnvironmentState() const;

  /**
   * @brief Serializes the system state to a string representation.
   * 
   * @return String representation of the system state
   */
  std::string Serialize() const;

  /**
   * @brief Deserializes a system state from a string representation.
   * 
   * @param serialized The serialized state string
   * @return True if deserialization was successful, false otherwise
   */
  bool Deserialize(const std::string& serialized);

 private:
  /// The current simulation time in seconds
  double time_;

  /// Collection of robot states
  std::vector<std::unique_ptr<RobotState>> robotStates_;

  /// Environment state
  std::unique_ptr<EnvironmentState> environmentState_;
};

} // namespace mobilerobotsim
