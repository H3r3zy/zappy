# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = /home/wisenoa/Téléchargements/clion-2017.3.1/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/wisenoa/Téléchargements/clion-2017.3.1/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/wisenoa/PSU_zappy_2017

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wisenoa/PSU_zappy_2017/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/PSU_zappy_2017.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/PSU_zappy_2017.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/PSU_zappy_2017.dir/flags.make

CMakeFiles/PSU_zappy_2017.dir/src/main.cpp.o: CMakeFiles/PSU_zappy_2017.dir/flags.make
CMakeFiles/PSU_zappy_2017.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wisenoa/PSU_zappy_2017/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/PSU_zappy_2017.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PSU_zappy_2017.dir/src/main.cpp.o -c /home/wisenoa/PSU_zappy_2017/src/main.cpp

CMakeFiles/PSU_zappy_2017.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PSU_zappy_2017.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wisenoa/PSU_zappy_2017/src/main.cpp > CMakeFiles/PSU_zappy_2017.dir/src/main.cpp.i

CMakeFiles/PSU_zappy_2017.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PSU_zappy_2017.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wisenoa/PSU_zappy_2017/src/main.cpp -o CMakeFiles/PSU_zappy_2017.dir/src/main.cpp.s

CMakeFiles/PSU_zappy_2017.dir/src/main.cpp.o.requires:

.PHONY : CMakeFiles/PSU_zappy_2017.dir/src/main.cpp.o.requires

CMakeFiles/PSU_zappy_2017.dir/src/main.cpp.o.provides: CMakeFiles/PSU_zappy_2017.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/PSU_zappy_2017.dir/build.make CMakeFiles/PSU_zappy_2017.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/PSU_zappy_2017.dir/src/main.cpp.o.provides

CMakeFiles/PSU_zappy_2017.dir/src/main.cpp.o.provides.build: CMakeFiles/PSU_zappy_2017.dir/src/main.cpp.o


CMakeFiles/PSU_zappy_2017.dir/src/Map.cpp.o: CMakeFiles/PSU_zappy_2017.dir/flags.make
CMakeFiles/PSU_zappy_2017.dir/src/Map.cpp.o: ../src/Map.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wisenoa/PSU_zappy_2017/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/PSU_zappy_2017.dir/src/Map.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PSU_zappy_2017.dir/src/Map.cpp.o -c /home/wisenoa/PSU_zappy_2017/src/Map.cpp

CMakeFiles/PSU_zappy_2017.dir/src/Map.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PSU_zappy_2017.dir/src/Map.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wisenoa/PSU_zappy_2017/src/Map.cpp > CMakeFiles/PSU_zappy_2017.dir/src/Map.cpp.i

CMakeFiles/PSU_zappy_2017.dir/src/Map.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PSU_zappy_2017.dir/src/Map.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wisenoa/PSU_zappy_2017/src/Map.cpp -o CMakeFiles/PSU_zappy_2017.dir/src/Map.cpp.s

CMakeFiles/PSU_zappy_2017.dir/src/Map.cpp.o.requires:

.PHONY : CMakeFiles/PSU_zappy_2017.dir/src/Map.cpp.o.requires

CMakeFiles/PSU_zappy_2017.dir/src/Map.cpp.o.provides: CMakeFiles/PSU_zappy_2017.dir/src/Map.cpp.o.requires
	$(MAKE) -f CMakeFiles/PSU_zappy_2017.dir/build.make CMakeFiles/PSU_zappy_2017.dir/src/Map.cpp.o.provides.build
.PHONY : CMakeFiles/PSU_zappy_2017.dir/src/Map.cpp.o.provides

CMakeFiles/PSU_zappy_2017.dir/src/Map.cpp.o.provides.build: CMakeFiles/PSU_zappy_2017.dir/src/Map.cpp.o


CMakeFiles/PSU_zappy_2017.dir/src/Cell.cpp.o: CMakeFiles/PSU_zappy_2017.dir/flags.make
CMakeFiles/PSU_zappy_2017.dir/src/Cell.cpp.o: ../src/Cell.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wisenoa/PSU_zappy_2017/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/PSU_zappy_2017.dir/src/Cell.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PSU_zappy_2017.dir/src/Cell.cpp.o -c /home/wisenoa/PSU_zappy_2017/src/Cell.cpp

CMakeFiles/PSU_zappy_2017.dir/src/Cell.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PSU_zappy_2017.dir/src/Cell.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wisenoa/PSU_zappy_2017/src/Cell.cpp > CMakeFiles/PSU_zappy_2017.dir/src/Cell.cpp.i

CMakeFiles/PSU_zappy_2017.dir/src/Cell.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PSU_zappy_2017.dir/src/Cell.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wisenoa/PSU_zappy_2017/src/Cell.cpp -o CMakeFiles/PSU_zappy_2017.dir/src/Cell.cpp.s

CMakeFiles/PSU_zappy_2017.dir/src/Cell.cpp.o.requires:

.PHONY : CMakeFiles/PSU_zappy_2017.dir/src/Cell.cpp.o.requires

