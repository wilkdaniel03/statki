set(SOURCES
	Window.cpp
)
add_library(core ${SOURCES})
target_include_directories(core PRIVATE ../Include)
