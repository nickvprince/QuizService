# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /QuizSharedDocker

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /QuizSharedDocker/Build

# Include any dependencies generated for this target.
include CMakeFiles/Quiz_webserver_dev.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Quiz_webserver_dev.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Quiz_webserver_dev.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Quiz_webserver_dev.dir/flags.make

CMakeFiles/Quiz_webserver_dev.dir/main.cpp.o: CMakeFiles/Quiz_webserver_dev.dir/flags.make
CMakeFiles/Quiz_webserver_dev.dir/main.cpp.o: ../main.cpp
CMakeFiles/Quiz_webserver_dev.dir/main.cpp.o: CMakeFiles/Quiz_webserver_dev.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/QuizSharedDocker/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Quiz_webserver_dev.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Quiz_webserver_dev.dir/main.cpp.o -MF CMakeFiles/Quiz_webserver_dev.dir/main.cpp.o.d -o CMakeFiles/Quiz_webserver_dev.dir/main.cpp.o -c /QuizSharedDocker/main.cpp

CMakeFiles/Quiz_webserver_dev.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Quiz_webserver_dev.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /QuizSharedDocker/main.cpp > CMakeFiles/Quiz_webserver_dev.dir/main.cpp.i

CMakeFiles/Quiz_webserver_dev.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Quiz_webserver_dev.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /QuizSharedDocker/main.cpp -o CMakeFiles/Quiz_webserver_dev.dir/main.cpp.s

# Object files for target Quiz_webserver_dev
Quiz_webserver_dev_OBJECTS = \
"CMakeFiles/Quiz_webserver_dev.dir/main.cpp.o"

# External object files for target Quiz_webserver_dev
Quiz_webserver_dev_EXTERNAL_OBJECTS =

Quiz_webserver_dev: CMakeFiles/Quiz_webserver_dev.dir/main.cpp.o
Quiz_webserver_dev: CMakeFiles/Quiz_webserver_dev.dir/build.make
Quiz_webserver_dev: /usr/lib/x86_64-linux-gnu/libboost_system.so.1.74.0
Quiz_webserver_dev: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so.1.74.0
Quiz_webserver_dev: CMakeFiles/Quiz_webserver_dev.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/QuizSharedDocker/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Quiz_webserver_dev"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Quiz_webserver_dev.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Quiz_webserver_dev.dir/build: Quiz_webserver_dev
.PHONY : CMakeFiles/Quiz_webserver_dev.dir/build

CMakeFiles/Quiz_webserver_dev.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Quiz_webserver_dev.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Quiz_webserver_dev.dir/clean

CMakeFiles/Quiz_webserver_dev.dir/depend:
	cd /QuizSharedDocker/Build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /QuizSharedDocker /QuizSharedDocker /QuizSharedDocker/Build /QuizSharedDocker/Build /QuizSharedDocker/Build/CMakeFiles/Quiz_webserver_dev.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Quiz_webserver_dev.dir/depend

