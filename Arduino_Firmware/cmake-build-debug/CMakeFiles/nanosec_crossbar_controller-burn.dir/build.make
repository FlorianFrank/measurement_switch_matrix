# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/florianfrank/Applications/CLion-2020.2.4/clion-2020.2.4/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/florianfrank/Applications/CLion-2020.2.4/clion-2020.2.4/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/florianfrank/Documents/Research/Projects/NanoSec/measurement_switch_matrix/nanosec_crossbar_controller/Arduino_Firmware

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/florianfrank/Documents/Research/Projects/NanoSec/measurement_switch_matrix/nanosec_crossbar_controller/Arduino_Firmware/cmake-build-debug

# Utility rule file for nanosec_crossbar_controller-burn.

# Include any custom commands dependencies for this target.
include CMakeFiles/nanosec_crossbar_controller-burn.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/nanosec_crossbar_controller-burn.dir/progress.make

CMakeFiles/nanosec_crossbar_controller-burn: nanosec_crossbar_controller.elf
	/home/florianfrank/Downloads/arduino-1.8.18/hardware/tools/avr/bin/avrdude -C/home/florianfrank/Downloads/arduino-1.8.18/hardware/tools/avr/etc/avrdude.conf -cstk500v2 -Pusb -patmega328p -v -Uflash:w:/home/florianfrank/Documents/Research/Projects/NanoSec/measurement_switch_matrix/nanosec_crossbar_controller/Arduino_Firmware/cmake-build-debug/nanosec_crossbar_controller.hex

nanosec_crossbar_controller-burn: CMakeFiles/nanosec_crossbar_controller-burn
nanosec_crossbar_controller-burn: CMakeFiles/nanosec_crossbar_controller-burn.dir/build.make
.PHONY : nanosec_crossbar_controller-burn

# Rule to build all files generated by this target.
CMakeFiles/nanosec_crossbar_controller-burn.dir/build: nanosec_crossbar_controller-burn
.PHONY : CMakeFiles/nanosec_crossbar_controller-burn.dir/build

CMakeFiles/nanosec_crossbar_controller-burn.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/nanosec_crossbar_controller-burn.dir/cmake_clean.cmake
.PHONY : CMakeFiles/nanosec_crossbar_controller-burn.dir/clean

CMakeFiles/nanosec_crossbar_controller-burn.dir/depend:
	cd /home/florianfrank/Documents/Research/Projects/NanoSec/measurement_switch_matrix/nanosec_crossbar_controller/Arduino_Firmware/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/florianfrank/Documents/Research/Projects/NanoSec/measurement_switch_matrix/nanosec_crossbar_controller/Arduino_Firmware /home/florianfrank/Documents/Research/Projects/NanoSec/measurement_switch_matrix/nanosec_crossbar_controller/Arduino_Firmware /home/florianfrank/Documents/Research/Projects/NanoSec/measurement_switch_matrix/nanosec_crossbar_controller/Arduino_Firmware/cmake-build-debug /home/florianfrank/Documents/Research/Projects/NanoSec/measurement_switch_matrix/nanosec_crossbar_controller/Arduino_Firmware/cmake-build-debug /home/florianfrank/Documents/Research/Projects/NanoSec/measurement_switch_matrix/nanosec_crossbar_controller/Arduino_Firmware/cmake-build-debug/CMakeFiles/nanosec_crossbar_controller-burn.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/nanosec_crossbar_controller-burn.dir/depend

