cmake_minimum_required(VERSION 3.12)
project(serialPort)

include_directories(
    include
    "/home/unitree/z1_lib"
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

add_executable(serialPort main.cpp src/SerialPort.cpp)

add_library(serialPort_AMD64 SHARED src/SerialPort.cpp)
set_target_properties(serialPort_AMD64 PROPERTIES OUTPUT_NAME "serialPort_AMD64")


set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)