# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mpaldhe/DRC/ladder-pipeline-example

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mpaldhe/DRC/ladder-pipeline-example/build

# Include any dependencies generated for this target.
include CMakeFiles/ladderTest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ladderTest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ladderTest.dir/flags.make

CMakeFiles/ladderTest.dir/ladder-pipeline-example.cpp.o: CMakeFiles/ladderTest.dir/flags.make
CMakeFiles/ladderTest.dir/ladder-pipeline-example.cpp.o: ../ladder-pipeline-example.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/mpaldhe/DRC/ladder-pipeline-example/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/ladderTest.dir/ladder-pipeline-example.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ladderTest.dir/ladder-pipeline-example.cpp.o -c /home/mpaldhe/DRC/ladder-pipeline-example/ladder-pipeline-example.cpp

CMakeFiles/ladderTest.dir/ladder-pipeline-example.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ladderTest.dir/ladder-pipeline-example.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/mpaldhe/DRC/ladder-pipeline-example/ladder-pipeline-example.cpp > CMakeFiles/ladderTest.dir/ladder-pipeline-example.cpp.i

CMakeFiles/ladderTest.dir/ladder-pipeline-example.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ladderTest.dir/ladder-pipeline-example.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/mpaldhe/DRC/ladder-pipeline-example/ladder-pipeline-example.cpp -o CMakeFiles/ladderTest.dir/ladder-pipeline-example.cpp.s

CMakeFiles/ladderTest.dir/ladder-pipeline-example.cpp.o.requires:
.PHONY : CMakeFiles/ladderTest.dir/ladder-pipeline-example.cpp.o.requires

CMakeFiles/ladderTest.dir/ladder-pipeline-example.cpp.o.provides: CMakeFiles/ladderTest.dir/ladder-pipeline-example.cpp.o.requires
	$(MAKE) -f CMakeFiles/ladderTest.dir/build.make CMakeFiles/ladderTest.dir/ladder-pipeline-example.cpp.o.provides.build
.PHONY : CMakeFiles/ladderTest.dir/ladder-pipeline-example.cpp.o.provides

CMakeFiles/ladderTest.dir/ladder-pipeline-example.cpp.o.provides.build: CMakeFiles/ladderTest.dir/ladder-pipeline-example.cpp.o

# Object files for target ladderTest
ladderTest_OBJECTS = \
"CMakeFiles/ladderTest.dir/ladder-pipeline-example.cpp.o"

# External object files for target ladderTest
ladderTest_EXTERNAL_OBJECTS =

../ladderTest: CMakeFiles/ladderTest.dir/ladder-pipeline-example.cpp.o
../ladderTest: CMakeFiles/ladderTest.dir/build.make
../ladderTest: CMakeFiles/ladderTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../ladderTest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ladderTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ladderTest.dir/build: ../ladderTest
.PHONY : CMakeFiles/ladderTest.dir/build

CMakeFiles/ladderTest.dir/requires: CMakeFiles/ladderTest.dir/ladder-pipeline-example.cpp.o.requires
.PHONY : CMakeFiles/ladderTest.dir/requires

CMakeFiles/ladderTest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ladderTest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ladderTest.dir/clean

CMakeFiles/ladderTest.dir/depend:
	cd /home/mpaldhe/DRC/ladder-pipeline-example/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mpaldhe/DRC/ladder-pipeline-example /home/mpaldhe/DRC/ladder-pipeline-example /home/mpaldhe/DRC/ladder-pipeline-example/build /home/mpaldhe/DRC/ladder-pipeline-example/build /home/mpaldhe/DRC/ladder-pipeline-example/build/CMakeFiles/ladderTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ladderTest.dir/depend

