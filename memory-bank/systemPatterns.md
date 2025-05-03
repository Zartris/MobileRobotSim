# MobileRobotSim System Patterns

## System Architecture

### High-Level Architecture
```mermaid
graph TD
    User[User] --> SimEngine[Simulation Engine]
    SimEngine --> Env[Environment]
    SimEngine --> Robots[Mobile Robots]
    SimEngine --> Serializer[Serializer]
    SimEngine --> SysState[System State]
    SysState --> Renderer[Renderer]
    User --> Renderer
```

The MobileRobotSim architecture follows a clear separation of concerns with these primary components:

1. **Simulation Engine**: Central coordinator that manages the simulation loop, time advancement, and orchestrates interactions between robots and the environment.

2. **Environment**: Represents the static world elements such as lanes, obstacles, and merge points.

3. **Mobile Robots**: Hierarchy of robot implementations that follow a common interface but can have different kinematics and behaviors.

4. **System State**: Data structure that captures the complete simulation state at a point in time.

5. **Renderer**: Decoupled visualization component that consumes system state to produce visual output.

6. **Serializer**: Utility for converting system state to/from persistent storage formats.

## Key Design Patterns

### Abstract Factory
Used for creating different types of robots while maintaining a common interface:

```mermaid
classDiagram
    class MobileRobotFactory {
        <<interface>>
        +createRobot() MobileRobotBase
    }
    
    class PointRobotFactory {
        +createRobot() PointRobot
    }
    
    class CarRobotFactory {
        +createRobot() CarRobot
    }
    
    MobileRobotFactory <|-- PointRobotFactory
    MobileRobotFactory <|-- CarRobotFactory
```

### Strategy Pattern
Applied to robot behaviors, allowing different merging strategies to be swapped dynamically:

```mermaid
classDiagram
    class MergeStrategy {
        <<interface>>
        +calculateMergeAction(robotState, environment) Action
    }
    
    class ZipperMergeStrategy {
        +calculateMergeAction(robotState, environment) Action
    }
    
    class PriorityMergeStrategy {
        +calculateMergeAction(robotState, environment) Action
    }
    
    MergeStrategy <|-- ZipperMergeStrategy
    MergeStrategy <|-- PriorityMergeStrategy
```

### Observer Pattern
Used for simulation events notification:

```mermaid
classDiagram
    class SimulationObserver {
        <<interface>>
        +onStep(SystemState)
        +onCollision(Robot, Object)
        +onMergePoint(Robot, MergePoint)
    }
    
    class Renderer {
        +onStep(SystemState)
    }
    
    class Logger {
        +onStep(SystemState)
        +onCollision(Robot, Object)
        +onMergePoint(Robot, MergePoint)
    }
    
    SimulationObserver <|-- Renderer
    SimulationObserver <|-- Logger
```

### Composite Pattern
Applied to environmental elements to create complex environments from simple components:

```mermaid
classDiagram
    class EnvironmentElement {
        <<interface>>
        +getState()
        +loadState(state)
        +checkCollision(position)
    }
    
    class Lane {
        +getState()
        +loadState(state)
        +checkCollision(position)
    }
    
    class Obstacle {
        +getState()
        +loadState(state)
        +checkCollision(position)
    }
    
    class CompositeEnvironment {
        -elements: EnvironmentElement[]
        +getState()
        +loadState(state)
        +checkCollision(position)
        +addElement(EnvironmentElement)
        +removeElement(EnvironmentElement)
    }
    
    EnvironmentElement <|-- Lane
    EnvironmentElement <|-- Obstacle
    EnvironmentElement <|-- CompositeEnvironment
    CompositeEnvironment o-- EnvironmentElement
```

## Component Relationships

### Core Class Structure
```mermaid
classDiagram
    class SimulationEngine {
        -robots: vector<MobileRobotBase*>
        -environment: Environment
        -time: double
        -observers: vector<SimulationObserver*>
        +step(dt: double)
        +addRobot(robot: MobileRobotBase*)
        +getState(): SystemState
        +loadState(state: SystemState)
        +registerObserver(observer: SimulationObserver*)
    }
    
    class SystemState {
        -robotStates: vector<RobotState>
        -environmentState: EnvironmentState
        -simulationTime: double
    }
    
    class MobileRobotBase {
        <<abstract>>
        #position
        #orientation
        #velocity
        +updateState(dt: double)*
        +getState(): RobotState*
        +loadState(state: RobotState)*
    }
    
    class PointRobot {
        -position: Eigen::Vector2d
        -orientation: double
        -velocity: Eigen::Vector2d
        +updateState(dt: double)
        +getState(): PointRobotState
        +loadState(state: PointRobotState)
    }
    
    class Environment {
        -elements: vector<EnvironmentElement*>
        +update(dt: double)
        +getState(): EnvironmentState
        +loadState(state: EnvironmentState)
        +addElement(element: EnvironmentElement*)
    }
    
    class Renderer {
        +render(state: SystemState)
    }
    
    MobileRobotBase <|-- PointRobot
    SimulationEngine o-- MobileRobotBase
    SimulationEngine o-- Environment
    SimulationEngine --> SystemState
    SimulationObserver <|-- Renderer
    SimulationEngine o-- SimulationObserver
```

## Data Flow

### Simulation Loop
```mermaid
sequenceDiagram
    participant User
    participant SimEngine as SimulationEngine
    participant Robots as MobileRobots
    participant Env as Environment
    participant State as SystemState
    participant Renderer
    
    User->>SimEngine: initialize()
    User->>SimEngine: step(dt)
    SimEngine->>Robots: updateState(dt)
    SimEngine->>Env: update(dt)
    Robots-->>SimEngine: updated states
    Env-->>SimEngine: updated environment
    SimEngine->>State: update with new states
    SimEngine->>Renderer: onStep(SystemState)
    Renderer-->>User: visual output
    
    Note over SimEngine,State: State can be saved/loaded at any point
```

## State Management

Every component in the system that maintains state implements:
1. `getState()` - Returns a serializable representation of its current state
2. `loadState(state)` - Reconstructs its state from a previously saved state

This consistent interface enables:
- Complete system snapshots
- Time travel debugging
- Scenario replays
- Crash analysis
- "What-if" experimentation

## Extension Points

The system is designed with several planned extension points:

1. **New Robot Types**: By implementing MobileRobotBase interface
2. **Alternative Environments**: Through the EnvironmentElement interface
3. **Different Rendering Options**: By implementing the SimulationObserver interface
4. **Custom Merge Behaviors**: Via the Strategy pattern for merge algorithms
5. **Spatial Optimization**: Future Quadtree implementation for efficient neighbor searching
