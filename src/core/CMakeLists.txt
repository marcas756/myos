SET (CORE_SOURCES
    task.c 
)

add_library(core OBJECT
    ${CORE_SOURCES}
    )
    
    
add_library(core_instrum OBJECT
    ${CORE_SOURCES}
    )
set_target_properties(core_instrum  PROPERTIES COMPILE_DEFINITIONS "MAESTRA_INSTRUM")


add_library(core_antistatic OBJECT 
    ${CORE_SOURCES}
    )
set_target_properties(core_antistatic  PROPERTIES COMPILE_DEFINITIONS  "ANTISTATIC")
    
    
add_library(core_instrum_antistatic OBJECT
    ${CORE_SOURCES}
    )
set_target_properties(core_instrum_antistatic  PROPERTIES COMPILE_DEFINITIONS "MAESTRA_INSTRUM;ANTISTATIC")