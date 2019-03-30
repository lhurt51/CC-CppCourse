cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# Set the compiler to clang++
set(CMAKE_CXX_COMPILER clang++)
# Setting the project to cxx_std_11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)

# Getting all files in the project
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.hpp include/*.hpp)

# Create the project
project(slot_machine LANGUAGES CXX)

# The version number.
set (slot_machine_VERSION_MAJOR 0)
set (slot_machine_VERSION_MINOR 1)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
"${PROJECT_SOURCE_DIR}/GameConfig.h.in"
"${PROJECT_BINARY_DIR}/GameConfig.h"
)

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}")

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

# add the install targets
install (TARGETS ${PROJECT_NAME} DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/GameConfig.h" DESTINATION include)

# build a CPack driven installer package
include (InstallRequiredSystemLibraries)
set (CPACK_RESOURCE_FILE_LICENSE
     "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set (CPACK_PACKAGE_VERSION_MAJOR "${slot_machine_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${slot_machine_VERSION_MINOR}")
include (CPack)
