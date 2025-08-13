cmake_minimum_required(VERSION 3.10)
project(QubitTests)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)
enable_testing()

add_executable(test_qubit test_qubit.cc)
add_executable(test_3_qubit_code test_3_qubit_code.cc)

target_link_libraries(test_qubit PRIVATE qubit_lib GTest::gtest GTest::gtest_main pthread)
target_link_libraries(test_3_qubit_code PRIVATE qubit_lib GTest::gtest GTest::gtest_main pthread)

add_test(NAME QubitTest COMMAND test_qubit)
add_test(NAME ThreeQubitCodeTest COMMAND test_3_qubit_code)