CMakeFiles/PSU_zappy_2017.dir/src/Cell.cpp.o.provides: CMakeFiles/PSU_zappy_2017.dir/src/Cell.cpp.o.requires
	$(MAKE) -f CMakeFiles/PSU_zappy_2017.dir/build.make CMakeFiles/PSU_zappy_2017.dir/src/Cell.cpp.o.provides.build
.PHONY : CMakeFiles/PSU_zappy_2017.dir/src/Cell.cpp.o.provides

CMakeFiles/PSU_zappy_2017.dir/src/Cell.cpp.o.provides.build: CMakeFiles/PSU_zappy_2017.dir/src/Cell.cpp.o


CMakeFiles/PSU_zappy_2017.dir/src/Grid.cpp.o: CMakeFiles/PSU_zappy_2017.dir/flags.make
CMakeFiles/PSU_zappy_2017.dir/src/Grid.cpp.o: ../src/Grid.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wisenoa/PSU_zappy_2017/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/PSU_zappy_2017.dir/src/Grid.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PSU_zappy_2017.dir/src/Grid.cpp.o -c /home/wisenoa/PSU_zappy_2017/src/Grid.cpp

CMakeFiles/PSU_zappy_2017.dir/src/Grid.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PSU_zappy_2017.dir/src/Grid.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wisenoa/PSU_zappy_2017/src/Grid.cpp > CMakeFiles/PSU_zappy_2017.dir/src/Grid.cpp.i

CMakeFiles/PSU_zappy_2017.dir/src/Grid.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PSU_zappy_2017.dir/src/Grid.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wisenoa/PSU_zappy_2017/src/Grid.cpp -o CMakeFiles/PSU_zappy_2017.dir/src/Grid.cpp.s

CMakeFiles/PSU_zappy_2017.dir/src/Grid.cpp.o.requires:

.PHONY : CMakeFiles/PSU_zappy_2017.dir/src/Grid.cpp.o.requires

CMakeFiles/PSU_zappy_2017.dir/src/Grid.cpp.o.provides: CMakeFiles/PSU_zappy_2017.dir/src/Grid.cpp.o.requires
	$(MAKE) -f CMakeFiles/PSU_zappy_2017.dir/build.make CMakeFiles/PSU_zappy_2017.dir/src/Grid.cpp.o.provides.build
.PHONY : CMakeFiles/PSU_zappy_2017.dir/src/Grid.cpp.o.provides

CMakeFiles/PSU_zappy_2017.dir/src/Grid.cpp.o.provides.build: CMakeFiles/PSU_zappy_2017.dir/src/Grid.cpp.o


CMakeFiles/PSU_zappy_2017.dir/src/WindowInfo.cpp.o: CMakeFiles/PSU_zappy_2017.dir/flags.make
CMakeFiles/PSU_zappy_2017.dir/src/WindowInfo.cpp.o: ../src/WindowInfo.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wisenoa/PSU_zappy_2017/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/PSU_zappy_2017.dir/src/WindowInfo.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PSU_zappy_2017.dir/src/WindowInfo.cpp.o -c /home/wisenoa/PSU_zappy_2017/src/WindowInfo.cpp

CMakeFiles/PSU_zappy_2017.dir/src/WindowInfo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PSU_zappy_2017.dir/src/WindowInfo.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wisenoa/PSU_zappy_2017/src/WindowInfo.cpp > CMakeFiles/PSU_zappy_2017.dir/src/WindowInfo.cpp.i

CMakeFiles/PSU_zappy_2017.dir/src/WindowInfo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PSU_zappy_2017.dir/src/WindowInfo.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wisenoa/PSU_zappy_2017/src/WindowInfo.cpp -o CMakeFiles/PSU_zappy_2017.dir/src/WindowInfo.cpp.s

CMakeFiles/PSU_zappy_2017.dir/src/WindowInfo.cpp.o.requires:

.PHONY : CMakeFiles/PSU_zappy_2017.dir/src/WindowInfo.cpp.o.requires

CMakeFiles/PSU_zappy_2017.dir/src/WindowInfo.cpp.o.provides: CMakeFiles/PSU_zappy_2017.dir/src/WindowInfo.cpp.o.requires
	$(MAKE) -f CMakeFiles/PSU_zappy_2017.dir/build.make CMakeFiles/PSU_zappy_2017.dir/src/WindowInfo.cpp.o.provides.build
.PHONY : CMakeFiles/PSU_zappy_2017.dir/src/WindowInfo.cpp.o.provides

CMakeFiles/PSU_zappy_2017.dir/src/WindowInfo.cpp.o.provides.build: CMakeFiles/PSU_zappy_2017.dir/src/WindowInfo.cpp.o


CMakeFiles/PSU_zappy_2017.dir/src/Character.cpp.o: CMakeFiles/PSU_zappy_2017.dir/flags.make
CMakeFiles/PSU_zappy_2017.dir/src/Character.cpp.o: ../src/Character.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wisenoa/PSU_zappy_2017/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/PSU_zappy_2017.dir/src/Character.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PSU_zappy_2017.dir/src/Character.cpp.o -c /home/wisenoa/PSU_zappy_2017/src/Character.cpp

