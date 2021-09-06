# set(CMAKE_BUILD_TYPE "RELEASE")
set(CMAKE_CXX_STANDARD 17)
set(PRODUCER_EXE "run")
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_CXX_FLAGS "-O3")

add_subdirectory(cpr)

set(SOURCE_LIST
    src/main.cpp
    src/producer.cpp
    src/job.cpp
)

add_executable(${PRODUCER_EXE} ${SOURCE_LIST})

target_include_directories(${PRODUCER_EXE} PRIVATE
            include
            json/include)

target_link_libraries(${PRODUCER_EXE}
            PRIVATE cpr::cpr)
