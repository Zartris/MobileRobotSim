cmake_minimum_required(VERSION 3.10)
project(MobileRobotSim VERSION 0.1.0 LANGUAGES CXX)

# Set C++17 as the standard for all targets
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set default build type to Release if not specified
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type" FORCE)
endif()

# Export compile commands for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add custom modules path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Options
option(BUILD_TESTING "Build the testing tree" ON)
option(BUILD_RENDERER "Build visualization component" ON)
option(USE_SYSTEM_EIGEN "Use system-installed Eigen" ON)
option(ENABLE_SANITIZERS "Enable address/undefined sanitizers (debug only)" OFF)

# Dependencies
# Try to find system Eigen3 config first (preferred method on Ubuntu 24.04)
find_package(Eigen3 3.4 CONFIG QUIET)
if(NOT Eigen3_FOUND)
  # Fall back to module-based find
  find_package(Eigen3 3.4 MODULE REQUIRED)
endif()

find_package(nlohmann_json 3.0 REQUIRED)

# Include directories
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Add Eigen3 include directory - handle both config and module find methods
if(TARGET Eigen3::Eigen)
  # Eigen3 was found via CONFIG mode
  message(STATUS "Using Eigen3 via CONFIG mode")
else()
  # Eigen3 was found via MODULE mode
  message(STATUS "Using Eigen3 via MODULE mode")
  include_directories(${EIGEN3_INCLUDE_DIR})
endif()

# Add compiler warnings
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  add_compile_options(-Wall -Wextra -Wpedantic -Werror)
elseif(MSVC)
  add_compile_options(/W4 /WX)
endif()

# Sanitizers for debug builds
if(CMAKE_BUILD_TYPE STREQUAL "Debug" AND ENABLE_SANITIZERS)
  if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-fsanitize=address,undefined -fno-omit-frame-pointer)
    add_link_options(-fsanitize=address,undefined)
  endif()
endif()

# Add subdirectories
add_subdirectory(src)

# Install headers
install(DIRECTORY include/ DESTINATION include)

# Testing
if(BUILD_TESTING)
  enable_testing()
  add_subdirectory(test)
endif()

# Documentation
find_package(Doxygen)
if(DOXYGEN_FOUND)
  add_custom_target(docs
    ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Generating API documentation with Doxygen" VERBATIM
  )
endif()

# Package information for CPack
include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_VENDOR "MobileRobotSim Team")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A flexible C++ simulator for mobile robots")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
include(CPack)

# Print build configuration summary
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Build testing: ${BUILD_TESTING}")
message(STATUS "Build renderer: ${BUILD_RENDERER}")
message(STATUS "System Eigen: ${USE_SYSTEM_EIGEN}")
message(STATUS "Sanitizers: ${ENABLE_SANITIZERS}")
