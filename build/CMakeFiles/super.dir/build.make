# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/dumitru/ClionProjects/KaZaA

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dumitru/ClionProjects/KaZaA/build

# Include any dependencies generated for this target.
include CMakeFiles/super.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/super.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/super.dir/flags.make

CMakeFiles/super.dir/src/IOLoop.cpp.o: CMakeFiles/super.dir/flags.make
CMakeFiles/super.dir/src/IOLoop.cpp.o: ../src/IOLoop.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dumitru/ClionProjects/KaZaA/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/super.dir/src/IOLoop.cpp.o"
	g++-6   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/super.dir/src/IOLoop.cpp.o -c /home/dumitru/ClionProjects/KaZaA/src/IOLoop.cpp

CMakeFiles/super.dir/src/IOLoop.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/super.dir/src/IOLoop.cpp.i"
	g++-6  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dumitru/ClionProjects/KaZaA/src/IOLoop.cpp > CMakeFiles/super.dir/src/IOLoop.cpp.i

CMakeFiles/super.dir/src/IOLoop.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/super.dir/src/IOLoop.cpp.s"
	g++-6  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dumitru/ClionProjects/KaZaA/src/IOLoop.cpp -o CMakeFiles/super.dir/src/IOLoop.cpp.s

CMakeFiles/super.dir/src/IOLoop.cpp.o.requires:

.PHONY : CMakeFiles/super.dir/src/IOLoop.cpp.o.requires

CMakeFiles/super.dir/src/IOLoop.cpp.o.provides: CMakeFiles/super.dir/src/IOLoop.cpp.o.requires
	$(MAKE) -f CMakeFiles/super.dir/build.make CMakeFiles/super.dir/src/IOLoop.cpp.o.provides.build
.PHONY : CMakeFiles/super.dir/src/IOLoop.cpp.o.provides

CMakeFiles/super.dir/src/IOLoop.cpp.o.provides.build: CMakeFiles/super.dir/src/IOLoop.cpp.o


CMakeFiles/super.dir/src/Message.cpp.o: CMakeFiles/super.dir/flags.make
CMakeFiles/super.dir/src/Message.cpp.o: ../src/Message.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dumitru/ClionProjects/KaZaA/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/super.dir/src/Message.cpp.o"
	g++-6   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/super.dir/src/Message.cpp.o -c /home/dumitru/ClionProjects/KaZaA/src/Message.cpp

CMakeFiles/super.dir/src/Message.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/super.dir/src/Message.cpp.i"
	g++-6  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dumitru/ClionProjects/KaZaA/src/Message.cpp > CMakeFiles/super.dir/src/Message.cpp.i

CMakeFiles/super.dir/src/Message.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/super.dir/src/Message.cpp.s"
	g++-6  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dumitru/ClionProjects/KaZaA/src/Message.cpp -o CMakeFiles/super.dir/src/Message.cpp.s

CMakeFiles/super.dir/src/Message.cpp.o.requires:

.PHONY : CMakeFiles/super.dir/src/Message.cpp.o.requires

CMakeFiles/super.dir/src/Message.cpp.o.provides: CMakeFiles/super.dir/src/Message.cpp.o.requires
	$(MAKE) -f CMakeFiles/super.dir/build.make CMakeFiles/super.dir/src/Message.cpp.o.provides.build
.PHONY : CMakeFiles/super.dir/src/Message.cpp.o.provides

CMakeFiles/super.dir/src/Message.cpp.o.provides.build: CMakeFiles/super.dir/src/Message.cpp.o


CMakeFiles/super.dir/src/Utils.cpp.o: CMakeFiles/super.dir/flags.make
CMakeFiles/super.dir/src/Utils.cpp.o: ../src/Utils.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dumitru/ClionProjects/KaZaA/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/super.dir/src/Utils.cpp.o"
	g++-6   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/super.dir/src/Utils.cpp.o -c /home/dumitru/ClionProjects/KaZaA/src/Utils.cpp

CMakeFiles/super.dir/src/Utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/super.dir/src/Utils.cpp.i"
	g++-6  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dumitru/ClionProjects/KaZaA/src/Utils.cpp > CMakeFiles/super.dir/src/Utils.cpp.i

CMakeFiles/super.dir/src/Utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/super.dir/src/Utils.cpp.s"
	g++-6  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dumitru/ClionProjects/KaZaA/src/Utils.cpp -o CMakeFiles/super.dir/src/Utils.cpp.s

CMakeFiles/super.dir/src/Utils.cpp.o.requires:

.PHONY : CMakeFiles/super.dir/src/Utils.cpp.o.requires

