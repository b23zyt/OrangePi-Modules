cmake_minimum_required(VERSION 3.10)

project(key_test)

find_library(WIRINGPI_LIBRARIES NAMES wiringPi)

include_directories(include)
link_directories(include)

set(sources
    main.cpp
    src/key.cpp
)
add_executable(key_test ${sources})
target_link_libraries(key_test ${WIRINGPI_LIBRARIES})