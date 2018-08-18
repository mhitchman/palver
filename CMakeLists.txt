cmake_minimum_required(VERSION 3.8.2)
enable_testing()
option(ENABLE_TESTS "Enable testing" ON)

project(palver VERSION 0.1 LANGUAGES CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS YES)
set(custom_compile_options -Wall -Wextra -Wpedantic)

add_subdirectory(third_party)
add_subdirectory(src)

# INSTALL
install(DIRECTORY resources/ DESTINATION $ENV{HOME}/.palver USE_SOURCE_PERMISSIONS)
