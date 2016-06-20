include_directories (
    "${PROJECT_SOURCE_DIR}/unittest"
)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/maestra")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/blackbox")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/whitebox")

SET (UNITTEST_SOURCES
    unittest.c 
    )

add_library(unittest STATIC ${UNITTEST_SOURCES})


