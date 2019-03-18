cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(maze_crawler VERSION 0.0.1 LANGUAGES CXX)

# Find ncurses package
find_package(Curses REQUIRED)

# Getting all files in the project
file(GLOB SOURCES CONFIGURE_DEPENDS src/*.cpp include/*.hpp)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME}
	PRIVATE
		${CURSES_INCLUDE_DIR}
	PUBLIC
		$<INSTALL_INTERFACE:include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Checking if it is in visual studio for correct errors flags
if (MSVC)
	target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
	target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror -Wpedantic)
endif()
# Adding c++ 11 to the project
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_11)
# Linking the ncurses library
target_link_libraries(${PROJECT_NAME} PRIVATE ${CURSES_LIBRARIES})
