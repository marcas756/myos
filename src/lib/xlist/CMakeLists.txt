SET (XLIST_SOURCES 
    xlist_erase.c
    xlist_find.c
    xlist_insert_after.c
    xlist_insert_before.c
    xlist_next.c
    xlist_pop_back.c
    xlist_pop_front.c
    xlist_prev.c
    xlist_push_back.c
    xlist_push_front.c
    xlist_remove.c
    xlist_reverse.c
    xlist_size.c
    xlist_sort.c
    xlist_unique.c
)


add_library(xlist OBJECT ${XLIST_SOURCES})

add_library(xlist_instrum OBJECT ${XLIST_SOURCES})
set_target_properties(xlist_instrum  PROPERTIES COMPILE_DEFINITIONS "MAESTRA_INSTRUM")