# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = /usr/local/cmake-3.9.2/bin/cmake

# The command to remove a file.
RM = /usr/local/cmake-3.9.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/travis/build/Alkud/OTUS_HOMEWORK_14

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/travis/build/Alkud/OTUS_HOMEWORK_14

# Include any dependencies generated for this target.
include unit_tests/CMakeFiles/reducer_test.dir/depend.make

# Include the progress variables for this target.
include unit_tests/CMakeFiles/reducer_test.dir/progress.make

# Include the compile flags for this target's objects.
include unit_tests/CMakeFiles/reducer_test.dir/flags.make

unit_tests/CMakeFiles/reducer_test.dir/reducer_test.cpp.o: unit_tests/CMakeFiles/reducer_test.dir/flags.make
unit_tests/CMakeFiles/reducer_test.dir/reducer_test.cpp.o: unit_tests/reducer_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/travis/build/Alkud/OTUS_HOMEWORK_14/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object unit_tests/CMakeFiles/reducer_test.dir/reducer_test.cpp.o"
	cd /home/travis/build/Alkud/OTUS_HOMEWORK_14/unit_tests && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/reducer_test.dir/reducer_test.cpp.o -c /home/travis/build/Alkud/OTUS_HOMEWORK_14/unit_tests/reducer_test.cpp

unit_tests/CMakeFiles/reducer_test.dir/reducer_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/reducer_test.dir/reducer_test.cpp.i"
	cd /home/travis/build/Alkud/OTUS_HOMEWORK_14/unit_tests && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/travis/build/Alkud/OTUS_HOMEWORK_14/unit_tests/reducer_test.cpp > CMakeFiles/reducer_test.dir/reducer_test.cpp.i

unit_tests/CMakeFiles/reducer_test.dir/reducer_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/reducer_test.dir/reducer_test.cpp.s"
	cd /home/travis/build/Alkud/OTUS_HOMEWORK_14/unit_tests && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/travis/build/Alkud/OTUS_HOMEWORK_14/unit_tests/reducer_test.cpp -o CMakeFiles/reducer_test.dir/reducer_test.cpp.s

unit_tests/CMakeFiles/reducer_test.dir/reducer_test.cpp.o.requires:

.PHONY : unit_tests/CMakeFiles/reducer_test.dir/reducer_test.cpp.o.requires

unit_tests/CMakeFiles/reducer_test.dir/reducer_test.cpp.o.provides: unit_tests/CMakeFiles/reducer_test.dir/reducer_test.cpp.o.requires
	$(MAKE) -f unit_tests/CMakeFiles/reducer_test.dir/build.make unit_tests/CMakeFiles/reducer_test.dir/reducer_test.cpp.o.provides.build
.PHONY : unit_tests/CMakeFiles/reducer_test.dir/reducer_test.cpp.o.provides

unit_tests/CMakeFiles/reducer_test.dir/reducer_test.cpp.o.provides.build: unit_tests/CMakeFiles/reducer_test.dir/reducer_test.cpp.o


# Object files for target reducer_test
reducer_test_OBJECTS = \
"CMakeFiles/reducer_test.dir/reducer_test.cpp.o"

# External object files for target reducer_test
reducer_test_EXTERNAL_OBJECTS =

unit_tests/reducer_test: unit_tests/CMakeFiles/reducer_test.dir/reducer_test.cpp.o
unit_tests/reducer_test: unit_tests/CMakeFiles/reducer_test.dir/build.make
unit_tests/reducer_test: mapper_reducer/libmapper_reducer.a
unit_tests/reducer_test: /usr/lib/x86_64-linux-gnu/libboost_unit_test_framework.so
unit_tests/reducer_test: unit_tests/CMakeFiles/reducer_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/travis/build/Alkud/OTUS_HOMEWORK_14/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable reducer_test"
	cd /home/travis/build/Alkud/OTUS_HOMEWORK_14/unit_tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/reducer_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
unit_tests/CMakeFiles/reducer_test.dir/build: unit_tests/reducer_test

.PHONY : unit_tests/CMakeFiles/reducer_test.dir/build

unit_tests/CMakeFiles/reducer_test.dir/requires: unit_tests/CMakeFiles/reducer_test.dir/reducer_test.cpp.o.requires

.PHONY : unit_tests/CMakeFiles/reducer_test.dir/requires

unit_tests/CMakeFiles/reducer_test.dir/clean:
	cd /home/travis/build/Alkud/OTUS_HOMEWORK_14/unit_tests && $(CMAKE_COMMAND) -P CMakeFiles/reducer_test.dir/cmake_clean.cmake
.PHONY : unit_tests/CMakeFiles/reducer_test.dir/clean

unit_tests/CMakeFiles/reducer_test.dir/depend:
	cd /home/travis/build/Alkud/OTUS_HOMEWORK_14 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/travis/build/Alkud/OTUS_HOMEWORK_14 /home/travis/build/Alkud/OTUS_HOMEWORK_14/unit_tests /home/travis/build/Alkud/OTUS_HOMEWORK_14 /home/travis/build/Alkud/OTUS_HOMEWORK_14/unit_tests /home/travis/build/Alkud/OTUS_HOMEWORK_14/unit_tests/CMakeFiles/reducer_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : unit_tests/CMakeFiles/reducer_test.dir/depend
