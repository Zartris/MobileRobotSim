#include "mobilerobotsim/point_robot.h"
#include "mobilerobotsim/robot_state.h"

#include <cmath>

namespace mobilerobotsim {

// Forward declaration of PointRobotState
class PointRobotState : public RobotState {
 public:
  PointRobotState(double x, double y, double orientation, double vx, double vy);
  ~PointRobotState() override = default;
  
  std::string GetTypeId() const override { return "PointRobotState"; }
  std::unique_ptr<RobotState> Clone() const override;
  std::string Serialize() const override;
  bool Deserialize(const std::string& serialized) override;
  
  double x;
  double y;
  double orientation;
  double vx;
  double vy;
};

// Implementation of PointRobotState
PointRobotState::PointRobotState(double x, double y, double orientation, double vx, double vy)
    : x(x), y(y), orientation(orientation), vx(vx), vy(vy) {
}

std::unique_ptr<RobotState> PointRobotState::Clone() const {
  return std::make_unique<PointRobotState>(x, y, orientation, vx, vy);
}

std::string PointRobotState::Serialize() const {
  // Placeholder for serialization
  return "{}";  // Empty JSON object
}

bool PointRobotState::Deserialize(const std::string& serialized) {
  // Placeholder for deserialization
  return true;
}

// Implementation of PointRobot
PointRobot::PointRobot()
    : x_(0.0), y_(0.0), orientation_(0.0), vx_(0.0), vy_(0.0),
      targetVx_(0.0), targetVy_(0.0), maxAcceleration_(1.0) {
}

PointRobot::PointRobot(double x, double y)
    : x_(x), y_(y), orientation_(0.0), vx_(0.0), vy_(0.0),
      targetVx_(0.0), targetVy_(0.0), maxAcceleration_(1.0) {
}

PointRobot::PointRobot(double x, double y, double orientation, double vx, double vy)
    : x_(x), y_(y), orientation_(orientation), vx_(vx), vy_(vy),
      targetVx_(vx), targetVy_(vy), maxAcceleration_(1.0) {
}

PointRobot::~PointRobot() = default;

void PointRobot::UpdateState(double dt) {
  // Simple acceleration model to reach target velocity
  double dvx = targetVx_ - vx_;
  double dvy = targetVy_ - vy_;
  
  // Limit acceleration
  double accel = std::sqrt(dvx * dvx + dvy * dvy) / dt;
  if (accel > maxAcceleration_) {
    double scale = maxAcceleration_ / accel;
    dvx *= scale;
    dvy *= scale;
  }
  
  // Apply acceleration
  vx_ += dvx;
  vy_ += dvy;
  
  // Update position
  x_ += vx_ * dt;
  y_ += vy_ * dt;
  
  // Update orientation based on velocity
  if (std::abs(vx_) > 1e-6 || std::abs(vy_) > 1e-6) {
    orientation_ = std::atan2(vy_, vx_);
  }
}

std::unique_ptr<RobotState> PointRobot::GetState() const {
  return std::make_unique<PointRobotState>(x_, y_, orientation_, vx_, vy_);
}

bool PointRobot::LoadState(const RobotState& state) {
  const auto* pointState = dynamic_cast<const PointRobotState*>(&state);
  if (!pointState) {
    return false;
  }
  
  x_ = pointState->x;
  y_ = pointState->y;
  orientation_ = pointState->orientation;
  vx_ = pointState->vx;
  vy_ = pointState->vy;
  
  return true;
}

void PointRobot::SetTargetVelocity(double vx, double vy) {
  targetVx_ = vx;
  targetVy_ = vy;
}

void PointRobot::GetPosition(double& x, double& y) const {
  x = x_;
  y = y_;
}

double PointRobot::GetOrientation() const {
  return orientation_;
}

void PointRobot::GetVelocity(double& vx, double& vy) const {
  vx = vx_;
  vy = vy_;
}

} // namespace mobilerobotsim
