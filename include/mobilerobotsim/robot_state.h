#pragma once

#include <string>
#include <memory>

namespace mobilerobotsim {

/**
 * @brief Base class for robot state representations.
 * 
 * RobotState serves as a base class for different types of robot state representations.
 * It defines the common interface for all robot states, including serialization and
 * type identification.
 */
class RobotState {
 public:
  /**
   * @brief Virtual destructor for proper cleanup of derived classes.
   */
  virtual ~RobotState() = default;

  /**
   * @brief Gets the type identifier of the robot state.
   * 
   * This method returns a string identifier for the specific type of robot state,
   * which is used for serialization and type checking during deserialization.
   * 
   * @return String identifier for the robot state type
   */
  virtual std::string GetTypeId() const = 0;

  /**
   * @brief Creates a clone of this robot state.
   * 
   * @return A unique pointer to a new RobotState that is a copy of this one
   */
  virtual std::unique_ptr<RobotState> Clone() const = 0;

  /**
   * @brief Serializes the robot state to a string representation.
   * 
   * @return String representation of the robot state
   */
  virtual std::string Serialize() const = 0;

  /**
   * @brief Deserializes a robot state from a string representation.
   * 
   * @param serialized The serialized state string
   * @return True if deserialization was successful, false otherwise
   */
  virtual bool Deserialize(const std::string& serialized) = 0;

 protected:
  /**
   * @brief Protected constructor to prevent direct instantiation.
   * 
   * RobotState is an abstract class and should not be instantiated directly.
   * Derived classes should call this constructor from their own constructors.
   */
  RobotState() = default;
};

} // namespace mobilerobotsim