CMakeFiles/PSU_zappy_2017.dir/src/Character.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PSU_zappy_2017.dir/src/Character.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wisenoa/PSU_zappy_2017/src/Character.cpp > CMakeFiles/PSU_zappy_2017.dir/src/Character.cpp.i

CMakeFiles/PSU_zappy_2017.dir/src/Character.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PSU_zappy_2017.dir/src/Character.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wisenoa/PSU_zappy_2017/src/Character.cpp -o CMakeFiles/PSU_zappy_2017.dir/src/Character.cpp.s

CMakeFiles/PSU_zappy_2017.dir/src/Character.cpp.o.requires:

.PHONY : CMakeFiles/PSU_zappy_2017.dir/src/Character.cpp.o.requires

CMakeFiles/PSU_zappy_2017.dir/src/Character.cpp.o.provides: CMakeFiles/PSU_zappy_2017.dir/src/Character.cpp.o.requires
	$(MAKE) -f CMakeFiles/PSU_zappy_2017.dir/build.make CMakeFiles/PSU_zappy_2017.dir/src/Character.cpp.o.provides.build
.PHONY : CMakeFiles/PSU_zappy_2017.dir/src/Character.cpp.o.provides

CMakeFiles/PSU_zappy_2017.dir/src/Character.cpp.o.provides.build: CMakeFiles/PSU_zappy_2017.dir/src/Character.cpp.o


# Object files for target PSU_zappy_2017
PSU_zappy_2017_OBJECTS = \
"CMakeFiles/PSU_zappy_2017.dir/src/main.cpp.o" \
"CMakeFiles/PSU_zappy_2017.dir/src/Map.cpp.o" \
"CMakeFiles/PSU_zappy_2017.dir/src/Cell.cpp.o" \
"CMakeFiles/PSU_zappy_2017.dir/src/Grid.cpp.o" \
"CMakeFiles/PSU_zappy_2017.dir/src/WindowInfo.cpp.o" \
"CMakeFiles/PSU_zappy_2017.dir/src/Character.cpp.o"

# External object files for target PSU_zappy_2017
PSU_zappy_2017_EXTERNAL_OBJECTS =

PSU_zappy_2017: CMakeFiles/PSU_zappy_2017.dir/src/main.cpp.o
PSU_zappy_2017: CMakeFiles/PSU_zappy_2017.dir/src/Map.cpp.o
PSU_zappy_2017: CMakeFiles/PSU_zappy_2017.dir/src/Cell.cpp.o
PSU_zappy_2017: CMakeFiles/PSU_zappy_2017.dir/src/Grid.cpp.o
PSU_zappy_2017: CMakeFiles/PSU_zappy_2017.dir/src/WindowInfo.cpp.o
PSU_zappy_2017: CMakeFiles/PSU_zappy_2017.dir/src/Character.cpp.o
PSU_zappy_2017: CMakeFiles/PSU_zappy_2017.dir/build.make
PSU_zappy_2017: CMakeFiles/PSU_zappy_2017.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wisenoa/PSU_zappy_2017/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable PSU_zappy_2017"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/PSU_zappy_2017.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/PSU_zappy_2017.dir/build: PSU_zappy_2017

.PHONY : CMakeFiles/PSU_zappy_2017.dir/build

CMakeFiles/PSU_zappy_2017.dir/requires: CMakeFiles/PSU_zappy_2017.dir/src/main.cpp.o.requires
CMakeFiles/PSU_zappy_2017.dir/requires: CMakeFiles/PSU_zappy_2017.dir/src/Map.cpp.o.requires
CMakeFiles/PSU_zappy_2017.dir/requires: CMakeFiles/PSU_zappy_2017.dir/src/Cell.cpp.o.requires
CMakeFiles/PSU_zappy_2017.dir/requires: CMakeFiles/PSU_zappy_2017.dir/src/Grid.cpp.o.requires
CMakeFiles/PSU_zappy_2017.dir/requires: CMakeFiles/PSU_zappy_2017.dir/src/WindowInfo.cpp.o.requires
CMakeFiles/PSU_zappy_2017.dir/requires: CMakeFiles/PSU_zappy_2017.dir/src/Character.cpp.o.requires

.PHONY : CMakeFiles/PSU_zappy_2017.dir/requires

CMakeFiles/PSU_zappy_2017.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/PSU_zappy_2017.dir/cmake_clean.cmake
.PHONY : CMakeFiles/PSU_zappy_2017.dir/clean

CMakeFiles/PSU_zappy_2017.dir/depend:
	cd /home/wisenoa/PSU_zappy_2017/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wisenoa/PSU_zappy_2017 /home/wisenoa/PSU_zappy_2017 /home/wisenoa/PSU_zappy_2017/cmake-build-debug /home/wisenoa/PSU_zappy_2017/cmake-build-debug /home/wisenoa/PSU_zappy_2017/cmake-build-debug/CMakeFiles/PSU_zappy_2017.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/PSU_zappy_2017.dir/depend

