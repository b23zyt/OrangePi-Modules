cmake_minimum_required(VERSION 3.10)

project(tim_test)

find_library(WIRINGPI_LIBRARIES NAMES wiringPi)

include_directories(include)
link_directories(include)

set(sources
    main.cpp
    src/tim.cpp
)
add_executable(tim_test ${sources})
target_link_libraries(tim_test ${WIRINGPI_LIBRARIES})