# set(CMAKE_BUILD_TYPE "RELEASE")
set(CMAKE_CXX_STANDARD 17)
set(BROKER_EXE "run")
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

add_subdirectory(cpr)

set(SOURCE_LIST
    src/main.cpp
    src/broker.cpp
    src/job.cpp
    src/tube.cpp
)

add_executable(${BROKER_EXE} ${SOURCE_LIST})
target_include_directories(${BROKER_EXE} PRIVATE
            include
            uWebSockets/src
            uWebSockets/uSockets/src)

target_link_libraries(${BROKER_EXE} PRIVATE
            cpr::cpr
            ${CMAKE_CURRENT_SOURCE_DIR}/uWebSockets/uSockets/uSockets.a
            dl
            pthread
            z)
