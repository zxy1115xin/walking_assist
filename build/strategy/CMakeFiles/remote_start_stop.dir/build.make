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
include strategy/CMakeFiles/remote_start_stop.dir/depend.make

# Include the progress variables for this target.
include strategy/CMakeFiles/remote_start_stop.dir/progress.make

# Include the compile flags for this target's objects.
include strategy/CMakeFiles/remote_start_stop.dir/flags.make

strategy/CMakeFiles/remote_start_stop.dir/src/remote_start_stop.cpp.o: strategy/CMakeFiles/remote_start_stop.dir/flags.make
strategy/CMakeFiles/remote_start_stop.dir/src/remote_start_stop.cpp.o: /home/c208/walking_assist/src/strategy/src/remote_start_stop.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/c208/walking_assist/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object strategy/CMakeFiles/remote_start_stop.dir/src/remote_start_stop.cpp.o"
	cd /home/c208/walking_assist/build/strategy && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/remote_start_stop.dir/src/remote_start_stop.cpp.o -c /home/c208/walking_assist/src/strategy/src/remote_start_stop.cpp

strategy/CMakeFiles/remote_start_stop.dir/src/remote_start_stop.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/remote_start_stop.dir/src/remote_start_stop.cpp.i"
	cd /home/c208/walking_assist/build/strategy && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/c208/walking_assist/src/strategy/src/remote_start_stop.cpp > CMakeFiles/remote_start_stop.dir/src/remote_start_stop.cpp.i

strategy/CMakeFiles/remote_start_stop.dir/src/remote_start_stop.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/remote_start_stop.dir/src/remote_start_stop.cpp.s"
	cd /home/c208/walking_assist/build/strategy && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/c208/walking_assist/src/strategy/src/remote_start_stop.cpp -o CMakeFiles/remote_start_stop.dir/src/remote_start_stop.cpp.s

# Object files for target remote_start_stop
remote_start_stop_OBJECTS = \
"CMakeFiles/remote_start_stop.dir/src/remote_start_stop.cpp.o"

# External object files for target remote_start_stop
remote_start_stop_EXTERNAL_OBJECTS =

/home/c208/walking_assist/devel/lib/strategy/remote_start_stop: strategy/CMakeFiles/remote_start_stop.dir/src/remote_start_stop.cpp.o
/home/c208/walking_assist/devel/lib/strategy/remote_start_stop: strategy/CMakeFiles/remote_start_stop.dir/build.make
/home/c208/walking_assist/devel/lib/strategy/remote_start_stop: /opt/ros/noetic/lib/libdynamic_reconfigure_config_init_mutex.so
/home/c208/walking_assist/devel/lib/strategy/remote_start_stop: /opt/ros/noetic/lib/libroscpp.so
/home/c208/walking_assist/devel/lib/strategy/remote_start_stop: /usr/lib/aarch64-linux-gnu/libpthread.so
/home/c208/walking_assist/devel/lib/strategy/remote_start_stop: /usr/lib/aarch64-linux-gnu/libboost_chrono.so.1.71.0
/home/c208/walking_assist/devel/lib/strategy/remote_start_stop: /usr/lib/aarch64-linux-gnu/libboost_filesystem.so.1.71.0
/home/c208/walking_assist/devel/lib/strategy/remote_start_stop: /opt/ros/noetic/lib/librosconsole.so
/home/c208/walking_assist/devel/lib/strategy/remote_start_stop: /opt/ros/noetic/lib/librosconsole_log4cxx.so
/home/c208/walking_assist/devel/lib/strategy/remote_start_stop: /opt/ros/noetic/lib/librosconsole_backend_interface.so
/home/c208/walking_assist/devel/lib/strategy/remote_start_stop: /usr/lib/aarch64-linux-gnu/liblog4cxx.so
/home/c208/walking_assist/devel/lib/strategy/remote_start_stop: /usr/lib/aarch64-linux-gnu/libboost_regex.so.1.71.0
/home/c208/walking_assist/devel/lib/strategy/remote_start_stop: /opt/ros/noetic/lib/libxmlrpcpp.so
/home/c208/walking_assist/devel/lib/strategy/remote_start_stop: /opt/ros/noetic/lib/libroscpp_serialization.so
/home/c208/walking_assist/devel/lib/strategy/remote_start_stop: /opt/ros/noetic/lib/librostime.so
/home/c208/walking_assist/devel/lib/strategy/remote_start_stop: /usr/lib/aarch64-linux-gnu/libboost_date_time.so.1.71.0
/home/c208/walking_assist/devel/lib/strategy/remote_start_stop: /opt/ros/noetic/lib/libcpp_common.so
/home/c208/walking_assist/devel/lib/strategy/remote_start_stop: /usr/lib/aarch64-linux-gnu/libboost_system.so.1.71.0
/home/c208/walking_assist/devel/lib/strategy/remote_start_stop: /usr/lib/aarch64-linux-gnu/libboost_thread.so.1.71.0
/home/c208/walking_assist/devel/lib/strategy/remote_start_stop: /usr/lib/aarch64-linux-gnu/libconsole_bridge.so.0.4
/home/c208/walking_assist/devel/lib/strategy/remote_start_stop: strategy/CMakeFiles/remote_start_stop.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/c208/walking_assist/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable /home/c208/walking_assist/devel/lib/strategy/remote_start_stop"
	cd /home/c208/walking_assist/build/strategy && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/remote_start_stop.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
strategy/CMakeFiles/remote_start_stop.dir/build: /home/c208/walking_assist/devel/lib/strategy/remote_start_stop

.PHONY : strategy/CMakeFiles/remote_start_stop.dir/build

strategy/CMakeFiles/remote_start_stop.dir/clean:
	cd /home/c208/walking_assist/build/strategy && $(CMAKE_COMMAND) -P CMakeFiles/remote_start_stop.dir/cmake_clean.cmake
.PHONY : strategy/CMakeFiles/remote_start_stop.dir/clean

strategy/CMakeFiles/remote_start_stop.dir/depend:
	cd /home/c208/walking_assist/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/c208/walking_assist/src /home/c208/walking_assist/src/strategy /home/c208/walking_assist/build /home/c208/walking_assist/build/strategy /home/c208/walking_assist/build/strategy/CMakeFiles/remote_start_stop.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : strategy/CMakeFiles/remote_start_stop.dir/depend

