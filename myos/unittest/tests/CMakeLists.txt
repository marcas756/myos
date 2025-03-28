include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(myunit_slist myunit_list.c)
target_compile_definitions(myunit_slist PRIVATE UNITTEST_LIST_TYPE=UNITTEST_LIST_TYPE_SLIST)
target_link_libraries(myunit_slist myos myunit)

add_executable(myunit_dlist myunit_list.c)
target_compile_definitions(myunit_dlist PRIVATE UNITTEST_LIST_TYPE=UNITTEST_LIST_TYPE_DLIST)
target_link_libraries(myunit_dlist myos myunit)

add_executable(myunit_bitarray myunit_bitarray.c)
target_link_libraries(myunit_bitarray myos myunit)

add_executable(myunit_bits myunit_bits.c)
target_link_libraries(myunit_bits myos myunit)

add_executable(myunit_binary myunit_binary.c)
target_link_libraries(myunit_binary myos myunit)

add_executable(myunit_itempool myunit_itempool.c)
target_link_libraries(myunit_itempool myos myunit)

add_executable(myunit_buffer myunit_buffer.c)
target_link_libraries(myunit_buffer myos myunit)

add_executable(myunit_ringbuffer myunit_ringbuffer.c)
target_link_libraries(myunit_ringbuffer myos myunit)

add_executable(myunit_crc16 myunit_crc16.c)
target_link_libraries(myunit_crc16 myos myunit)

add_executable(myunit_hash myunit_hash.c)
target_link_libraries(myunit_hash myos myunit)