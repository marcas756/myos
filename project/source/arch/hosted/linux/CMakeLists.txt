SET (ARCH_SOURCES 
	timestamp_arch.c
)

SET (ARCH_HEADERS
	critical_arch.h
	timestamp_arch.h
)

add_library(arch OBJECT ${ARCH_SOURCES})
