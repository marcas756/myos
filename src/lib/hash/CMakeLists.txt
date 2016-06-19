SET (HASH_SOURCES 
    hash_sdbm.c
)


add_library(hash OBJECT ${HASH_SOURCES})

add_library(hash_instrum OBJECT ${HASH_SOURCES})
set_target_properties(hash_instrum  PROPERTIES COMPILE_DEFINITIONS "MAESTRA_INSTRUM")