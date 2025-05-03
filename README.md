# MobileRobotSim

A flexible C++ simulator for mobile robots, with an initial focus on merge scenarios.

## Overview

MobileRobotSim is a lightweight, flexible simulation environment specifically designed for studying mobile robot interactions, particularly in merge scenarios. The simulator features a decoupled visualization component to allow for headless operation and flexibility in rendering.

## Features

- 2D robot kinematics simulation (position, orientation, velocity)
- Robot merging behavior implementation
- Complete simulation state saving and loading
- Extensible design for different robot types and environments
- Decoupled visualization component

## Requirements

- C++17 compliant compiler
- CMake 3.10+
- Eigen 3.4+
- Docker (recommended for consistent development environment)
- VSCode with Remote Containers extension (for containerized development)

## Project Structure

```
MobileRobotSim/
├── include/              # Header files
│   └── mobilerobotsim/   # Public API headers
├── src/                  # Implementation files
├── test/                 # Test files
├── docs/                 # Documentation
├── cmake/                # CMake modules and helpers
├── .devcontainer/        # VSCode container configuration
├── memory-bank/          # Project documentation
└── CMakeLists.txt        # Main build configuration
```

## Getting Started

### Using Docker and VSCode

1. Ensure Docker and VSCode with Remote Containers extension are installed
2. Clone the repository
3. Open the folder in VSCode
4. Click "Reopen in Container" when prompted
5. Build the project using CMake

### Manual Setup

1. Install required dependencies (C++17 compiler, CMake, Eigen 3.4+)
2. Clone the repository
3. Configure and build:
   ```bash
   mkdir build && cd build
   cmake ..
   make
   ```

## Core Components

- **SimulationEngine**: Orchestrates the simulation loop, manages time, robots, and environment
- **Environment**: Represents static world elements (lanes, obstacles, merge points)
- **MobileRobotBase**: Abstract base class defining the robot interface
- **PointRobot**: Concrete implementation of a simple holonomic robot
- **SystemState**: Data structure holding a complete simulation snapshot
- **Renderer**: Visualization module that takes SystemState and renders it

## License

[License information to be determined]

## Development Tools

### clangd Integration

The project includes full integration with clangd for improved code intelligence:

- Faster and more accurate code completion
- Better navigation and refactoring
- Real-time error detection
- Integration with clang-tidy

Configuration files are organized in the `config/` directory, and helper scripts in the `scripts/` directory. See [docs/clangd-setup.md](docs/clangd-setup.md) for detailed setup and usage information.

## Contributing

Contribution guidelines will be added as the project matures.
