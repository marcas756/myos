include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set (UNITTEST_SOURCES
	unittest_printf.c
)

set (UNITTEST_HEADERS
	unittest.h
)

add_library(unittest ${UNITTEST_SOURCES})

function(add_unittest TARGET)	
	add_executable(${TARGET} ${TARGET}.c $<TARGET_OBJECTS:unittest> )     
	target_link_libraries(${TARGET} myos)   
	target_compile_definitions(${TARGET} PRIVATE UNITTEST_VERBOSE)
	add_test(${TARGET} ${TARGET})
	#add_splint(${TARGET} ${TARGET}.c)
endfunction()



add_subdirectory(tests)

