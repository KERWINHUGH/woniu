# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/hugh/woniu/250519/person/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hugh/woniu/250519/person/build

# Include any dependencies generated for this target.
include CMakeFiles/person.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/person.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/person.dir/flags.make

CMakeFiles/person.dir/StuInfoManager.cpp.o: CMakeFiles/person.dir/flags.make
CMakeFiles/person.dir/StuInfoManager.cpp.o: /home/hugh/woniu/250519/person/src/StuInfoManager.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hugh/woniu/250519/person/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/person.dir/StuInfoManager.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/person.dir/StuInfoManager.cpp.o -c /home/hugh/woniu/250519/person/src/StuInfoManager.cpp

CMakeFiles/person.dir/StuInfoManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/person.dir/StuInfoManager.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hugh/woniu/250519/person/src/StuInfoManager.cpp > CMakeFiles/person.dir/StuInfoManager.cpp.i

CMakeFiles/person.dir/StuInfoManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/person.dir/StuInfoManager.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hugh/woniu/250519/person/src/StuInfoManager.cpp -o CMakeFiles/person.dir/StuInfoManager.cpp.s

CMakeFiles/person.dir/StuInfoManager.cpp.o.requires:

.PHONY : CMakeFiles/person.dir/StuInfoManager.cpp.o.requires

CMakeFiles/person.dir/StuInfoManager.cpp.o.provides: CMakeFiles/person.dir/StuInfoManager.cpp.o.requires
	$(MAKE) -f CMakeFiles/person.dir/build.make CMakeFiles/person.dir/StuInfoManager.cpp.o.provides.build
.PHONY : CMakeFiles/person.dir/StuInfoManager.cpp.o.provides

CMakeFiles/person.dir/StuInfoManager.cpp.o.provides.build: CMakeFiles/person.dir/StuInfoManager.cpp.o


CMakeFiles/person.dir/main.cpp.o: CMakeFiles/person.dir/flags.make
CMakeFiles/person.dir/main.cpp.o: /home/hugh/woniu/250519/person/src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hugh/woniu/250519/person/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/person.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/person.dir/main.cpp.o -c /home/hugh/woniu/250519/person/src/main.cpp

CMakeFiles/person.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/person.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hugh/woniu/250519/person/src/main.cpp > CMakeFiles/person.dir/main.cpp.i

CMakeFiles/person.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/person.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hugh/woniu/250519/person/src/main.cpp -o CMakeFiles/person.dir/main.cpp.s

CMakeFiles/person.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/person.dir/main.cpp.o.requires

CMakeFiles/person.dir/main.cpp.o.provides: CMakeFiles/person.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/person.dir/build.make CMakeFiles/person.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/person.dir/main.cpp.o.provides

CMakeFiles/person.dir/main.cpp.o.provides.build: CMakeFiles/person.dir/main.cpp.o


# Object files for target person
person_OBJECTS = \
"CMakeFiles/person.dir/StuInfoManager.cpp.o" \
"CMakeFiles/person.dir/main.cpp.o"

# External object files for target person
person_EXTERNAL_OBJECTS =

bin/person: CMakeFiles/person.dir/StuInfoManager.cpp.o
bin/person: CMakeFiles/person.dir/main.cpp.o
bin/person: CMakeFiles/person.dir/build.make
bin/person: CMakeFiles/person.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hugh/woniu/250519/person/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable bin/person"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/person.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/person.dir/build: bin/person

.PHONY : CMakeFiles/person.dir/build

CMakeFiles/person.dir/requires: CMakeFiles/person.dir/StuInfoManager.cpp.o.requires
CMakeFiles/person.dir/requires: CMakeFiles/person.dir/main.cpp.o.requires

.PHONY : CMakeFiles/person.dir/requires

CMakeFiles/person.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/person.dir/cmake_clean.cmake
.PHONY : CMakeFiles/person.dir/clean

CMakeFiles/person.dir/depend:
	cd /home/hugh/woniu/250519/person/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hugh/woniu/250519/person/src /home/hugh/woniu/250519/person/src /home/hugh/woniu/250519/person/build /home/hugh/woniu/250519/person/build /home/hugh/woniu/250519/person/build/CMakeFiles/person.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/person.dir/depend

