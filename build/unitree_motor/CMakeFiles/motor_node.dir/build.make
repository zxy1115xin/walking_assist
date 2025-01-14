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
include unitree_motor/CMakeFiles/motor_node.dir/depend.make

# Include the progress variables for this target.
include unitree_motor/CMakeFiles/motor_node.dir/progress.make

# Include the compile flags for this target's objects.
include unitree_motor/CMakeFiles/motor_node.dir/flags.make

unitree_motor/CMakeFiles/motor_node.dir/src/motor.cpp.o: unitree_motor/CMakeFiles/motor_node.dir/flags.make
unitree_motor/CMakeFiles/motor_node.dir/src/motor.cpp.o: /home/c208/walking_assist/src/unitree_motor/src/motor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/c208/walking_assist/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object unitree_motor/CMakeFiles/motor_node.dir/src/motor.cpp.o"
	cd /home/c208/walking_assist/build/unitree_motor && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/motor_node.dir/src/motor.cpp.o -c /home/c208/walking_assist/src/unitree_motor/src/motor.cpp

unitree_motor/CMakeFiles/motor_node.dir/src/motor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/motor_node.dir/src/motor.cpp.i"
	cd /home/c208/walking_assist/build/unitree_motor && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/c208/walking_assist/src/unitree_motor/src/motor.cpp > CMakeFiles/motor_node.dir/src/motor.cpp.i

unitree_motor/CMakeFiles/motor_node.dir/src/motor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/motor_node.dir/src/motor.cpp.s"
	cd /home/c208/walking_assist/build/unitree_motor && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/c208/walking_assist/src/unitree_motor/src/motor.cpp -o CMakeFiles/motor_node.dir/src/motor.cpp.s

unitree_motor/CMakeFiles/motor_node.dir/src/UnitreeMotor.cpp.o: unitree_motor/CMakeFiles/motor_node.dir/flags.make
unitree_motor/CMakeFiles/motor_node.dir/src/UnitreeMotor.cpp.o: /home/c208/walking_assist/src/unitree_motor/src/UnitreeMotor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/c208/walking_assist/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object unitree_motor/CMakeFiles/motor_node.dir/src/UnitreeMotor.cpp.o"
	cd /home/c208/walking_assist/build/unitree_motor && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/motor_node.dir/src/UnitreeMotor.cpp.o -c /home/c208/walking_assist/src/unitree_motor/src/UnitreeMotor.cpp

unitree_motor/CMakeFiles/motor_node.dir/src/UnitreeMotor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/motor_node.dir/src/UnitreeMotor.cpp.i"
	cd /home/c208/walking_assist/build/unitree_motor && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/c208/walking_assist/src/unitree_motor/src/UnitreeMotor.cpp > CMakeFiles/motor_node.dir/src/UnitreeMotor.cpp.i

unitree_motor/CMakeFiles/motor_node.dir/src/UnitreeMotor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/motor_node.dir/src/UnitreeMotor.cpp.s"
	cd /home/c208/walking_assist/build/unitree_motor && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/c208/walking_assist/src/unitree_motor/src/UnitreeMotor.cpp -o CMakeFiles/motor_node.dir/src/UnitreeMotor.cpp.s

# Object files for target motor_node
motor_node_OBJECTS = \
"CMakeFiles/motor_node.dir/src/motor.cpp.o" \
"CMakeFiles/motor_node.dir/src/UnitreeMotor.cpp.o"

# External object files for target motor_node
motor_node_EXTERNAL_OBJECTS =

