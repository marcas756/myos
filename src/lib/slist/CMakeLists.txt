SET (SLIST_SOURCES 
    slist_end.c
    slist_erase.c
    slist_find.c
    slist_insert_after.c
    slist_insert_before.c
    slist_pop_back.c
    slist_prev.c
    slist_push_back.c
    slist_remove.c
    slist_reverse.c
    slist_size.c
    slist_sort.c
    slist_swap.c
    slist_unique.c
)


add_library(slist OBJECT ${SLIST_SOURCES} )

add_library(slist_instrum OBJECT ${SLIST_SOURCES} )
set_target_properties(slist_instrum  PROPERTIES COMPILE_DEFINITIONS "MAESTRA_INSTRUM")

add_library(slist_exposed OBJECT ${SLIST_SOURCES} )
set_target_properties(slist_exposed  PROPERTIES COMPILE_DEFINITIONS "UNITTEST_EXPOSE")

add_library(slist_instrum_exposed OBJECT ${SLIST_SOURCES} )
set_target_properties(slist_instrum_exposed  PROPERTIES COMPILE_DEFINITIONS "MAESTRA_INSTRUM;UNITTEST_EXPOSE")