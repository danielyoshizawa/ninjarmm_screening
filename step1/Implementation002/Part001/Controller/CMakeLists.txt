cmake_minimum_required(VERSION 3.8)

target_sources("${NAME}"
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/Controller.cpp
)

target_include_directories("${NAME}" PRIVATE .)