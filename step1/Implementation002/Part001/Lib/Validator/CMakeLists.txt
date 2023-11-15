cmake_minimum_required(VERSION 3.8)

set(LIBNAME Validator)

include(GNUInstallDirs)

project("${LIBNAME}" VERSION 1.0.0 DESCRIPTION "Validator Lib")

add_library("${LIBNAME}" INTERFACE)
# TODO : Do I need this? Since our lib is header only it will be compiled with our project
set_target_properties("${LIBNAME}" PROPERTIES 
                        VERSION ${PROJECT_VERSION}
                        PUBLIC_HEADER Validator.h
                        CXX_STANDARD 20
                        CXX_STANDARD_REQUIRED ON
                    )

# TODO : Do I need to install?
install(TARGETS "${LIBNAME}"
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        )

target_include_directories("${LIBNAME}" INTERFACE .)

add_subdirectory(Tests)

# TODO : Remove before commiting
# Sandbox
# add_executable(ClockSandBox sandbox.cpp)
# target_include_directories(ClockSandBox PRIVATE .)
# target_link_libraries(ClockSandBox PRIVATE Clock)
# set_property(TARGET ClockSandBox 
#     PROPERTY 
#         CXX_STANDARD 20 
#         CXX_STANDARD_REQUIRED ON)
