#include "mobilerobotsim/simulation_engine.h"
#include "mobilerobotsim/point_robot.h"

#include <iostream>
#include <memory>
#include <thread>
#include <chrono>

using namespace mobilerobotsim;

int main() {
    // Create a simulation engine
    auto engine = std::make_unique<SimulationEngine>();
    
    // Add some robots
    engine->AddRobot(std::make_unique<PointRobot>(0.0, 0.0));
    engine->AddRobot(std::make_unique<PointRobot>(1.0, 1.0));
    engine->AddRobot(std::make_unique<PointRobot>(2.0, 2.0, 0.0, 0.5, 0.5));
    
    // Run the simulation for 10 seconds
    double time = 0.0;
    double dt = 0.1;  // 100 ms time step
    
    std::cout << "Starting simulation..." << std::endl;
    
    while (time < 10.0) {
        engine->Step(dt);
        time += dt;
        
        // Print the simulation time
        std::cout << "Simulation time: " << time << " seconds" << std::endl;
        
        // In a real application, we would visualize the simulation here
        
        // Sleep for a bit to slow down the simulation for demonstration
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    
    std::cout << "Simulation complete!" << std::endl;
    
    // Save the final state to a file
    if (engine->SaveStateToFile("simulation_final_state.json")) {
        std::cout << "Final state saved to 'simulation_final_state.json'" << std::endl;
    } else {
        std::cerr << "Failed to save final state" << std::endl;
    }
    
    return 0;
}
