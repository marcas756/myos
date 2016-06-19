add_executable(utwb_task utwb_task.c)
target_link_libraries(utwb_task oz unittest)
run_test(utwb_task)

add_executable(utwb_task_instrum utwb_task.c)
target_link_libraries(utwb_task_instrum oz_instrum unittest)
run_test(utwb_task_instrum)


