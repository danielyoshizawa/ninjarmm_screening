cmake_minimum_required(VERSION 3.8)

add_subdirectory(Tests)

target_sources("${NAME}"
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/Developer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Pilot.cpp
)

target_include_directories("${NAME}" PRIVATE .)
