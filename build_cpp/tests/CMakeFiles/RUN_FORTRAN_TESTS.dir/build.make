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

# Utility rule file for RUN_FORTRAN_TESTS.

# Include any custom commands dependencies for this target.
include tests/CMakeFiles/RUN_FORTRAN_TESTS.dir/compiler_depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/RUN_FORTRAN_TESTS.dir/progress.make

tests/CMakeFiles/RUN_FORTRAN_TESTS:
	cd /home/akiel/Desktop/trunk/github/OSS/openGPMP/build_cpp/tests && /usr/bin/cmake -E cmake_echo_color --green [==========]
	cd /home/akiel/Desktop/trunk/github/OSS/openGPMP/build_cpp/tests && /usr/bin/cmake -E cmake_echo_color --magenta --bold [Running\ Fortran\ Unit\ Tests]
	cd /home/akiel/Desktop/trunk/github/OSS/openGPMP/build_cpp/tests && ./test_openGPMP_fortran

RUN_FORTRAN_TESTS: tests/CMakeFiles/RUN_FORTRAN_TESTS
RUN_FORTRAN_TESTS: tests/CMakeFiles/RUN_FORTRAN_TESTS.dir/build.make
.PHONY : RUN_FORTRAN_TESTS

# Rule to build all files generated by this target.
tests/CMakeFiles/RUN_FORTRAN_TESTS.dir/build: RUN_FORTRAN_TESTS
.PHONY : tests/CMakeFiles/RUN_FORTRAN_TESTS.dir/build

tests/CMakeFiles/RUN_FORTRAN_TESTS.dir/clean:
	cd /home/akiel/Desktop/trunk/github/OSS/openGPMP/build_cpp/tests && $(CMAKE_COMMAND) -P CMakeFiles/RUN_FORTRAN_TESTS.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/RUN_FORTRAN_TESTS.dir/clean

tests/CMakeFiles/RUN_FORTRAN_TESTS.dir/depend:
	cd /home/akiel/Desktop/trunk/github/OSS/openGPMP/build_cpp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/akiel/Desktop/trunk/github/OSS/openGPMP /home/akiel/Desktop/trunk/github/OSS/openGPMP/tests /home/akiel/Desktop/trunk/github/OSS/openGPMP/build_cpp /home/akiel/Desktop/trunk/github/OSS/openGPMP/build_cpp/tests /home/akiel/Desktop/trunk/github/OSS/openGPMP/build_cpp/tests/CMakeFiles/RUN_FORTRAN_TESTS.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : tests/CMakeFiles/RUN_FORTRAN_TESTS.dir/depend