/home/c208/walking_assist/devel/lib/unitree_motor/motor_node: unitree_motor/CMakeFiles/motor_node.dir/src/motor.cpp.o
/home/c208/walking_assist/devel/lib/unitree_motor/motor_node: unitree_motor/CMakeFiles/motor_node.dir/src/UnitreeMotor.cpp.o
/home/c208/walking_assist/devel/lib/unitree_motor/motor_node: unitree_motor/CMakeFiles/motor_node.dir/build.make
/home/c208/walking_assist/devel/lib/unitree_motor/motor_node: /opt/ros/noetic/lib/libroscpp.so
/home/c208/walking_assist/devel/lib/unitree_motor/motor_node: /usr/lib/aarch64-linux-gnu/libpthread.so
/home/c208/walking_assist/devel/lib/unitree_motor/motor_node: /usr/lib/aarch64-linux-gnu/libboost_chrono.so.1.71.0
/home/c208/walking_assist/devel/lib/unitree_motor/motor_node: /usr/lib/aarch64-linux-gnu/libboost_filesystem.so.1.71.0
/home/c208/walking_assist/devel/lib/unitree_motor/motor_node: /opt/ros/noetic/lib/librosconsole.so
/home/c208/walking_assist/devel/lib/unitree_motor/motor_node: /opt/ros/noetic/lib/librosconsole_log4cxx.so
/home/c208/walking_assist/devel/lib/unitree_motor/motor_node: /opt/ros/noetic/lib/librosconsole_backend_interface.so
/home/c208/walking_assist/devel/lib/unitree_motor/motor_node: /usr/lib/aarch64-linux-gnu/liblog4cxx.so
/home/c208/walking_assist/devel/lib/unitree_motor/motor_node: /usr/lib/aarch64-linux-gnu/libboost_regex.so.1.71.0
/home/c208/walking_assist/devel/lib/unitree_motor/motor_node: /opt/ros/noetic/lib/libxmlrpcpp.so
/home/c208/walking_assist/devel/lib/unitree_motor/motor_node: /opt/ros/noetic/lib/libroscpp_serialization.so
/home/c208/walking_assist/devel/lib/unitree_motor/motor_node: /opt/ros/noetic/lib/librostime.so
/home/c208/walking_assist/devel/lib/unitree_motor/motor_node: /usr/lib/aarch64-linux-gnu/libboost_date_time.so.1.71.0
/home/c208/walking_assist/devel/lib/unitree_motor/motor_node: /opt/ros/noetic/lib/libcpp_common.so
/home/c208/walking_assist/devel/lib/unitree_motor/motor_node: /usr/lib/aarch64-linux-gnu/libboost_system.so.1.71.0
/home/c208/walking_assist/devel/lib/unitree_motor/motor_node: /usr/lib/aarch64-linux-gnu/libboost_thread.so.1.71.0
/home/c208/walking_assist/devel/lib/unitree_motor/motor_node: /usr/lib/aarch64-linux-gnu/libconsole_bridge.so.0.4
/home/c208/walking_assist/devel/lib/unitree_motor/motor_node: unitree_motor/CMakeFiles/motor_node.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/c208/walking_assist/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable /home/c208/walking_assist/devel/lib/unitree_motor/motor_node"
	cd /home/c208/walking_assist/build/unitree_motor && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/motor_node.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
unitree_motor/CMakeFiles/motor_node.dir/build: /home/c208/walking_assist/devel/lib/unitree_motor/motor_node

.PHONY : unitree_motor/CMakeFiles/motor_node.dir/build

unitree_motor/CMakeFiles/motor_node.dir/clean:
	cd /home/c208/walking_assist/build/unitree_motor && $(CMAKE_COMMAND) -P CMakeFiles/motor_node.dir/cmake_clean.cmake
.PHONY : unitree_motor/CMakeFiles/motor_node.dir/clean

unitree_motor/CMakeFiles/motor_node.dir/depend:
	cd /home/c208/walking_assist/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/c208/walking_assist/src /home/c208/walking_assist/src/unitree_motor /home/c208/walking_assist/build /home/c208/walking_assist/build/unitree_motor /home/c208/walking_assist/build/unitree_motor/CMakeFiles/motor_node.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : unitree_motor/CMakeFiles/motor_node.dir/depend

