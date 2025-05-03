#pragma once

#include "simulation_observer.h"

namespace mobilerobotsim {

// Forward declarations
class SystemState;
class MobileRobotBase;
class EnvironmentElement;

/**
 * @brief Interface for renderer components.
 * 
 * Renderer is an implementation of the SimulationObserver interface
 * that visualizes the simulation state. It provides methods for
 * initialization, rendering, and cleanup.
 */
class Renderer : public SimulationObserver {
 public:
  /**
   * @brief Default constructor.
   */
  Renderer();

  /**
   * @brief Destructor.
   */
  ~Renderer() override;
  
  /**
   * @brief Called when a simulation step is completed.
   * 
   * This method is invoked by the SimulationEngine after each simulation step
   * is completed, triggering a rendering update.
   * 
   * @param state Reference to the current state of the simulation
   */
  void OnStep(const SystemState& state) override;

  /**
   * @brief Called when a collision is detected.
   * 
   * This method is invoked when a collision is detected, allowing
   * the renderer to visualize the collision.
   * 
   * @param robot Pointer to the robot involved in the collision
   * @param object Pointer to the object involved in the collision
   */
  void OnCollision(const MobileRobotBase* robot, 
                 const void* object) override;

  /**
   * @brief Called when a robot reaches a merge point.
   * 
   * This method is invoked when a robot reaches a designated merge point,
   * allowing the renderer to visualize the merge event.
   * 
   * @param robot Pointer to the robot that reached the merge point
   * @param mergePoint Pointer to the merge point that was reached
   */
  void OnMergePoint(const MobileRobotBase* robot, 
                   const EnvironmentElement* mergePoint) override;
  
  /**
   * @brief Initializes the renderer.
   * 
   * This method sets up the rendering environment, such as
   * creating a window, initializing graphics libraries, etc.
   * 
   * @return True if initialization was successful, false otherwise
   */
  bool Initialize();
  
  /**
   * @brief Renders the current simulation state.
   * 
   * This method visualizes the current state of the simulation,
   * including robots, environment elements, and other visual elements.
   * 
   * @param state The state to render
   */
  void Render(const SystemState& state);
  
  /**
   * @brief Shuts down the renderer.
   * 
   * This method cleans up resources used by the renderer,
   * such as closing windows, releasing graphics resources, etc.
   */
  void Shutdown();
  
 private:
  /// Flag indicating whether the renderer has been initialized
  bool initialized_;
};

} // namespace mobilerobotsim
