#include "mobilerobotsim/simulation_engine.h"
#include "mobilerobotsim/mobile_robot_base.h"
#include "mobilerobotsim/environment.h"
#include "mobilerobotsim/system_state.h"

#include <fstream>
#include <nlohmann/json.hpp>

namespace mobilerobotsim {

SimulationEngine::SimulationEngine() : time_(0.0) {
  environment_ = std::make_unique<Environment>();
}

SimulationEngine::SimulationEngine(std::unique_ptr<Environment> environment)
    : time_(0.0), environment_(std::move(environment)) {
}

SimulationEngine::~SimulationEngine() = default;

void SimulationEngine::Step(double dt) {
  // Update all robots
  for (auto& robot : robots_) {
    robot->UpdateState(dt);
    
    // TODO: Implement collision detection and handling
    // TODO: Implement merge point detection and handling
  }
  
  // Update environment
  environment_->Update(dt);
  
  // Update simulation time
  time_ += dt;
  
  // Notify observers
  auto state = GetState();
  NotifyStep(*state);
}

void SimulationEngine::AddRobot(std::unique_ptr<MobileRobotBase> robot) {
  robots_.push_back(std::move(robot));
}

bool SimulationEngine::RemoveRobot(size_t index) {
  if (index >= robots_.size()) {
    return false;
  }
  
  robots_.erase(robots_.begin() + index);
  return true;
}

size_t SimulationEngine::GetRobotCount() const {
  return robots_.size();
}

void SimulationEngine::SetEnvironment(std::unique_ptr<Environment> environment) {
  environment_ = std::move(environment);
}

double SimulationEngine::GetTime() const {
  return time_;
}

void SimulationEngine::RegisterObserver(SimulationObserver* observer) {
  observers_.push_back(observer);
}

bool SimulationEngine::UnregisterObserver(SimulationObserver* observer) {
  auto it = std::find(observers_.begin(), observers_.end(), observer);
  if (it == observers_.end()) {
    return false;
  }
  
  observers_.erase(it);
  return true;
}

std::unique_ptr<SystemState> SimulationEngine::GetState() const {
  auto state = std::make_unique<SystemState>(time_);
  
  // Add robot states
  for (const auto& robot : robots_) {
    state->AddRobotState(robot->GetState());
  }
  
  // Add environment state
  state->SetEnvironmentState(environment_->GetState());
  
  return state;
}

bool SimulationEngine::LoadState(const SystemState& state) {
  time_ = state.GetTime();
  
  // TODO: Implement robot state loading
  // TODO: Implement environment state loading
  
  return true;
}

bool SimulationEngine::SaveStateToFile(const std::string& filename) const {
  auto state = GetState();
  std::string serialized = state->Serialize();
  
  std::ofstream file(filename);
  if (!file.is_open()) {
    return false;
  }
  
  file << serialized;
  file.close();
  
  return true;
}

bool SimulationEngine::LoadStateFromFile(const std::string& filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    return false;
  }
  
  std::string serialized;
  file >> serialized;
  file.close();
  
  auto state = std::make_unique<SystemState>();
  if (!state->Deserialize(serialized)) {
    return false;
  }
  
  return LoadState(*state);
}

void SimulationEngine::NotifyStep(const SystemState& state) const {
  for (auto observer : observers_) {
    observer->OnStep(state);
  }
}

void SimulationEngine::NotifyCollision(const MobileRobotBase* robot, const void* object) const {
  for (auto observer : observers_) {
    observer->OnCollision(robot, object);
  }
}

void SimulationEngine::NotifyMergePoint(const MobileRobotBase* robot, 
                                     const EnvironmentElement* mergePoint) const {
  for (auto observer : observers_) {
    observer->OnMergePoint(robot, mergePoint);
  }
}

} // namespace mobilerobotsim
