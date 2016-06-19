SET (CORE_SOURCES
    task.c 
)

add_library(core 
    ${CORE_SOURCES}
    )
    
    
add_library(core_instrum 
    ${CORE_SOURCES}
    )
set_target_properties(core_instrum  PROPERTIES COMPILE_DEFINITIONS "MAESTRA_INSTRUM")