cmake_minimum_required(VERSION 3.10) # 设置CMake的最低版本要求为3.10。确保CMake版本满足项目的需求。

project(led_test)# 定义项目名称为led_test。

find_library(WIRINGPI_LIBRARIES NAMES wiringPi)# 查找名为wiringPi的库，返回找到的库的路径并存储在WIRINGPI_LIBRARIES变量中。

# 添加一个可执行文件。第一个参数是可执行文件的名称，第二个参数是源代码文件列表。
add_executable(led_test main.cpp)# 此处创建一个名为led_test的可执行文件，源文件是main.cpp。

# 将找到的wiringPi库链接到led_test可执行文件。
target_link_libraries(led_test ${WIRINGPI_LIBRARIES})# 使用target_link_libraries将WIRINGPI_LIBRARIES与led_test进行链接。