cmake_minimum_required (VERSION 3.8)
project(myunit C)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})


SET (MYUNIT_SOURCES
    myunit_platform_linux.c  
)

SET (MYUNIT_HEADERS
    myunit.h  
)


add_library(myunit ${MYUNIT_SOURCES})

add_executable(myunit_selftest myunit_selftest.c )
#target_compile_definitions(myunit_selftest PRIVATE  MYUNIT_VERBOSE=MYUNIT_VERB3_ALL_ASSERTS)
target_link_libraries(myunit_selftest myunit)

