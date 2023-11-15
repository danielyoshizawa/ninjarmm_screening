cmake_minimum_required(VERSION 3.8)

set(TEST_NAME devTest)

set(FILES
    ../Developer.cpp
    Developer.test.cpp
    Pilot.test.cpp
)

add_executable("${TEST_NAME}" ${FILES})
target_include_directories("${TEST_NAME}" PUBLIC ../ ../../Lib/Clock)
target_link_libraries("${TEST_NAME}" PRIVATE Catch2::Catch2WithMain Clock)
set_property(TARGET "${TEST_NAME}" PROPERTY CMAKE_CXX_STANDARD 20)

add_test(NAME "${TEST_NAME}" COMMAND "${TEST_NAME}")
