# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/c208/walking_assist/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/c208/walking_assist/build

# Include any dependencies generated for this target.
include emg_process/CMakeFiles/emg_process_node.dir/depend.make

# Include the progress variables for this target.
include emg_process/CMakeFiles/emg_process_node.dir/progress.make

# Include the compile flags for this target's objects.
include emg_process/CMakeFiles/emg_process_node.dir/flags.make

emg_process/CMakeFiles/emg_process_node.dir/src/process.cpp.o: emg_process/CMakeFiles/emg_process_node.dir/flags.make
emg_process/CMakeFiles/emg_process_node.dir/src/process.cpp.o: /home/c208/walking_assist/src/emg_process/src/process.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/c208/walking_assist/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object emg_process/CMakeFiles/emg_process_node.dir/src/process.cpp.o"
	cd /home/c208/walking_assist/build/emg_process && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/emg_process_node.dir/src/process.cpp.o -c /home/c208/walking_assist/src/emg_process/src/process.cpp

emg_process/CMakeFiles/emg_process_node.dir/src/process.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/emg_process_node.dir/src/process.cpp.i"
	cd /home/c208/walking_assist/build/emg_process && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/c208/walking_assist/src/emg_process/src/process.cpp > CMakeFiles/emg_process_node.dir/src/process.cpp.i

emg_process/CMakeFiles/emg_process_node.dir/src/process.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/emg_process_node.dir/src/process.cpp.s"
	cd /home/c208/walking_assist/build/emg_process && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/c208/walking_assist/src/emg_process/src/process.cpp -o CMakeFiles/emg_process_node.dir/src/process.cpp.s

emg_process/CMakeFiles/emg_process_node.dir/lib/iirFilter.c.o: emg_process/CMakeFiles/emg_process_node.dir/flags.make
emg_process/CMakeFiles/emg_process_node.dir/lib/iirFilter.c.o: /home/c208/walking_assist/src/emg_process/lib/iirFilter.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/c208/walking_assist/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object emg_process/CMakeFiles/emg_process_node.dir/lib/iirFilter.c.o"
	cd /home/c208/walking_assist/build/emg_process && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/emg_process_node.dir/lib/iirFilter.c.o   -c /home/c208/walking_assist/src/emg_process/lib/iirFilter.c

emg_process/CMakeFiles/emg_process_node.dir/lib/iirFilter.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/emg_process_node.dir/lib/iirFilter.c.i"
	cd /home/c208/walking_assist/build/emg_process && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/c208/walking_assist/src/emg_process/lib/iirFilter.c > CMakeFiles/emg_process_node.dir/lib/iirFilter.c.i

emg_process/CMakeFiles/emg_process_node.dir/lib/iirFilter.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/emg_process_node.dir/lib/iirFilter.c.s"
	cd /home/c208/walking_assist/build/emg_process && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/c208/walking_assist/src/emg_process/lib/iirFilter.c -o CMakeFiles/emg_process_node.dir/lib/iirFilter.c.s

emg_process/CMakeFiles/emg_process_node.dir/lib/iirFilter_data.c.o: emg_process/CMakeFiles/emg_process_node.dir/flags.make
emg_process/CMakeFiles/emg_process_node.dir/lib/iirFilter_data.c.o: /home/c208/walking_assist/src/emg_process/lib/iirFilter_data.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/c208/walking_assist/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object emg_process/CMakeFiles/emg_process_node.dir/lib/iirFilter_data.c.o"
	cd /home/c208/walking_assist/build/emg_process && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/emg_process_node.dir/lib/iirFilter_data.c.o   -c /home/c208/walking_assist/src/emg_process/lib/iirFilter_data.c

emg_process/CMakeFiles/emg_process_node.dir/lib/iirFilter_data.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/emg_process_node.dir/lib/iirFilter_data.c.i"
	cd /home/c208/walking_assist/build/emg_process && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/c208/walking_assist/src/emg_process/lib/iirFilter_data.c > CMakeFiles/emg_process_node.dir/lib/iirFilter_data.c.i

emg_process/CMakeFiles/emg_process_node.dir/lib/iirFilter_data.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/emg_process_node.dir/lib/iirFilter_data.c.s"
	cd /home/c208/walking_assist/build/emg_process && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/c208/walking_assist/src/emg_process/lib/iirFilter_data.c -o CMakeFiles/emg_process_node.dir/lib/iirFilter_data.c.s

