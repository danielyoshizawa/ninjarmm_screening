cmake_minimum_required(VERSION 3.8)

set(TEST_NAME validatorTest)

set(FILES
    Validator.test.cpp
)

add_executable("${TEST_NAME}" ${FILES})
target_include_directories("${TEST_NAME}" PUBLIC ../)
target_link_libraries("${TEST_NAME}" PRIVATE Catch2::Catch2WithMain Validator)
set_property(TARGET "${TEST_NAME}" 
    PROPERTY 
        CXX_STANDARD 20 
        CXX_STANDARD_REQUIRED ON)

add_test(NAME "${TEST_NAME}" COMMAND "${TEST_NAME}")
