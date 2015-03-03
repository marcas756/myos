cmake_minimum_required(VERSION 2.8.8)
project(Oz C)

add_custom_target(test)
macro(run_test test_target)
  add_custom_target(${test_target}_runtest
      COMMAND ${test_target} 
      DEPENDS ${test_target}
      WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")
  add_dependencies(test ${test_target}_runtest)
endmacro()

include_directories (
    "${PROJECT_SOURCE_DIR}"
    "${PROJECT_SOURCE_DIR}/lib/adt"
    "${PROJECT_SOURCE_DIR}/lib/adt/slist"
    "${PROJECT_SOURCE_DIR}/core"
)


add_subdirectory("${PROJECT_SOURCE_DIR}/lib")
add_subdirectory("${PROJECT_SOURCE_DIR}/core")
add_subdirectory("${PROJECT_SOURCE_DIR}/unittest")




