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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.15.3/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.15.3/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Applications/POK/AKC/threads_integration

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Applications/POK/AKC/threads_integration/build

# Include any dependencies generated for this target.
include CMakeFiles/threads_integration.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/threads_integration.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/threads_integration.dir/flags.make

CMakeFiles/threads_integration.dir/main.cpp.o: CMakeFiles/threads_integration.dir/flags.make
CMakeFiles/threads_integration.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Applications/POK/AKC/threads_integration/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/threads_integration.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/threads_integration.dir/main.cpp.o -c /Applications/POK/AKC/threads_integration/main.cpp

CMakeFiles/threads_integration.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/threads_integration.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Applications/POK/AKC/threads_integration/main.cpp > CMakeFiles/threads_integration.dir/main.cpp.i

CMakeFiles/threads_integration.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/threads_integration.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Applications/POK/AKC/threads_integration/main.cpp -o CMakeFiles/threads_integration.dir/main.cpp.s

# Object files for target threads_integration
threads_integration_OBJECTS = \
"CMakeFiles/threads_integration.dir/main.cpp.o"

# External object files for target threads_integration
threads_integration_EXTERNAL_OBJECTS =

threads_integration: CMakeFiles/threads_integration.dir/main.cpp.o
threads_integration: CMakeFiles/threads_integration.dir/build.make
threads_integration: CMakeFiles/threads_integration.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Applications/POK/AKC/threads_integration/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable threads_integration"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/threads_integration.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/threads_integration.dir/build: threads_integration

.PHONY : CMakeFiles/threads_integration.dir/build

CMakeFiles/threads_integration.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/threads_integration.dir/cmake_clean.cmake
.PHONY : CMakeFiles/threads_integration.dir/clean

CMakeFiles/threads_integration.dir/depend:
	cd /Applications/POK/AKC/threads_integration/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Applications/POK/AKC/threads_integration /Applications/POK/AKC/threads_integration /Applications/POK/AKC/threads_integration/build /Applications/POK/AKC/threads_integration/build /Applications/POK/AKC/threads_integration/build/CMakeFiles/threads_integration.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/threads_integration.dir/depend

