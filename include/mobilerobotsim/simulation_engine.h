#pragma once

#include <vector>
#include <memory>
#include <string>

#include "mobilerobotsim/simulation_observer.h"

namespace mobilerobotsim {

// Forward declarations
class MobileRobotBase;
class Environment;
class SystemState;

/**
 * @brief Main simulation engine class.
 * 
 * SimulationEngine is the central coordinator for the simulation. It manages
 * the simulation time, robots, environment, and observers. It provides methods
 * for stepping the simulation forward, adding and removing robots, and
 * managing the simulation state.
 */
class SimulationEngine {
 public:
  /**
   * @brief Default constructor.
   * 
   * Creates a simulation engine with no robots, an empty environment,
   * and time set to zero.
   */
  SimulationEngine();

  /**
   * @brief Constructor with environment.
   * 
   * Creates a simulation engine with the specified environment,
   * no robots, and time set to zero.
   * 
   * @param environment The environment to use in the simulation
   */
  explicit SimulationEngine(std::unique_ptr<Environment> environment);

  /**
   * @brief Destructor.
   */
  ~SimulationEngine();

  /**
   * @brief Advances the simulation by the specified time step.
   * 
   * This method updates all robots and the environment based on the
   * specified time step, then notifies all observers of the updated state.
   * 
   * @param dt Time step size in seconds
   */
  void Step(double dt);

  /**
   * @brief Adds a robot to the simulation.
   * 
   * @param robot The robot to add
   */
  void AddRobot(std::unique_ptr<MobileRobotBase> robot);

  /**
   * @brief Removes a robot from the simulation.
   * 
   * @param index The index of the robot to remove
   * @return True if the robot was successfully removed, false otherwise
   */
  bool RemoveRobot(size_t index);

  /**
   * @brief Gets the number of robots in the simulation.
   * 
   * @return The number of robots
   */
  size_t GetRobotCount() const;

  /**
   * @brief Sets the environment for the simulation.
   * 
   * @param environment The environment to use
   */
  void SetEnvironment(std::unique_ptr<Environment> environment);

  /**
   * @brief Gets the current simulation time.
   * 
   * @return The current simulation time in seconds
   */
  double GetTime() const;

  /**
   * @brief Registers an observer for simulation events.
   * 
   * @param observer The observer to register
   */
  void RegisterObserver(SimulationObserver* observer);

  /**
   * @brief Unregisters an observer for simulation events.
   * 
   * @param observer The observer to unregister
   * @return True if the observer was successfully unregistered, false otherwise
   */
  bool UnregisterObserver(SimulationObserver* observer);

  /**
   * @brief Gets the current state of the simulation.
   * 
   * This method returns a representation of the complete simulation state,
   * including the states of all robots, the environment, and the simulation time.
   * 
   * @return A unique pointer to a SystemState object
   */
  std::unique_ptr<SystemState> GetState() const;

  /**
   * @brief Loads a previously saved simulation state.
   * 
   * This method reconstructs the simulation state from a previously saved
   * state object. This allows for state loading, time travel debugging, and
   * scenario replays.
   * 
   * @param state The state to load
   * @return True if the state was successfully loaded, false otherwise
   */
  bool LoadState(const SystemState& state);

  /**
   * @brief Saves the current simulation state to a file.
   * 
   * @param filename The name of the file to save to
   * @return True if the state was successfully saved, false otherwise
   */
  bool SaveStateToFile(const std::string& filename) const;

  /**
   * @brief Loads a simulation state from a file.
   * 
   * @param filename The name of the file to load from
   * @return True if the state was successfully loaded, false otherwise
   */
  bool LoadStateFromFile(const std::string& filename);

 private:
  /// The current simulation time in seconds
  double time_;

  /// Collection of robots in the simulation
  std::vector<std::unique_ptr<MobileRobotBase>> robots_;

  /// The environment for the simulation
  std::unique_ptr<Environment> environment_;

  /// Collection of observers for simulation events
  std::vector<SimulationObserver*> observers_;

  /**
   * @brief Notifies all observers of a simulation step.
   * 
   * @param state The current state of the simulation
   */
  void NotifyStep(const SystemState& state) const;

  /**
   * @brief Notifies all observers of a collision.
   * 
   * @param robot The robot involved in the collision
   * @param object The object involved in the collision
   */
  void NotifyCollision(const MobileRobotBase* robot, const void* object) const;

  /**
   * @brief Notifies all observers of a robot reaching a merge point.
   * 
   * @param robot The robot that reached the merge point
   * @param mergePoint The merge point that was reached
   */
  void NotifyMergePoint(const MobileRobotBase* robot, 
                        const EnvironmentElement* mergePoint) const;
};

} // namespace mobilerobotsim
