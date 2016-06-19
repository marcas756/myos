SET (DLIST_SOURCES 
    dlist_erase.c
    dlist_find.c
    dlist_insert_after.c
    dlist_insert_before.c
    dlist_pop_back.c
    dlist_pop_front.c
    dlist_push_back.c
    dlist_push_front.c
    dlist_remove.c
    dlist_reverse.c
    dlist_size.c
    dlist_sort.c
    dlist_swap.c
    dlist_unique.c
)


add_library(dlist OBJECT ${DLIST_SOURCES})

add_library(dlist_instrum OBJECT ${DLIST_SOURCES})
set_target_properties(dlist_instrum  PROPERTIES COMPILE_DEFINITIONS "MAESTRA_INSTRUM")