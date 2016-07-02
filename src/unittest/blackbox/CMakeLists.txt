add_executable(utbb_ringbuffer utbb_ringbuffer.c)
target_link_libraries(utbb_ringbuffer unittest)

add_executable(utbb_buffer utbb_buffer.c)
target_link_libraries(utbb_buffer unittest)
run_test(utbb_buffer)


add_executable(utbb_slist utbb_list.c)
set_target_properties(utbb_slist PROPERTIES COMPILE_DEFINITIONS "UTBB_SLIST")
target_link_libraries(utbb_slist oz unittest)
run_test(utbb_slist)

add_executable(utbb_slist_instrum utbb_list.c)
set_target_properties(utbb_slist_instrum PROPERTIES COMPILE_DEFINITIONS "UTBB_SLIST")
target_link_libraries(utbb_slist_instrum oz_instrum unittest)
run_test(utbb_slist_instrum)


add_executable(utbb_dlist utbb_list.c)
set_target_properties(utbb_dlist PROPERTIES COMPILE_DEFINITIONS "UTBB_DLIST")
target_link_libraries(utbb_dlist oz unittest)
run_test(utbb_dlist)

add_executable(utbb_dlist_instrum utbb_list.c)
set_target_properties(utbb_dlist_instrum PROPERTIES COMPILE_DEFINITIONS "UTBB_DLIST")
target_link_libraries(utbb_dlist_instrum oz_instrum unittest)
run_test(utbb_dlist_instrum)

add_executable(utbb_xlist utbb_list.c)
set_target_properties(utbb_xlist PROPERTIES COMPILE_DEFINITIONS "UTBB_XLIST")
target_link_libraries(utbb_xlist oz unittest)
run_test(utbb_xlist) 

add_executable(utbb_xlist_instrum utbb_list.c)
set_target_properties(utbb_xlist_instrum PROPERTIES COMPILE_DEFINITIONS "UTBB_XLIST")
target_link_libraries(utbb_xlist_instrum oz_instrum unittest)
run_test(utbb_xlist_instrum)

add_executable(utbb_itempool utbb_itempool.c)
target_link_libraries(utbb_itempool oz unittest)
run_test(utbb_itempool)

add_executable(utbb_itempool_instrum utbb_itempool.c)
target_link_libraries(utbb_itempool_instrum oz_instrum unittest)
run_test(utbb_itempool_instrum)

#add_executable(utbb_pt utbb_pt.c)
#run_test(utbb_pt)


add_executable(utbb_task utbb_task.c)
target_link_libraries(utbb_task oz unittest)
run_test(utbb_task)


add_executable(utbb_hash utbb_hash.c)
target_link_libraries(utbb_hash oz unittest)
run_test(utbb_hash) 

add_executable(utbb_hash_instrum utbb_hash.c)
target_link_libraries(utbb_hash_instrum oz_instrum unittest)
run_test(utbb_hash_instrum) 

add_executable(utbb_timer utbb_timer.c)
target_link_libraries(utbb_timer oz unittest)
run_test(utbb_timer) 

add_executable(utbb_timer_instrum utbb_timer.c)
target_link_libraries(utbb_timer_instrum oz_instrum unittest)
run_test(utbb_timer_instrum)

add_custom_target(utbb)
add_dependencies(utbb 
    utbb_hash 
    utbb_ringbuffer
    utbb_buffer 
    utbb_slist
    utbb_dlist
    utbb_xlist
    utbb_itempool
    utbb_task
    utbb_timer
    )
    
add_custom_target(utbb_instrum)
add_dependencies(utbb_instrum 
    utbb_hash_instrum  
    utbb_slist_instrum 
    utbb_dlist_instrum 
    utbb_xlist_instrum 
    utbb_itempool_instrum 
    utbb_timer_instrum
    )

