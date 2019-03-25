cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# Set the compiler to clang++
set(CMAKE_CXX_COMPILER clang++)
# Setting the project to cxx_std_11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)

# Getting all files in the project
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.hpp include/*.hpp)

# Create the project
project(maze_crawler VERSION 0.0.1 LANGUAGES CXX)

# Find ncurses package
find_package(Curses REQUIRED)

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
# Linking the ncurses library
target_link_libraries(${PROJECT_NAME} PRIVATE ${CURSES_LIBRARIES})
