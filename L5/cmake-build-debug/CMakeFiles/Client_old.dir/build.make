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
include CMakeFiles/Client_old.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Client_old.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Client_old.dir/flags.make

CMakeFiles/Client_old.dir/playing_around/client_1.c.o: CMakeFiles/Client_old.dir/flags.make
CMakeFiles/Client_old.dir/playing_around/client_1.c.o: ../playing_around/client_1.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gabe/Documents/School/COE768/L5/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Client_old.dir/playing_around/client_1.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Client_old.dir/playing_around/client_1.c.o   -c /home/gabe/Documents/School/COE768/L5/playing_around/client_1.c

CMakeFiles/Client_old.dir/playing_around/client_1.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Client_old.dir/playing_around/client_1.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/gabe/Documents/School/COE768/L5/playing_around/client_1.c > CMakeFiles/Client_old.dir/playing_around/client_1.c.i

CMakeFiles/Client_old.dir/playing_around/client_1.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Client_old.dir/playing_around/client_1.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/gabe/Documents/School/COE768/L5/playing_around/client_1.c -o CMakeFiles/Client_old.dir/playing_around/client_1.c.s

# Object files for target Client_old
Client_old_OBJECTS = \
"CMakeFiles/Client_old.dir/playing_around/client_1.c.o"

# External object files for target Client_old
Client_old_EXTERNAL_OBJECTS =

Client_old: CMakeFiles/Client_old.dir/playing_around/client_1.c.o
Client_old: CMakeFiles/Client_old.dir/build.make
Client_old: CMakeFiles/Client_old.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/gabe/Documents/School/COE768/L5/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Client_old"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Client_old.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Client_old.dir/build: Client_old

.PHONY : CMakeFiles/Client_old.dir/build

CMakeFiles/Client_old.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Client_old.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Client_old.dir/clean

CMakeFiles/Client_old.dir/depend:
	cd /home/gabe/Documents/School/COE768/L5/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gabe/Documents/School/COE768/L5 /home/gabe/Documents/School/COE768/L5 /home/gabe/Documents/School/COE768/L5/cmake-build-debug /home/gabe/Documents/School/COE768/L5/cmake-build-debug /home/gabe/Documents/School/COE768/L5/cmake-build-debug/CMakeFiles/Client_old.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Client_old.dir/depend

