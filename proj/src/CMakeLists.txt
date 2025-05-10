add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/lib")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/os")

SET (MYOS_SOURCES 

)

SET (MYOS_OBJECTS
    $<TARGET_OBJECTS:lib>
   # $<TARGET_OBJECTS:os>
   # $<TARGET_OBJECTS:os>
   # $<TARGET_OBJECTS:arch>
    
)

add_library(myos ${MYOS_SOURCES} ${MYOS_OBJECTS})
