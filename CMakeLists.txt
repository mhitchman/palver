cmake_minimum_required(VERSION 3.8.2)
enable_testing()

project(palver VERSION 0.1 LANGUAGES CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS YES)
set(custom_compile_options -Wall -Wextra -Wpedantic)

add_subdirectory(third_party)
add_subdirectory(src)
