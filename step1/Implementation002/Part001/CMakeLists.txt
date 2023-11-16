cmake_minimum_required(VERSION 3.8)

set(NAME "Step1Implementation002")

project("${NAME}" CXX)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.3.2 # or a later release
)

FetchContent_MakeAvailable(Catch2)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
enable_testing()

add_subdirectory(Lib/Clock)
add_subdirectory(Lib/Validator)
add_subdirectory(Lib/Time)

add_executable("${NAME}" main.cpp)
set_property(TARGET "${NAME}" 
    PROPERTY 
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON)

add_subdirectory(Model)
add_subdirectory(Controller)
add_subdirectory(View)

target_link_libraries("${NAME}" PUBLIC Clock Validator Time)