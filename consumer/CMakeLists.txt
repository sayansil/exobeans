# set(CMAKE_BUILD_TYPE "RELEASE")
set(CMAKE_CXX_STANDARD 17)
set(CONSUMER_EXE "run")
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_CXX_FLAGS "-O3")

add_subdirectory(cpr)

set(SOURCE_LIST
    src/main.cpp
    src/consumer.cpp
    src/job.cpp
)

add_executable(${CONSUMER_EXE} ${SOURCE_LIST})

target_include_directories(${CONSUMER_EXE} PRIVATE
            include
            json/include)

target_link_libraries(${CONSUMER_EXE}
            PRIVATE cpr::cpr)
