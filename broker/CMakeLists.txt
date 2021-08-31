cmake_minimum_required(VERSION 3.5)

project(BROKER
    DESCRIPTION "Exobeanstalkd Broker"
    LANGUAGES C CXX
    )


include(FetchContent)
include(cmake/download_file.cmake)

if(${CMAKE_VERSION} VERSION_LESS 3.14)
    include(cmake/add_FetchContent_MakeAvailable.cmake)
endif()

set(BROKER_LIB "broker")
set(BROKER_EXE "run")
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

find_program(CCACHE_PROGRAM ccache)

if(CCACHE_PROGRAM)
    MESSAGE("CCACHE support enabled")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK "${CCACHE_PROGRAM}")
endif()

set(CMAKE_BUILD_TYPE "RELEASE")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE 1)

set(FETCHCONTENT_QUIET FALSE)

add_subdirectory(src)
add_subdirectory(run)
