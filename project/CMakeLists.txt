cmake_minimum_required (VERSION 2.6)
project(myos C)

set_property(DIRECTORY APPEND PROPERTY
  COMPILE_DEFINITIONS $<$<CONFIG:Debug>:DEBUG=1>
)
  
set(CMAKE_C_FLAGS "-std=c99 -Wall -pedantic-errors")

include_directories (
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/source
    ${PROJECT_SOURCE_DIR}/source/lib 
    ${PROJECT_SOURCE_DIR}/source/os 
    ${PROJECT_SOURCE_DIR}/source/arch/hosted
    )


add_subdirectory("${PROJECT_SOURCE_DIR}/source")
add_subdirectory("${PROJECT_SOURCE_DIR}/unittest")


