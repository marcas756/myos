add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/lib")

SET (MYOS_SOURCES 
    debug.c
)

SET (MYOS_OBJECTS
    $<TARGET_OBJECTS:lib>
    )

add_library(myos ${MYOS_SOURCES} ${MYOS_OBJECTS})