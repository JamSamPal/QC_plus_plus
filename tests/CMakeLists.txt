add_executable(test_qubit test_qubit.cc)
add_executable(test_3_qubit_code test_3_qubit_code.cc)

find_package(GTest REQUIRED)

target_link_libraries(test_qubit PRIVATE qubit_lib GTest::gtest_main pthread)
target_link_libraries(test_3_qubit_code PRIVATE qubit_lib GTest::gtest_main pthread)

add_test(NAME QubitTest COMMAND test_qubit)
add_test(NAME ThreeQubitCodeTest COMMAND test_3_qubit_code)