emg_process/CMakeFiles/emg_process_node.dir/lib/iirFilter_initialize.c.o: emg_process/CMakeFiles/emg_process_node.dir/flags.make
emg_process/CMakeFiles/emg_process_node.dir/lib/iirFilter_initialize.c.o: /home/c208/walking_assist/src/emg_process/lib/iirFilter_initialize.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/c208/walking_assist/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object emg_process/CMakeFiles/emg_process_node.dir/lib/iirFilter_initialize.c.o"
	cd /home/c208/walking_assist/build/emg_process && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/emg_process_node.dir/lib/iirFilter_initialize.c.o   -c /home/c208/walking_assist/src/emg_process/lib/iirFilter_initialize.c

emg_process/CMakeFiles/emg_process_node.dir/lib/iirFilter_initialize.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/emg_process_node.dir/lib/iirFilter_initialize.c.i"
	cd /home/c208/walking_assist/build/emg_process && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/c208/walking_assist/src/emg_process/lib/iirFilter_initialize.c > CMakeFiles/emg_process_node.dir/lib/iirFilter_initialize.c.i

emg_process/CMakeFiles/emg_process_node.dir/lib/iirFilter_initialize.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/emg_process_node.dir/lib/iirFilter_initialize.c.s"
	cd /home/c208/walking_assist/build/emg_process && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/c208/walking_assist/src/emg_process/lib/iirFilter_initialize.c -o CMakeFiles/emg_process_node.dir/lib/iirFilter_initialize.c.s

emg_process/CMakeFiles/emg_process_node.dir/lib/iirFilter_terminate.c.o: emg_process/CMakeFiles/emg_process_node.dir/flags.make
emg_process/CMakeFiles/emg_process_node.dir/lib/iirFilter_terminate.c.o: /home/c208/walking_assist/src/emg_process/lib/iirFilter_terminate.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/c208/walking_assist/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object emg_process/CMakeFiles/emg_process_node.dir/lib/iirFilter_terminate.c.o"
	cd /home/c208/walking_assist/build/emg_process && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/emg_process_node.dir/lib/iirFilter_terminate.c.o   -c /home/c208/walking_assist/src/emg_process/lib/iirFilter_terminate.c

emg_process/CMakeFiles/emg_process_node.dir/lib/iirFilter_terminate.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/emg_process_node.dir/lib/iirFilter_terminate.c.i"
	cd /home/c208/walking_assist/build/emg_process && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/c208/walking_assist/src/emg_process/lib/iirFilter_terminate.c > CMakeFiles/emg_process_node.dir/lib/iirFilter_terminate.c.i

emg_process/CMakeFiles/emg_process_node.dir/lib/iirFilter_terminate.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/emg_process_node.dir/lib/iirFilter_terminate.c.s"
	cd /home/c208/walking_assist/build/emg_process && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/c208/walking_assist/src/emg_process/lib/iirFilter_terminate.c -o CMakeFiles/emg_process_node.dir/lib/iirFilter_terminate.c.s

# Object files for target emg_process_node
emg_process_node_OBJECTS = \
"CMakeFiles/emg_process_node.dir/src/process.cpp.o" \
"CMakeFiles/emg_process_node.dir/lib/iirFilter.c.o" \
"CMakeFiles/emg_process_node.dir/lib/iirFilter_data.c.o" \
"CMakeFiles/emg_process_node.dir/lib/iirFilter_initialize.c.o" \
"CMakeFiles/emg_process_node.dir/lib/iirFilter_terminate.c.o"

# External object files for target emg_process_node
emg_process_node_EXTERNAL_OBJECTS =

