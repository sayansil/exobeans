set(BROKER_SOURCES
    broker.cpp
    job.cpp
    tube.cpp
    )

add_library(${BROKER_LIB} SHARED ${BROKER_SOURCES})
target_include_directories(${BROKER_LIB} PRIVATE
                           ${BROKER_SOURCE_DIR}/include)
target_link_libraries(${BROKER_LIB} PRIVATE)
