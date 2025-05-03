# Define the source files for the core library
set(SOURCES
    simulation_engine.cpp
    environment.cpp
    mobile_robot_base.cpp
    point_robot.cpp
    system_state.cpp
)

# Define the header files (for IDE integration)
set(HEADERS
    ${CMAKE_SOURCE_DIR}/include/mobilerobotsim/simulation_engine.h
    ${CMAKE_SOURCE_DIR}/include/mobilerobotsim/environment.h
    ${CMAKE_SOURCE_DIR}/include/mobilerobotsim/mobile_robot_base.h
    ${CMAKE_SOURCE_DIR}/include/mobilerobotsim/point_robot.h
    ${CMAKE_SOURCE_DIR}/include/mobilerobotsim/system_state.h
    ${CMAKE_SOURCE_DIR}/include/mobilerobotsim/simulation_observer.h
)

# Create the core library
add_library(mobilerobotsim ${SOURCES} ${HEADERS})

# Link with external dependencies
target_link_libraries(mobilerobotsim
    PRIVATE
    Eigen3::Eigen
    nlohmann_json::nlohmann_json
)

# Set include directories for the library
target_include_directories(mobilerobotsim
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Set up installation targets
install(TARGETS mobilerobotsim
    EXPORT mobilerobotsim-targets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

# Add visualization component if enabled
if(BUILD_RENDERER)
    # Define renderer source files
    set(RENDERER_SOURCES
        renderer.cpp
    )
    
    # Define renderer headers
    set(RENDERER_HEADERS
        ${CMAKE_SOURCE_DIR}/include/mobilerobotsim/renderer.h
    )
    
    # Create renderer library
    add_library(mobilerobotsim_renderer ${RENDERER_SOURCES} ${RENDERER_HEADERS})
    
    # Link with core library and visualization dependencies
    target_link_libraries(mobilerobotsim_renderer
        PRIVATE
        mobilerobotsim
    )
    
    # Install renderer
    install(TARGETS mobilerobotsim_renderer
        EXPORT mobilerobotsim-targets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
    )
endif()

# Build a simple example application
add_executable(simulator_example examples/simulator_example.cpp)
target_link_libraries(simulator_example PRIVATE mobilerobotsim)
if(BUILD_RENDERER)
    target_link_libraries(simulator_example PRIVATE mobilerobotsim_renderer)
endif()
