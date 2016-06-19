add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/slist")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/dlist")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/xlist")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/hash")

SET (LIB_SOURCES
    itempool.c 
    )

add_library(lib OBJECT ${LIB_SOURCES})

add_library(lib_instrum OBJECT ${LIB_SOURCES})
set_target_properties(lib_instrum  PROPERTIES COMPILE_DEFINITIONS "MAESTRA_INSTRUM")
