# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Applications/CMake.app/Contents/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/liamhurt/code/CC-CppCourse/FileManipulator

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/liamhurt/code/CC-CppCourse/FileManipulator/build

# Include any dependencies generated for this target.
include CMakeFiles/file_manipulator.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/file_manipulator.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/file_manipulator.dir/flags.make

CMakeFiles/file_manipulator.dir/src/main.cpp.o: CMakeFiles/file_manipulator.dir/flags.make
CMakeFiles/file_manipulator.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/liamhurt/code/CC-CppCourse/FileManipulator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/file_manipulator.dir/src/main.cpp.o"
	/usr/bin/clang++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/file_manipulator.dir/src/main.cpp.o -c /Users/liamhurt/code/CC-CppCourse/FileManipulator/src/main.cpp

CMakeFiles/file_manipulator.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/file_manipulator.dir/src/main.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/liamhurt/code/CC-CppCourse/FileManipulator/src/main.cpp > CMakeFiles/file_manipulator.dir/src/main.cpp.i

CMakeFiles/file_manipulator.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/file_manipulator.dir/src/main.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/liamhurt/code/CC-CppCourse/FileManipulator/src/main.cpp -o CMakeFiles/file_manipulator.dir/src/main.cpp.s

# Object files for target file_manipulator
file_manipulator_OBJECTS = \
"CMakeFiles/file_manipulator.dir/src/main.cpp.o"

# External object files for target file_manipulator
file_manipulator_EXTERNAL_OBJECTS =

file_manipulator: CMakeFiles/file_manipulator.dir/src/main.cpp.o
file_manipulator: CMakeFiles/file_manipulator.dir/build.make
file_manipulator: CMakeFiles/file_manipulator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/liamhurt/code/CC-CppCourse/FileManipulator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable file_manipulator"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/file_manipulator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/file_manipulator.dir/build: file_manipulator

.PHONY : CMakeFiles/file_manipulator.dir/build

CMakeFiles/file_manipulator.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/file_manipulator.dir/cmake_clean.cmake
.PHONY : CMakeFiles/file_manipulator.dir/clean

CMakeFiles/file_manipulator.dir/depend:
	cd /Users/liamhurt/code/CC-CppCourse/FileManipulator/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/liamhurt/code/CC-CppCourse/FileManipulator /Users/liamhurt/code/CC-CppCourse/FileManipulator /Users/liamhurt/code/CC-CppCourse/FileManipulator/build /Users/liamhurt/code/CC-CppCourse/FileManipulator/build /Users/liamhurt/code/CC-CppCourse/FileManipulator/build/CMakeFiles/file_manipulator.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/file_manipulator.dir/depend

