add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/portable")


SET (MYOS_SOURCES 
    debug.c
)

SET (MYOS_OBJECTS
    $<TARGET_OBJECTS:lib>
    $<TARGET_OBJECTS:os>
    $<TARGET_OBJECTS:arch>
    
)

add_library(myos ${MYOS_SOURCES} ${MYOS_OBJECTS})
