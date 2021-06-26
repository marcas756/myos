SET (OS_SOURCES 
	timer.c
	process.c
	ptimer.c
	
)

SET (OS_HEADERS
	timestamp.h
	timer.h
	pt.h
	process.h
	ptimer.h
)

add_library(os OBJECT ${OS_SOURCES})