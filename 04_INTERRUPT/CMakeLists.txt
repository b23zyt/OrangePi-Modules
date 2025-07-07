cmake_minimum_required(VERSION 3.10)

project(exti_test)

find_library(WIRINGPI_LIBRARIES NAMES wiringPi)

include_directories(include)
link_directories(include)

set(sources
    main.cpp
    src/exti.cpp
)
add_executable(exti_test ${sources})
target_link_libraries(exti_test ${WIRINGPI_LIBRARIES})