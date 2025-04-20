include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/myunit/myunit/src
	)

add_compile_definitions(MYUNIT_VERBOSE=MYUNIT_VERB3_FAILED_ASSERTS)

add_subdirectory(myunit/myunit)
add_subdirectory(tests)
