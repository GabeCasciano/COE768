# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /home/gabe/Programs/Clion/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/gabe/Programs/Clion/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/gabe/Documents/School/COE768/L5

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gabe/Documents/School/COE768/L5/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Server_old.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Server_old.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Server_old.dir/flags.make

CMakeFiles/Server_old.dir/playing_around/server_1.c.o: CMakeFiles/Server_old.dir/flags.make
CMakeFiles/Server_old.dir/playing_around/server_1.c.o: ../playing_around/server_1.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gabe/Documents/School/COE768/L5/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Server_old.dir/playing_around/server_1.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Server_old.dir/playing_around/server_1.c.o   -c /home/gabe/Documents/School/COE768/L5/playing_around/server_1.c

CMakeFiles/Server_old.dir/playing_around/server_1.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Server_old.dir/playing_around/server_1.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/gabe/Documents/School/COE768/L5/playing_around/server_1.c > CMakeFiles/Server_old.dir/playing_around/server_1.c.i

CMakeFiles/Server_old.dir/playing_around/server_1.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Server_old.dir/playing_around/server_1.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/gabe/Documents/School/COE768/L5/playing_around/server_1.c -o CMakeFiles/Server_old.dir/playing_around/server_1.c.s

# Object files for target Server_old
Server_old_OBJECTS = \
"CMakeFiles/Server_old.dir/playing_around/server_1.c.o"

# External object files for target Server_old
Server_old_EXTERNAL_OBJECTS =

Server_old: CMakeFiles/Server_old.dir/playing_around/server_1.c.o
Server_old: CMakeFiles/Server_old.dir/build.make
Server_old: CMakeFiles/Server_old.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/gabe/Documents/School/COE768/L5/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Server_old"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Server_old.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Server_old.dir/build: Server_old

.PHONY : CMakeFiles/Server_old.dir/build

CMakeFiles/Server_old.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Server_old.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Server_old.dir/clean

CMakeFiles/Server_old.dir/depend:
	cd /home/gabe/Documents/School/COE768/L5/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gabe/Documents/School/COE768/L5 /home/gabe/Documents/School/COE768/L5 /home/gabe/Documents/School/COE768/L5/cmake-build-debug /home/gabe/Documents/School/COE768/L5/cmake-build-debug /home/gabe/Documents/School/COE768/L5/cmake-build-debug/CMakeFiles/Server_old.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Server_old.dir/depend
