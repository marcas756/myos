SET (OS_SOURCES 
	timer.c
	process.c
	ptimer.c
	ctimer.c
	etimer.c
	
)

SET (OS_HEADERS
	timestamp.h
	timer.h
	pt.h
	process.h
	ptimer.h
	ctimer.h
	etimer.h
)

add_library(os OBJECT ${OS_SOURCES})