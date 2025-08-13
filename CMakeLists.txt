cmake_minimum_required(VERSION 3.10)
project(QuantumErrorCodeProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_library(qubit_lib src/Codes.cc
)

target_include_directories(qubit_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

enable_testing()

add_subdirectory(tests)