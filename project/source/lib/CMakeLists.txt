SET (LIB_SOURCES 
	slist.c
	dlist.c
	#itempool.c
	#hash_sdbm.c
	
)

SET (LIB_HEADERS
	slist.h
	dlist.h
	itempool.h
	buffer.h
	ringbuffer.h
	binary.h
	bits.h
	bitarray.h
	hash_sdbm.h
)

add_library(lib OBJECT ${LIB_SOURCES})
