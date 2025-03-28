include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_compile_definitions(MYUNIT_VERBOSE=MYUNIT_VERB3_FAILED_ASSERTS)




set (UNITTEST_SOURCES
	myunit_platform_linux.c
	myunit.c	
)

set (UNITTEST_HEADERS
	myunit.h
)

add_library(myunit ${UNITTEST_SOURCES})

add_subdirectory(tests)

