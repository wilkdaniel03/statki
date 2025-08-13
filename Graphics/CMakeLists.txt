set(SOURCES
	Point.cpp
)
add_library(graphics ${SOURCES})
target_include_directories(graphics PRIVATE ../Include)
