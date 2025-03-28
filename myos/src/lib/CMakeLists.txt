SET (LIB_SOURCES 
	slist.c
	dlist.c	
	itempool.c
	crc16.c
	hash.c
)

SET (LIB_HEADERS
	slist.h
	dlist.h
	utils.h
	bitarray.h
	bits.h
	itempool.h
	binary.h
	buffer.h
	crc16.h
	hash.h
)

add_library(lib OBJECT ${LIB_SOURCES})
