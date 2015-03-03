add_subdirectory(slist)
add_subdirectory(xlist)

add_library(adt 
    dlist.c
    itempool.c
    $<TARGET_OBJECTS:slist>
    $<TARGET_OBJECTS:xlist>
    )
