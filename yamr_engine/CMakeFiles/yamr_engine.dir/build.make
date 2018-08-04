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
include yamr_engine/CMakeFiles/yamr_engine.dir/depend.make

# Include the progress variables for this target.
include yamr_engine/CMakeFiles/yamr_engine.dir/progress.make

# Include the compile flags for this target's objects.
include yamr_engine/CMakeFiles/yamr_engine.dir/flags.make

yamr_engine/CMakeFiles/yamr_engine.dir/yamr_engine.cpp.o: yamr_engine/CMakeFiles/yamr_engine.dir/flags.make
yamr_engine/CMakeFiles/yamr_engine.dir/yamr_engine.cpp.o: yamr_engine/yamr_engine.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/travis/build/Alkud/OTUS_HOMEWORK_14/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object yamr_engine/CMakeFiles/yamr_engine.dir/yamr_engine.cpp.o"
	cd /home/travis/build/Alkud/OTUS_HOMEWORK_14/yamr_engine && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/yamr_engine.dir/yamr_engine.cpp.o -c /home/travis/build/Alkud/OTUS_HOMEWORK_14/yamr_engine/yamr_engine.cpp

yamr_engine/CMakeFiles/yamr_engine.dir/yamr_engine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/yamr_engine.dir/yamr_engine.cpp.i"
	cd /home/travis/build/Alkud/OTUS_HOMEWORK_14/yamr_engine && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/travis/build/Alkud/OTUS_HOMEWORK_14/yamr_engine/yamr_engine.cpp > CMakeFiles/yamr_engine.dir/yamr_engine.cpp.i

yamr_engine/CMakeFiles/yamr_engine.dir/yamr_engine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/yamr_engine.dir/yamr_engine.cpp.s"
	cd /home/travis/build/Alkud/OTUS_HOMEWORK_14/yamr_engine && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/travis/build/Alkud/OTUS_HOMEWORK_14/yamr_engine/yamr_engine.cpp -o CMakeFiles/yamr_engine.dir/yamr_engine.cpp.s

yamr_engine/CMakeFiles/yamr_engine.dir/yamr_engine.cpp.o.requires:

.PHONY : yamr_engine/CMakeFiles/yamr_engine.dir/yamr_engine.cpp.o.requires

yamr_engine/CMakeFiles/yamr_engine.dir/yamr_engine.cpp.o.provides: yamr_engine/CMakeFiles/yamr_engine.dir/yamr_engine.cpp.o.requires
	$(MAKE) -f yamr_engine/CMakeFiles/yamr_engine.dir/build.make yamr_engine/CMakeFiles/yamr_engine.dir/yamr_engine.cpp.o.provides.build
.PHONY : yamr_engine/CMakeFiles/yamr_engine.dir/yamr_engine.cpp.o.provides

yamr_engine/CMakeFiles/yamr_engine.dir/yamr_engine.cpp.o.provides.build: yamr_engine/CMakeFiles/yamr_engine.dir/yamr_engine.cpp.o


# Object files for target yamr_engine
yamr_engine_OBJECTS = \
"CMakeFiles/yamr_engine.dir/yamr_engine.cpp.o"

# External object files for target yamr_engine
yamr_engine_EXTERNAL_OBJECTS =

yamr_engine/libyamr_engine.a: yamr_engine/CMakeFiles/yamr_engine.dir/yamr_engine.cpp.o
yamr_engine/libyamr_engine.a: yamr_engine/CMakeFiles/yamr_engine.dir/build.make
yamr_engine/libyamr_engine.a: yamr_engine/CMakeFiles/yamr_engine.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/travis/build/Alkud/OTUS_HOMEWORK_14/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libyamr_engine.a"
	cd /home/travis/build/Alkud/OTUS_HOMEWORK_14/yamr_engine && $(CMAKE_COMMAND) -P CMakeFiles/yamr_engine.dir/cmake_clean_target.cmake
	cd /home/travis/build/Alkud/OTUS_HOMEWORK_14/yamr_engine && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/yamr_engine.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
yamr_engine/CMakeFiles/yamr_engine.dir/build: yamr_engine/libyamr_engine.a

.PHONY : yamr_engine/CMakeFiles/yamr_engine.dir/build

yamr_engine/CMakeFiles/yamr_engine.dir/requires: yamr_engine/CMakeFiles/yamr_engine.dir/yamr_engine.cpp.o.requires

.PHONY : yamr_engine/CMakeFiles/yamr_engine.dir/requires

yamr_engine/CMakeFiles/yamr_engine.dir/clean:
	cd /home/travis/build/Alkud/OTUS_HOMEWORK_14/yamr_engine && $(CMAKE_COMMAND) -P CMakeFiles/yamr_engine.dir/cmake_clean.cmake
.PHONY : yamr_engine/CMakeFiles/yamr_engine.dir/clean

yamr_engine/CMakeFiles/yamr_engine.dir/depend:
	cd /home/travis/build/Alkud/OTUS_HOMEWORK_14 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/travis/build/Alkud/OTUS_HOMEWORK_14 /home/travis/build/Alkud/OTUS_HOMEWORK_14/yamr_engine /home/travis/build/Alkud/OTUS_HOMEWORK_14 /home/travis/build/Alkud/OTUS_HOMEWORK_14/yamr_engine /home/travis/build/Alkud/OTUS_HOMEWORK_14/yamr_engine/CMakeFiles/yamr_engine.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : yamr_engine/CMakeFiles/yamr_engine.dir/depend