CMakeFiles/super.dir/src/Utils.cpp.o.provides: CMakeFiles/super.dir/src/Utils.cpp.o.requires
	$(MAKE) -f CMakeFiles/super.dir/build.make CMakeFiles/super.dir/src/Utils.cpp.o.provides.build
.PHONY : CMakeFiles/super.dir/src/Utils.cpp.o.provides

CMakeFiles/super.dir/src/Utils.cpp.o.provides.build: CMakeFiles/super.dir/src/Utils.cpp.o


CMakeFiles/super.dir/src/Socket.cpp.o: CMakeFiles/super.dir/flags.make
CMakeFiles/super.dir/src/Socket.cpp.o: ../src/Socket.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dumitru/ClionProjects/KaZaA/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/super.dir/src/Socket.cpp.o"
	g++-6   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/super.dir/src/Socket.cpp.o -c /home/dumitru/ClionProjects/KaZaA/src/Socket.cpp

CMakeFiles/super.dir/src/Socket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/super.dir/src/Socket.cpp.i"
	g++-6  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dumitru/ClionProjects/KaZaA/src/Socket.cpp > CMakeFiles/super.dir/src/Socket.cpp.i

CMakeFiles/super.dir/src/Socket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/super.dir/src/Socket.cpp.s"
	g++-6  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dumitru/ClionProjects/KaZaA/src/Socket.cpp -o CMakeFiles/super.dir/src/Socket.cpp.s

CMakeFiles/super.dir/src/Socket.cpp.o.requires:

.PHONY : CMakeFiles/super.dir/src/Socket.cpp.o.requires

CMakeFiles/super.dir/src/Socket.cpp.o.provides: CMakeFiles/super.dir/src/Socket.cpp.o.requires
	$(MAKE) -f CMakeFiles/super.dir/build.make CMakeFiles/super.dir/src/Socket.cpp.o.provides.build
.PHONY : CMakeFiles/super.dir/src/Socket.cpp.o.provides

CMakeFiles/super.dir/src/Socket.cpp.o.provides.build: CMakeFiles/super.dir/src/Socket.cpp.o


CMakeFiles/super.dir/src/File.cpp.o: CMakeFiles/super.dir/flags.make
CMakeFiles/super.dir/src/File.cpp.o: ../src/File.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dumitru/ClionProjects/KaZaA/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/super.dir/src/File.cpp.o"
	g++-6   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/super.dir/src/File.cpp.o -c /home/dumitru/ClionProjects/KaZaA/src/File.cpp

CMakeFiles/super.dir/src/File.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/super.dir/src/File.cpp.i"
	g++-6  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dumitru/ClionProjects/KaZaA/src/File.cpp > CMakeFiles/super.dir/src/File.cpp.i

CMakeFiles/super.dir/src/File.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/super.dir/src/File.cpp.s"
	g++-6  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dumitru/ClionProjects/KaZaA/src/File.cpp -o CMakeFiles/super.dir/src/File.cpp.s

CMakeFiles/super.dir/src/File.cpp.o.requires:

.PHONY : CMakeFiles/super.dir/src/File.cpp.o.requires

CMakeFiles/super.dir/src/File.cpp.o.provides: CMakeFiles/super.dir/src/File.cpp.o.requires
	$(MAKE) -f CMakeFiles/super.dir/build.make CMakeFiles/super.dir/src/File.cpp.o.provides.build
.PHONY : CMakeFiles/super.dir/src/File.cpp.o.provides

CMakeFiles/super.dir/src/File.cpp.o.provides.build: CMakeFiles/super.dir/src/File.cpp.o


CMakeFiles/super.dir/src/IOHandler.cpp.o: CMakeFiles/super.dir/flags.make
CMakeFiles/super.dir/src/IOHandler.cpp.o: ../src/IOHandler.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dumitru/ClionProjects/KaZaA/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/super.dir/src/IOHandler.cpp.o"
	g++-6   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/super.dir/src/IOHandler.cpp.o -c /home/dumitru/ClionProjects/KaZaA/src/IOHandler.cpp

CMakeFiles/super.dir/src/IOHandler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/super.dir/src/IOHandler.cpp.i"
	g++-6  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dumitru/ClionProjects/KaZaA/src/IOHandler.cpp > CMakeFiles/super.dir/src/IOHandler.cpp.i

CMakeFiles/super.dir/src/IOHandler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/super.dir/src/IOHandler.cpp.s"
	g++-6  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dumitru/ClionProjects/KaZaA/src/IOHandler.cpp -o CMakeFiles/super.dir/src/IOHandler.cpp.s

CMakeFiles/super.dir/src/IOHandler.cpp.o.requires:

.PHONY : CMakeFiles/super.dir/src/IOHandler.cpp.o.requires

