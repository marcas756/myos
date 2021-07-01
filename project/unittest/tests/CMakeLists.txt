include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(unittest_slist unittest_list.c)
set_target_properties(unittest_slist PROPERTIES COMPILE_DEFINITIONS "UNITTEST_SLIST")
target_link_libraries(unittest_slist myos unittest)

add_executable(unittest_dlist unittest_list.c)
set_target_properties(unittest_dlist PROPERTIES COMPILE_DEFINITIONS "UNITTEST_DLIST")
target_link_libraries(unittest_dlist myos unittest)


add_executable(unittest_process unittest_process.c)
set_target_properties(unittest_process PROPERTIES COMPILE_DEFINITIONS "PROCESS_LIST_TYPE=SLIST")
target_link_libraries(unittest_process myos unittest)

add_executable(unittest_timer unittest_timer.c)
target_link_libraries(unittest_timer myos unittest)

add_executable(unittest_ctimer unittest_ctimer.c)
set_target_properties(unittest_ctimer PROPERTIES COMPILE_DEFINITIONS "PROCESS_LIST_TYPE=SLIST")
target_link_libraries(unittest_ctimer myos unittest)