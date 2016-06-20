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


add_library(core_exposed OBJECT 
    ${CORE_SOURCES}
    )
set_target_properties(core_exposed  PROPERTIES COMPILE_DEFINITIONS  "UNITTEST_EXPOSE")
    
    
add_library(core_instrum_exposed OBJECT
    ${CORE_SOURCES}
    )
set_target_properties(core_instrum_exposed  PROPERTIES COMPILE_DEFINITIONS "MAESTRA_INSTRUM;UNITTEST_EXPOSE")