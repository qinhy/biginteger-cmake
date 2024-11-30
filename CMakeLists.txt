# CMakeLists.txt for biginteger
cmake_minimum_required(VERSION 3.10)

# Project details
project(biginteger LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Locate OpenCL
find_package(OpenCL REQUIRED)

# Include OpenCL headers
include_directories(${OpenCL_INCLUDE_DIRS})

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Define the library
file(GLOB_RECURSE BIGINTEGER_SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

# Create a static library target
add_library(biginteger STATIC ${BIGINTEGER_SOURCES})

add_executable(biginteger_test ./src/rsa.cpp)

# Link OpenCL libraries
target_link_libraries(biginteger ${OpenCL_LIBRARIES})
target_link_libraries(biginteger_test biginteger)

# Installation (optional)
install(TARGETS biginteger
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION include)
