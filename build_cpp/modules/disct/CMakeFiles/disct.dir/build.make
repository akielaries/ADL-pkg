# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_SOURCE_DIR = /home/akiel/Desktop/trunk/github/OSS/openGPMP

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/akiel/Desktop/trunk/github/OSS/openGPMP/build_cpp

# Include any dependencies generated for this target.
include modules/disct/CMakeFiles/disct.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include modules/disct/CMakeFiles/disct.dir/compiler_depend.make

# Include the progress variables for this target.
include modules/disct/CMakeFiles/disct.dir/progress.make

# Include the compile flags for this target's objects.
include modules/disct/CMakeFiles/disct.dir/flags.make

modules/disct/CMakeFiles/disct.dir/graphs.cpp.o: modules/disct/CMakeFiles/disct.dir/flags.make
modules/disct/CMakeFiles/disct.dir/graphs.cpp.o: /home/akiel/Desktop/trunk/github/OSS/openGPMP/modules/disct/graphs.cpp
modules/disct/CMakeFiles/disct.dir/graphs.cpp.o: modules/disct/CMakeFiles/disct.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/akiel/Desktop/trunk/github/OSS/openGPMP/build_cpp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object modules/disct/CMakeFiles/disct.dir/graphs.cpp.o"
	cd /home/akiel/Desktop/trunk/github/OSS/openGPMP/build_cpp/modules/disct && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT modules/disct/CMakeFiles/disct.dir/graphs.cpp.o -MF CMakeFiles/disct.dir/graphs.cpp.o.d -o CMakeFiles/disct.dir/graphs.cpp.o -c /home/akiel/Desktop/trunk/github/OSS/openGPMP/modules/disct/graphs.cpp

modules/disct/CMakeFiles/disct.dir/graphs.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/disct.dir/graphs.cpp.i"
	cd /home/akiel/Desktop/trunk/github/OSS/openGPMP/build_cpp/modules/disct && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/akiel/Desktop/trunk/github/OSS/openGPMP/modules/disct/graphs.cpp > CMakeFiles/disct.dir/graphs.cpp.i

modules/disct/CMakeFiles/disct.dir/graphs.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/disct.dir/graphs.cpp.s"
	cd /home/akiel/Desktop/trunk/github/OSS/openGPMP/build_cpp/modules/disct && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/akiel/Desktop/trunk/github/OSS/openGPMP/modules/disct/graphs.cpp -o CMakeFiles/disct.dir/graphs.cpp.s

disct: modules/disct/CMakeFiles/disct.dir/graphs.cpp.o
disct: modules/disct/CMakeFiles/disct.dir/build.make
.PHONY : disct

# Rule to build all files generated by this target.
modules/disct/CMakeFiles/disct.dir/build: disct
.PHONY : modules/disct/CMakeFiles/disct.dir/build

modules/disct/CMakeFiles/disct.dir/clean:
	cd /home/akiel/Desktop/trunk/github/OSS/openGPMP/build_cpp/modules/disct && $(CMAKE_COMMAND) -P CMakeFiles/disct.dir/cmake_clean.cmake
.PHONY : modules/disct/CMakeFiles/disct.dir/clean

modules/disct/CMakeFiles/disct.dir/depend:
	cd /home/akiel/Desktop/trunk/github/OSS/openGPMP/build_cpp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/akiel/Desktop/trunk/github/OSS/openGPMP /home/akiel/Desktop/trunk/github/OSS/openGPMP/modules/disct /home/akiel/Desktop/trunk/github/OSS/openGPMP/build_cpp /home/akiel/Desktop/trunk/github/OSS/openGPMP/build_cpp/modules/disct /home/akiel/Desktop/trunk/github/OSS/openGPMP/build_cpp/modules/disct/CMakeFiles/disct.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : modules/disct/CMakeFiles/disct.dir/depend

