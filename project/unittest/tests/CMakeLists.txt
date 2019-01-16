include_directories(${CMAKE_CURRENT_LIST_DIR})



add_executable(unittest_slist unittest_list.c)
set_target_properties(unittest_slist PROPERTIES COMPILE_DEFINITIONS "UNITTEST_SLIST")
target_link_libraries(unittest_slist myos unittest)

