# MobileRobotSim Project Brief

## Project Overview
MobileRobotSim is a flexible C++ simulator for mobile robots, with an initial focus on merge scenarios. The simulator features a decoupled visualization component to allow for headless operation and flexibility in rendering.

## Core Requirements

### Simulation Capabilities
- Simulate 2D robot kinematics (position, orientation, velocity)
- Implement logic for robot merging behaviors
- Support saving the complete simulation state to memory/file and loading it back
- Design for extensibility to different robot types and environments

### Technical Requirements
- Language: C++17
- Linear Algebra: Eigen library (version 3.4 or later)
- Build System: CMake
- Environment: Docker for consistent development and runtime environment

## Project Scope

### In Scope
- Core simulation engine with time management
- Environment representation (lanes, obstacles, merge points)
- Mobile robot base class and point robot implementation
- System state management for serialization and visualization
- Decoupled renderer component
- Basic serialization functionality
- Docker and VSCode containerization

### Out of Scope (Future Enhancements)
- Advanced physics simulation
- 3D simulation capabilities
- Real-time hardware interfaces
- Path planning algorithms (initially)
- Complex obstacle avoidance (initially)

## Success Criteria
- Successful simulation of point robots in a merge scenario
- Ability to save and load system state
- Visualization of the simulation
- Clean, modular architecture with well-defined interfaces
- Comprehensive documentation
- Containerized development environment
