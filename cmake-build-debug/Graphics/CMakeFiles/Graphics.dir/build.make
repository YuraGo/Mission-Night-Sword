# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /snap/clion/44/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/44/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dartmoor/Desktop/C++/nightsword

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dartmoor/Desktop/C++/nightsword/cmake-build-debug

# Include any dependencies generated for this target.
include Graphics/CMakeFiles/Graphics.dir/depend.make

# Include the progress variables for this target.
include Graphics/CMakeFiles/Graphics.dir/progress.make

# Include the compile flags for this target's objects.
include Graphics/CMakeFiles/Graphics.dir/flags.make

Graphics/CMakeFiles/Graphics.dir/graphics.cpp.o: Graphics/CMakeFiles/Graphics.dir/flags.make
Graphics/CMakeFiles/Graphics.dir/graphics.cpp.o: ../Graphics/graphics.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dartmoor/Desktop/C++/nightsword/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Graphics/CMakeFiles/Graphics.dir/graphics.cpp.o"
	cd /home/dartmoor/Desktop/C++/nightsword/cmake-build-debug/Graphics && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Graphics.dir/graphics.cpp.o -c /home/dartmoor/Desktop/C++/nightsword/Graphics/graphics.cpp

Graphics/CMakeFiles/Graphics.dir/graphics.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Graphics.dir/graphics.cpp.i"
	cd /home/dartmoor/Desktop/C++/nightsword/cmake-build-debug/Graphics && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dartmoor/Desktop/C++/nightsword/Graphics/graphics.cpp > CMakeFiles/Graphics.dir/graphics.cpp.i

Graphics/CMakeFiles/Graphics.dir/graphics.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Graphics.dir/graphics.cpp.s"
	cd /home/dartmoor/Desktop/C++/nightsword/cmake-build-debug/Graphics && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dartmoor/Desktop/C++/nightsword/Graphics/graphics.cpp -o CMakeFiles/Graphics.dir/graphics.cpp.s

# Object files for target Graphics
Graphics_OBJECTS = \
"CMakeFiles/Graphics.dir/graphics.cpp.o"

# External object files for target Graphics
Graphics_EXTERNAL_OBJECTS =

Graphics/libGraphics.a: Graphics/CMakeFiles/Graphics.dir/graphics.cpp.o
Graphics/libGraphics.a: Graphics/CMakeFiles/Graphics.dir/build.make
Graphics/libGraphics.a: Graphics/CMakeFiles/Graphics.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dartmoor/Desktop/C++/nightsword/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libGraphics.a"
	cd /home/dartmoor/Desktop/C++/nightsword/cmake-build-debug/Graphics && $(CMAKE_COMMAND) -P CMakeFiles/Graphics.dir/cmake_clean_target.cmake
	cd /home/dartmoor/Desktop/C++/nightsword/cmake-build-debug/Graphics && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Graphics.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Graphics/CMakeFiles/Graphics.dir/build: Graphics/libGraphics.a

.PHONY : Graphics/CMakeFiles/Graphics.dir/build

Graphics/CMakeFiles/Graphics.dir/clean:
	cd /home/dartmoor/Desktop/C++/nightsword/cmake-build-debug/Graphics && $(CMAKE_COMMAND) -P CMakeFiles/Graphics.dir/cmake_clean.cmake
.PHONY : Graphics/CMakeFiles/Graphics.dir/clean

Graphics/CMakeFiles/Graphics.dir/depend:
	cd /home/dartmoor/Desktop/C++/nightsword/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dartmoor/Desktop/C++/nightsword /home/dartmoor/Desktop/C++/nightsword/Graphics /home/dartmoor/Desktop/C++/nightsword/cmake-build-debug /home/dartmoor/Desktop/C++/nightsword/cmake-build-debug/Graphics /home/dartmoor/Desktop/C++/nightsword/cmake-build-debug/Graphics/CMakeFiles/Graphics.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Graphics/CMakeFiles/Graphics.dir/depend

