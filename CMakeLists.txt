cmake_minimum_required(VERSION 2.6)

project(RingBuffer)

if(ENABLE_TRACE)
	message(STATUS "Enable trace")
	add_definitions(-DTRACE)
endif(ENABLE_TRACE)

add_subdirectory(src)
add_subdirectory(lib)
