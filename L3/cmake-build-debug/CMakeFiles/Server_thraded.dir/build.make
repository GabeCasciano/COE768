# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /home/gabriel/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/192.7142.39/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/gabriel/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/192.7142.39/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/gabriel/Documents/COE768/L3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gabriel/Documents/COE768/L3/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Server_thraded.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Server_thraded.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Server_thraded.dir/flags.make

CMakeFiles/Server_thraded.dir/most_of_c_server/server.c.o: CMakeFiles/Server_thraded.dir/flags.make
CMakeFiles/Server_thraded.dir/most_of_c_server/server.c.o: ../most_of_c_server/server.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gabriel/Documents/COE768/L3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Server_thraded.dir/most_of_c_server/server.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Server_thraded.dir/most_of_c_server/server.c.o   -c /home/gabriel/Documents/COE768/L3/most_of_c_server/server.c

CMakeFiles/Server_thraded.dir/most_of_c_server/server.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Server_thraded.dir/most_of_c_server/server.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/gabriel/Documents/COE768/L3/most_of_c_server/server.c > CMakeFiles/Server_thraded.dir/most_of_c_server/server.c.i

CMakeFiles/Server_thraded.dir/most_of_c_server/server.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Server_thraded.dir/most_of_c_server/server.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/gabriel/Documents/COE768/L3/most_of_c_server/server.c -o CMakeFiles/Server_thraded.dir/most_of_c_server/server.c.s

# Object files for target Server_thraded
Server_thraded_OBJECTS = \
"CMakeFiles/Server_thraded.dir/most_of_c_server/server.c.o"

# External object files for target Server_thraded
Server_thraded_EXTERNAL_OBJECTS =

Server_thraded: CMakeFiles/Server_thraded.dir/most_of_c_server/server.c.o
Server_thraded: CMakeFiles/Server_thraded.dir/build.make
Server_thraded: CMakeFiles/Server_thraded.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/gabriel/Documents/COE768/L3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Server_thraded"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Server_thraded.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Server_thraded.dir/build: Server_thraded

.PHONY : CMakeFiles/Server_thraded.dir/build

CMakeFiles/Server_thraded.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Server_thraded.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Server_thraded.dir/clean

CMakeFiles/Server_thraded.dir/depend:
	cd /home/gabriel/Documents/COE768/L3/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gabriel/Documents/COE768/L3 /home/gabriel/Documents/COE768/L3 /home/gabriel/Documents/COE768/L3/cmake-build-debug /home/gabriel/Documents/COE768/L3/cmake-build-debug /home/gabriel/Documents/COE768/L3/cmake-build-debug/CMakeFiles/Server_thraded.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Server_thraded.dir/depend

