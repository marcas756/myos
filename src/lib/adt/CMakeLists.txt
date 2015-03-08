add_subdirectory(slist)
add_subdirectory(xlist)
add_subdirectory(dlist)

add_library(adt 
    itempool.c
    $<TARGET_OBJECTS:slist>
    $<TARGET_OBJECTS:xlist>
    $<TARGET_OBJECTS:dlist>
    )
