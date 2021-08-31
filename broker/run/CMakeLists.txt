set(SOURCE_LIST
    main.cpp
    )

add_executable(${BROKER_EXE} ${SOURCE_LIST})
target_include_directories(${BROKER_EXE} PRIVATE
                           ${BROKER_SOURCE_DIR}/include
                           )

target_link_libraries(${BROKER_EXE} PRIVATE ${BROKER_LIB})
