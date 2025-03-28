cmake_minimum_required (VERSION 2.6)
project(myos C)

set_property(DIRECTORY APPEND PROPERTY
  COMPILE_DEFINITIONS $<$<CONFIG:Debug>:DEBUG=1>
)
  
set(CMAKE_C_FLAGS "-std=c99 -Wall -pedantic-errors -O1")


include_directories (
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/src/lib 
#    ${PROJECT_SOURCE_DIR}/source/os 
#    ${PROJECT_SOURCE_DIR}/source/arch/hosted/linux
    )
add_compile_definitions(UNITTEST)

add_subdirectory("${PROJECT_SOURCE_DIR}/src")
add_subdirectory("${PROJECT_SOURCE_DIR}/unittest")
#add_subdirectory("${PROJECT_SOURCE_DIR}/source/arch/hosted/linux")

