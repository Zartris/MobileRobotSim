#pragma once

#include <vector>
#include <memory>
#include <string>
#include <Eigen/Dense>

namespace mobilerobotsim {

// Forward declarations
class EnvironmentState;

/**
 * @brief Interface for environment elements.
 * 
 * EnvironmentElement defines the interface for all environment elements,
 * such as lanes, obstacles, and merge points. It provides methods for
 * state access, collision detection, and serialization.
 */
class EnvironmentElement {
 public:
  /**
   * @brief Virtual destructor for proper cleanup of derived classes.
   */
  virtual ~EnvironmentElement() = default;

  /**
   * @brief Gets the type identifier of the environment element.
   * 
   * @return String identifier for the element type
   */
  virtual std::string GetTypeId() const = 0;

  /**
   * @brief Checks if a point collides with this element.
   * 
   * @param position The position to check for collision
   * @return True if the position collides with this element, false otherwise
   */
  virtual bool CheckCollision(const Eigen::Vector2d& position) const = 0;

  /**
   * @brief Gets the state of this environment element.
   * 
   * @return A string representation of the element's state
   */
  virtual std::string GetState() const = 0;

  /**
   * @brief Loads the state of this environment element.
   * 
   * @param state The state to load
   * @return True if the state was successfully loaded, false otherwise
   */
  virtual bool LoadState(const std::string& state) = 0;

 protected:
  /**
   * @brief Protected constructor to prevent direct instantiation.
   */
  EnvironmentElement() = default;
};

/**
 * @brief Class representing the environment state.
 * 
 * EnvironmentState encapsulates the state of all environment elements
 * at a specific point in time.
 */
class EnvironmentState {
 public:
  /**
   * @brief Default constructor.
   */
  EnvironmentState() = default;

  /**
   * @brief Destructor.
   */
  ~EnvironmentState() = default;

  /**
   * @brief Copy constructor.
   * 
   * @param other The EnvironmentState to copy
   */
  EnvironmentState(const EnvironmentState& other) = default;

  /**
   * @brief Move constructor.
   * 
   * @param other The EnvironmentState to move from
   */
  EnvironmentState(EnvironmentState&& other) noexcept = default;

  /**
   * @brief Copy assignment operator.
   * 
   * @param other The EnvironmentState to copy
   * @return Reference to this EnvironmentState
   */
  EnvironmentState& operator=(const EnvironmentState& other) = default;

  /**
   * @brief Move assignment operator.
   * 
   * @param other The EnvironmentState to move from
   * @return Reference to this EnvironmentState
   */
  EnvironmentState& operator=(EnvironmentState&& other) noexcept = default;

  /**
   * @brief Adds an element state to the environment state.
   * 
   * @param typeId The type identifier of the element
   * @param state The serialized state of the element
   */
  void AddElementState(const std::string& typeId, const std::string& state);

  /**
   * @brief Gets the element state at the specified index.
   * 
   * @param index The index of the element state to get
   * @param typeId Output parameter for the element type identifier
   * @param state Output parameter for the element state
   * @return True if the element state exists, false otherwise
   */
  bool GetElementState(size_t index, std::string& typeId, std::string& state) const;

  /**
   * @brief Gets the number of element states.
   * 
   * @return The number of element states
   */
  size_t GetElementStateCount() const;

  /**
   * @brief Serializes the environment state to a string representation.
   * 
   * @return String representation of the environment state
   */
  std::string Serialize() const;

  /**
   * @brief Deserializes an environment state from a string representation.
   * 
   * @param serialized The serialized state string
   * @return True if deserialization was successful, false otherwise
   */
  bool Deserialize(const std::string& serialized);

 private:
  /// Collection of element type identifiers
  std::vector<std::string> elementTypeIds_;

  /// Collection of element states
  std::vector<std::string> elementStates_;
};

/**
 * @brief Class representing the simulation environment.
 * 
 * Environment manages a collection of environment elements and provides
 * methods for updating, collision detection, and state management.
 */
class Environment {
 public:
  /**
   * @brief Default constructor.
   */
  Environment();

  /**
   * @brief Destructor.
   */
  ~Environment();

  /**
   * @brief Adds an environment element.
   * 
   * @param element The environment element to add
   */
  void AddElement(std::unique_ptr<EnvironmentElement> element);

  /**
   * @brief Updates the environment based on the current time step.
   * 
   * @param dt Time step size in seconds
   */
  void Update(double dt);

  /**
   * @brief Checks if a position collides with any environment element.
   * 
   * @param position The position to check
   * @return Pointer to the colliding element, or nullptr if no collision
   */
  const EnvironmentElement* CheckCollision(const Eigen::Vector2d& position) const;

  /**
   * @brief Gets the current state of the environment.
   * 
   * @return A unique pointer to an EnvironmentState object
   */
  std::unique_ptr<EnvironmentState> GetState() const;

  /**
   * @brief Loads a previously saved environment state.
   * 
   * @param state The environment state to load
   * @return True if the state was successfully loaded, false otherwise
   */
  bool LoadState(const EnvironmentState& state);

 private:
  /// Collection of environment elements
  std::vector<std::unique_ptr<EnvironmentElement>> elements_;
};

} // namespace mobilerobotsim
