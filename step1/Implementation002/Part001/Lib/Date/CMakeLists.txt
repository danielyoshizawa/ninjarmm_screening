cmake_minimum_required(VERSION 3.8)

set(LIBNAME Date)

include(GNUInstallDirs)

project("${LIBNAME}" VERSION 1.0.0 DESCRIPTION "Date Lib")

add_library("${LIBNAME}" INTERFACE)
# TODO : Do I need this? Since our lib is header only it will be compiled with our project
set_target_properties("${LIBNAME}" PROPERTIES 
                        VERSION ${PROJECT_VERSION}
                        PUBLIC_HEADER Date.h
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
