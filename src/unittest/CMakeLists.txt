

add_executable(unittest_ringbuffer unittest_ringbuffer.c)
add_executable(unittest_buffer unittest_buffer.c)
run_test(unittest_buffer)


add_executable(unittest_slist unittest_list.c)
set_target_properties(unittest_slist PROPERTIES COMPILE_DEFINITIONS "UNITTEST_SLIST")
target_link_libraries(unittest_slist adt)
run_test(unittest_slist)

add_executable(unittest_dlist unittest_list.c)
set_target_properties(unittest_dlist PROPERTIES COMPILE_DEFINITIONS "UNITTEST_DLIST")
target_link_libraries(unittest_dlist adt)
run_test(unittest_dlist)

add_executable(unittest_itempool unittest_itempool.c)
target_link_libraries(unittest_itempool adt)
run_test(unittest_itempool)