/home/c208/walking_assist/devel/lib/emg_process/emg_process_node: emg_process/CMakeFiles/emg_process_node.dir/src/process.cpp.o
/home/c208/walking_assist/devel/lib/emg_process/emg_process_node: emg_process/CMakeFiles/emg_process_node.dir/lib/iirFilter.c.o
/home/c208/walking_assist/devel/lib/emg_process/emg_process_node: emg_process/CMakeFiles/emg_process_node.dir/lib/iirFilter_data.c.o
/home/c208/walking_assist/devel/lib/emg_process/emg_process_node: emg_process/CMakeFiles/emg_process_node.dir/lib/iirFilter_initialize.c.o
/home/c208/walking_assist/devel/lib/emg_process/emg_process_node: emg_process/CMakeFiles/emg_process_node.dir/lib/iirFilter_terminate.c.o
/home/c208/walking_assist/devel/lib/emg_process/emg_process_node: emg_process/CMakeFiles/emg_process_node.dir/build.make
/home/c208/walking_assist/devel/lib/emg_process/emg_process_node: /opt/ros/noetic/lib/libroscpp.so
/home/c208/walking_assist/devel/lib/emg_process/emg_process_node: /usr/lib/aarch64-linux-gnu/libpthread.so
/home/c208/walking_assist/devel/lib/emg_process/emg_process_node: /usr/lib/aarch64-linux-gnu/libboost_chrono.so.1.71.0
/home/c208/walking_assist/devel/lib/emg_process/emg_process_node: /usr/lib/aarch64-linux-gnu/libboost_filesystem.so.1.71.0
/home/c208/walking_assist/devel/lib/emg_process/emg_process_node: /opt/ros/noetic/lib/librosconsole.so
/home/c208/walking_assist/devel/lib/emg_process/emg_process_node: /opt/ros/noetic/lib/librosconsole_log4cxx.so
/home/c208/walking_assist/devel/lib/emg_process/emg_process_node: /opt/ros/noetic/lib/librosconsole_backend_interface.so
/home/c208/walking_assist/devel/lib/emg_process/emg_process_node: /usr/lib/aarch64-linux-gnu/liblog4cxx.so
/home/c208/walking_assist/devel/lib/emg_process/emg_process_node: /usr/lib/aarch64-linux-gnu/libboost_regex.so.1.71.0
/home/c208/walking_assist/devel/lib/emg_process/emg_process_node: /opt/ros/noetic/lib/libxmlrpcpp.so
/home/c208/walking_assist/devel/lib/emg_process/emg_process_node: /opt/ros/noetic/lib/libroscpp_serialization.so
/home/c208/walking_assist/devel/lib/emg_process/emg_process_node: /opt/ros/noetic/lib/librostime.so
/home/c208/walking_assist/devel/lib/emg_process/emg_process_node: /usr/lib/aarch64-linux-gnu/libboost_date_time.so.1.71.0
/home/c208/walking_assist/devel/lib/emg_process/emg_process_node: /opt/ros/noetic/lib/libcpp_common.so
/home/c208/walking_assist/devel/lib/emg_process/emg_process_node: /usr/lib/aarch64-linux-gnu/libboost_system.so.1.71.0
/home/c208/walking_assist/devel/lib/emg_process/emg_process_node: /usr/lib/aarch64-linux-gnu/libboost_thread.so.1.71.0
/home/c208/walking_assist/devel/lib/emg_process/emg_process_node: /usr/lib/aarch64-linux-gnu/libconsole_bridge.so.0.4
/home/c208/walking_assist/devel/lib/emg_process/emg_process_node: emg_process/CMakeFiles/emg_process_node.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/c208/walking_assist/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable /home/c208/walking_assist/devel/lib/emg_process/emg_process_node"
	cd /home/c208/walking_assist/build/emg_process && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/emg_process_node.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
emg_process/CMakeFiles/emg_process_node.dir/build: /home/c208/walking_assist/devel/lib/emg_process/emg_process_node

.PHONY : emg_process/CMakeFiles/emg_process_node.dir/build

emg_process/CMakeFiles/emg_process_node.dir/clean:
	cd /home/c208/walking_assist/build/emg_process && $(CMAKE_COMMAND) -P CMakeFiles/emg_process_node.dir/cmake_clean.cmake
.PHONY : emg_process/CMakeFiles/emg_process_node.dir/clean

emg_process/CMakeFiles/emg_process_node.dir/depend:
	cd /home/c208/walking_assist/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/c208/walking_assist/src /home/c208/walking_assist/src/emg_process /home/c208/walking_assist/build /home/c208/walking_assist/build/emg_process /home/c208/walking_assist/build/emg_process/CMakeFiles/emg_process_node.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : emg_process/CMakeFiles/emg_process_node.dir/depend

