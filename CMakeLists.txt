enable_testing()

cmake_minimum_required(VERSION 3.31.0)
project(statki)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCES
	main.cpp
)

set(HEADERS
	Include
)

add_subdirectory(SDL)

add_subdirectory(Core)
add_subdirectory(Graphics)

add_custom_target(Assets ALL
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${PROJECT_SOURCE_DIR}/Assets
	${PROJECT_BINARY_DIR}/Assets
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} core graphics SDL2 SDL2main pthread)
target_include_directories(${PROJECT_NAME} PRIVATE ${HEADERS})