CMakeFiles/super.dir/src/IOHandler.cpp.o.provides: CMakeFiles/super.dir/src/IOHandler.cpp.o.requires
	$(MAKE) -f CMakeFiles/super.dir/build.make CMakeFiles/super.dir/src/IOHandler.cpp.o.provides.build
.PHONY : CMakeFiles/super.dir/src/IOHandler.cpp.o.provides

CMakeFiles/super.dir/src/IOHandler.cpp.o.provides.build: CMakeFiles/super.dir/src/IOHandler.cpp.o


CMakeFiles/super.dir/super.cpp.o: CMakeFiles/super.dir/flags.make
CMakeFiles/super.dir/super.cpp.o: ../super.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dumitru/ClionProjects/KaZaA/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/super.dir/super.cpp.o"
	g++-6   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/super.dir/super.cpp.o -c /home/dumitru/ClionProjects/KaZaA/super.cpp

CMakeFiles/super.dir/super.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/super.dir/super.cpp.i"
	g++-6  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dumitru/ClionProjects/KaZaA/super.cpp > CMakeFiles/super.dir/super.cpp.i

CMakeFiles/super.dir/super.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/super.dir/super.cpp.s"
	g++-6  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dumitru/ClionProjects/KaZaA/super.cpp -o CMakeFiles/super.dir/super.cpp.s

CMakeFiles/super.dir/super.cpp.o.requires:

.PHONY : CMakeFiles/super.dir/super.cpp.o.requires

CMakeFiles/super.dir/super.cpp.o.provides: CMakeFiles/super.dir/super.cpp.o.requires
	$(MAKE) -f CMakeFiles/super.dir/build.make CMakeFiles/super.dir/super.cpp.o.provides.build
.PHONY : CMakeFiles/super.dir/super.cpp.o.provides

CMakeFiles/super.dir/super.cpp.o.provides.build: CMakeFiles/super.dir/super.cpp.o


# Object files for target super
super_OBJECTS = \
"CMakeFiles/super.dir/src/IOLoop.cpp.o" \
"CMakeFiles/super.dir/src/Message.cpp.o" \
"CMakeFiles/super.dir/src/Utils.cpp.o" \
"CMakeFiles/super.dir/src/Socket.cpp.o" \
"CMakeFiles/super.dir/src/File.cpp.o" \
"CMakeFiles/super.dir/src/IOHandler.cpp.o" \
"CMakeFiles/super.dir/super.cpp.o"

# External object files for target super
super_EXTERNAL_OBJECTS =

super: CMakeFiles/super.dir/src/IOLoop.cpp.o
super: CMakeFiles/super.dir/src/Message.cpp.o
super: CMakeFiles/super.dir/src/Utils.cpp.o
super: CMakeFiles/super.dir/src/Socket.cpp.o
super: CMakeFiles/super.dir/src/File.cpp.o
super: CMakeFiles/super.dir/src/IOHandler.cpp.o
super: CMakeFiles/super.dir/super.cpp.o
super: CMakeFiles/super.dir/build.make
super: CMakeFiles/super.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dumitru/ClionProjects/KaZaA/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable super"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/super.dir/link.txt --verbose=$(VERBOSE)
	/usr/bin/cmake -E copy /home/dumitru/ClionProjects/KaZaA/build/super /home/dumitru/ClionProjects/KaZaA/env/super/

# Rule to build all files generated by this target.
CMakeFiles/super.dir/build: super

.PHONY : CMakeFiles/super.dir/build

CMakeFiles/super.dir/requires: CMakeFiles/super.dir/src/IOLoop.cpp.o.requires
CMakeFiles/super.dir/requires: CMakeFiles/super.dir/src/Message.cpp.o.requires
CMakeFiles/super.dir/requires: CMakeFiles/super.dir/src/Utils.cpp.o.requires
CMakeFiles/super.dir/requires: CMakeFiles/super.dir/src/Socket.cpp.o.requires
CMakeFiles/super.dir/requires: CMakeFiles/super.dir/src/File.cpp.o.requires
CMakeFiles/super.dir/requires: CMakeFiles/super.dir/src/IOHandler.cpp.o.requires
CMakeFiles/super.dir/requires: CMakeFiles/super.dir/super.cpp.o.requires

.PHONY : CMakeFiles/super.dir/requires

CMakeFiles/super.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/super.dir/cmake_clean.cmake
.PHONY : CMakeFiles/super.dir/clean

CMakeFiles/super.dir/depend:
	cd /home/dumitru/ClionProjects/KaZaA/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dumitru/ClionProjects/KaZaA /home/dumitru/ClionProjects/KaZaA /home/dumitru/ClionProjects/KaZaA/build /home/dumitru/ClionProjects/KaZaA/build /home/dumitru/ClionProjects/KaZaA/build/CMakeFiles/super.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/super.dir/depend

