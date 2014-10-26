cmake_minimum_required(VERSION 2.8.7)
project(Oz C)

include_directories ("${PROJECT_SOURCE_DIR}/lib/adt")

add_subdirectory("${PROJECT_SOURCE_DIR}/lib")
add_subdirectory("${PROJECT_SOURCE_DIR}/unittest")
