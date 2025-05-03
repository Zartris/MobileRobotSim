#include "mobilerobotsim/system_state.h"
#include "mobilerobotsim/robot_state.h"
#include "mobilerobotsim/environment.h"

namespace mobilerobotsim {

SystemState::SystemState() : time_(0.0) {
}

SystemState::SystemState(double time) : time_(time) {
}

SystemState::SystemState(const SystemState& other) : time_(other.time_) {
  // Clone robot states
  for (const auto& robotState : other.robotStates_) {
    robotStates_.push_back(robotState->Clone());
  }
  
  // Clone environment state
  if (other.environmentState_) {
    environmentState_ = std::make_unique<EnvironmentState>(*other.environmentState_);
  }
}

SystemState::SystemState(SystemState&& other) noexcept
    : time_(other.time_),
      robotStates_(std::move(other.robotStates_)),
      environmentState_(std::move(other.environmentState_)) {
}

SystemState& SystemState::operator=(const SystemState& other) {
  if (this != &other) {
    time_ = other.time_;
    
    // Clone robot states
    robotStates_.clear();
    for (const auto& robotState : other.robotStates_) {
      robotStates_.push_back(robotState->Clone());
    }
    
    // Clone environment state
    if (other.environmentState_) {
      environmentState_ = std::make_unique<EnvironmentState>(*other.environmentState_);
    } else {
      environmentState_.reset();
    }
  }
  
  return *this;
}

SystemState& SystemState::operator=(SystemState&& other) noexcept {
  if (this != &other) {
    time_ = other.time_;
    robotStates_ = std::move(other.robotStates_);
    environmentState_ = std::move(other.environmentState_);
  }
  
  return *this;
}

SystemState::~SystemState() = default;

double SystemState::GetTime() const {
  return time_;
}

void SystemState::SetTime(double time) {
  time_ = time;
}

void SystemState::AddRobotState(std::unique_ptr<RobotState> robotState) {
  robotStates_.push_back(std::move(robotState));
}

const RobotState* SystemState::GetRobotState(size_t index) const {
  if (index >= robotStates_.size()) {
    return nullptr;
  }
  
  return robotStates_[index].get();
}

size_t SystemState::GetRobotStateCount() const {
  return robotStates_.size();
}

void SystemState::SetEnvironmentState(std::unique_ptr<EnvironmentState> environmentState) {
  environmentState_ = std::move(environmentState);
}

const EnvironmentState* SystemState::GetEnvironmentState() const {
  return environmentState_.get();
}

std::string SystemState::Serialize() const {
  // Placeholder for serialization
  return "{}";  // Empty JSON object
}

bool SystemState::Deserialize(const std::string& serialized) {
  // Placeholder for deserialization
  return true;
}

} // namespace mobilerobotsim
