cmake_minimum_required(VERSION 2.8.8)
project(Oz C)


set_property(DIRECTORY APPEND PROPERTY
  COMPILE_DEFINITIONS $<$<CONFIG:Debug>:DEBUG=1>
)
  
set(CMAKE_C_FLAGS "-std=c99 -Wall -pedantic-errors")

add_custom_target(unittest_target)
macro(run_test test_target)
  add_custom_target(${test_target}_runtest
      COMMAND ${test_target} 
      DEPENDS ${test_target}
      WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")
  add_dependencies(unittest_target ${test_target}_runtest)
endmacro()

include_directories (
    "${PROJECT_SOURCE_DIR}"
    "${PROJECT_SOURCE_DIR}/lib"
    "${PROJECT_SOURCE_DIR}/core"
)


add_subdirectory("${PROJECT_SOURCE_DIR}/lib")
add_subdirectory("${PROJECT_SOURCE_DIR}/core")
add_subdirectory("${PROJECT_SOURCE_DIR}/unittest")

SET (OZ_SOURCES 
    debug.c
)

SET (OZ_OBJECTS
    $<TARGET_OBJECTS:slist>
    $<TARGET_OBJECTS:xlist>
    $<TARGET_OBJECTS:dlist>
    $<TARGET_OBJECTS:hash>
    $<TARGET_OBJECTS:lib>
    $<TARGET_OBJECTS:core>
    )

add_library(oz ${OZ_SOURCES} ${OZ_OBJECTS})

SET (OZ_OBJECTS_INSTRUM
    $<TARGET_OBJECTS:slist_instrum>
    $<TARGET_OBJECTS:xlist_instrum>
    $<TARGET_OBJECTS:dlist_instrum>
    $<TARGET_OBJECTS:hash_instrum>
    $<TARGET_OBJECTS:lib_instrum>
    $<TARGET_OBJECTS:core_instrum>
    )

add_library(oz_instrum ${OZ_SOURCES} ${OZ_OBJECTS_INSTRUM} $<TARGET_OBJECTS:maestra>)
set_target_properties(oz_instrum  PROPERTIES COMPILE_DEFINITIONS "MAESTRA_INSTRUM")


SET (OZ_OBJECTS_EXPOSED
    $<TARGET_OBJECTS:slist_exposed>
    #$<TARGET_OBJECTS:xlist>
    #$<TARGET_OBJECTS:dlist>
    #$<TARGET_OBJECTS:hash>
    #$<TARGET_OBJECTS:lib>
    $<TARGET_OBJECTS:core_exposed>
    )

add_library(oz_exposed ${OZ_SOURCES} ${OZ_OBJECTS_EXPOSED})
set_target_properties(oz_exposed  PROPERTIES COMPILE_DEFINITIONS "UNITTEST_EXPOSE")

SET (OZ_OBJECTS_INSTRUM_EXPOSED
    $<TARGET_OBJECTS:slist_instrum_exposed>
    #$<TARGET_OBJECTS:xlist_instrum>
    #$<TARGET_OBJECTS:dlist_instrum>
    #$<TARGET_OBJECTS:hash_instrum>
    #$<TARGET_OBJECTS:lib_instrum>
    $<TARGET_OBJECTS:core_instrum_exposed>
    )
    

add_library(oz_instrum_exposed ${OZ_SOURCES} ${OZ_OBJECTS_INSTRUM_EXPOSED} $<TARGET_OBJECTS:maestra>)
set_target_properties(oz_instrum_exposed  PROPERTIES COMPILE_DEFINITIONS "MAESTRA_INSTRUM;UNITTEST_EXPOSE")



