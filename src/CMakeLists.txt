add_library(qubit_lib
    Codes.cc
    Operators.cc
)

target_include_directories(qubit_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})