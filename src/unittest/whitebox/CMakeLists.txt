add_executable(utwb_task utwb_task.c)
target_link_libraries(utwb_task oz_exposed unittest)
run_test(utwb_task)

add_executable(utwb_task_instrum utwb_task.c)
target_link_libraries(utwb_task_instrum oz_instrum_exposed unittest)
run_test(utwb_task_instrum)


