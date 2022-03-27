# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/shurik/myCodes/myGames/CowRunner_cocos

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/shurik/myCodes/myGames/CowRunner_cocos/linux-build

# Include any dependencies generated for this target.
include engine/external/clipper/CMakeFiles/ext_clipper.dir/depend.make

# Include the progress variables for this target.
include engine/external/clipper/CMakeFiles/ext_clipper.dir/progress.make

# Include the compile flags for this target's objects.
include engine/external/clipper/CMakeFiles/ext_clipper.dir/flags.make

engine/external/clipper/CMakeFiles/ext_clipper.dir/clipper.cpp.o: engine/external/clipper/CMakeFiles/ext_clipper.dir/flags.make
engine/external/clipper/CMakeFiles/ext_clipper.dir/clipper.cpp.o: ../cocos2d/external/clipper/clipper.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/shurik/myCodes/myGames/CowRunner_cocos/linux-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object engine/external/clipper/CMakeFiles/ext_clipper.dir/clipper.cpp.o"
	cd /home/shurik/myCodes/myGames/CowRunner_cocos/linux-build/engine/external/clipper && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ext_clipper.dir/clipper.cpp.o -c /home/shurik/myCodes/myGames/CowRunner_cocos/cocos2d/external/clipper/clipper.cpp

engine/external/clipper/CMakeFiles/ext_clipper.dir/clipper.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ext_clipper.dir/clipper.cpp.i"
	cd /home/shurik/myCodes/myGames/CowRunner_cocos/linux-build/engine/external/clipper && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/shurik/myCodes/myGames/CowRunner_cocos/cocos2d/external/clipper/clipper.cpp > CMakeFiles/ext_clipper.dir/clipper.cpp.i

engine/external/clipper/CMakeFiles/ext_clipper.dir/clipper.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ext_clipper.dir/clipper.cpp.s"
	cd /home/shurik/myCodes/myGames/CowRunner_cocos/linux-build/engine/external/clipper && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/shurik/myCodes/myGames/CowRunner_cocos/cocos2d/external/clipper/clipper.cpp -o CMakeFiles/ext_clipper.dir/clipper.cpp.s

# Object files for target ext_clipper
ext_clipper_OBJECTS = \
"CMakeFiles/ext_clipper.dir/clipper.cpp.o"

# External object files for target ext_clipper
ext_clipper_EXTERNAL_OBJECTS =

lib/libext_clipper.a: engine/external/clipper/CMakeFiles/ext_clipper.dir/clipper.cpp.o
lib/libext_clipper.a: engine/external/clipper/CMakeFiles/ext_clipper.dir/build.make
lib/libext_clipper.a: engine/external/clipper/CMakeFiles/ext_clipper.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/shurik/myCodes/myGames/CowRunner_cocos/linux-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library ../../../lib/libext_clipper.a"
	cd /home/shurik/myCodes/myGames/CowRunner_cocos/linux-build/engine/external/clipper && $(CMAKE_COMMAND) -P CMakeFiles/ext_clipper.dir/cmake_clean_target.cmake
	cd /home/shurik/myCodes/myGames/CowRunner_cocos/linux-build/engine/external/clipper && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ext_clipper.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
engine/external/clipper/CMakeFiles/ext_clipper.dir/build: lib/libext_clipper.a

.PHONY : engine/external/clipper/CMakeFiles/ext_clipper.dir/build

engine/external/clipper/CMakeFiles/ext_clipper.dir/clean:
	cd /home/shurik/myCodes/myGames/CowRunner_cocos/linux-build/engine/external/clipper && $(CMAKE_COMMAND) -P CMakeFiles/ext_clipper.dir/cmake_clean.cmake
.PHONY : engine/external/clipper/CMakeFiles/ext_clipper.dir/clean

engine/external/clipper/CMakeFiles/ext_clipper.dir/depend:
	cd /home/shurik/myCodes/myGames/CowRunner_cocos/linux-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/shurik/myCodes/myGames/CowRunner_cocos /home/shurik/myCodes/myGames/CowRunner_cocos/cocos2d/external/clipper /home/shurik/myCodes/myGames/CowRunner_cocos/linux-build /home/shurik/myCodes/myGames/CowRunner_cocos/linux-build/engine/external/clipper /home/shurik/myCodes/myGames/CowRunner_cocos/linux-build/engine/external/clipper/CMakeFiles/ext_clipper.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : engine/external/clipper/CMakeFiles/ext_clipper.dir/depend

