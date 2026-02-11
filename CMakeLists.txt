cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project(mps)

file(GLOB INCLUDES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} include/*.h)
file(GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*.c src/*.cpp)

add_library(
	${PROJECT_NAME}
	SHARED
	${SOURCES}
	${INCLUDES}
)
target_include_directories(${PROJECT_NAME} PUBLIC include)
