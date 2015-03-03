add_subdirectory(slist)

add_library(adt 
    dlist.c
    xlist.c
    itempool.c
    $<TARGET_OBJECTS:slist>
    )
