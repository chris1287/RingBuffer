add_executable(test test.c)

include(FindPkgConfig)
pkg_check_modules(GLIB2 REQUIRED glib-2.0)
include_directories(${GLIB2_INCLUDE_DIRS})
link_directories(${GLIB2_LIBRARY_DIRS})
target_link_libraries(test ${GLIB2_LIBRARIES})


include_directories(${RingBuffer_SOURCE_DIR}/lib)
link_directories(${RingBuffer_BINARY_DIR}/lib)
target_link_libraries(test ringbuffer)
