# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/fabien/Documents/FDS/M1/Moteur_de_jeux/Projet_code

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/fabien/Documents/FDS/M1/Moteur_de_jeux/Projet_code/build

# Include any dependencies generated for this target.
include CMakeFiles/Projet.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Projet.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Projet.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Projet.dir/flags.make

CMakeFiles/Projet.dir/Projet/Projet.cpp.o: CMakeFiles/Projet.dir/flags.make
CMakeFiles/Projet.dir/Projet/Projet.cpp.o: ../Projet/Projet.cpp
CMakeFiles/Projet.dir/Projet/Projet.cpp.o: CMakeFiles/Projet.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/fabien/Documents/FDS/M1/Moteur_de_jeux/Projet_code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Projet.dir/Projet/Projet.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Projet.dir/Projet/Projet.cpp.o -MF CMakeFiles/Projet.dir/Projet/Projet.cpp.o.d -o CMakeFiles/Projet.dir/Projet/Projet.cpp.o -c /home/fabien/Documents/FDS/M1/Moteur_de_jeux/Projet_code/Projet/Projet.cpp

CMakeFiles/Projet.dir/Projet/Projet.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Projet.dir/Projet/Projet.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/fabien/Documents/FDS/M1/Moteur_de_jeux/Projet_code/Projet/Projet.cpp > CMakeFiles/Projet.dir/Projet/Projet.cpp.i

CMakeFiles/Projet.dir/Projet/Projet.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Projet.dir/Projet/Projet.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/fabien/Documents/FDS/M1/Moteur_de_jeux/Projet_code/Projet/Projet.cpp -o CMakeFiles/Projet.dir/Projet/Projet.cpp.s

CMakeFiles/Projet.dir/common/shader.cpp.o: CMakeFiles/Projet.dir/flags.make
CMakeFiles/Projet.dir/common/shader.cpp.o: ../common/shader.cpp
CMakeFiles/Projet.dir/common/shader.cpp.o: CMakeFiles/Projet.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/fabien/Documents/FDS/M1/Moteur_de_jeux/Projet_code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Projet.dir/common/shader.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Projet.dir/common/shader.cpp.o -MF CMakeFiles/Projet.dir/common/shader.cpp.o.d -o CMakeFiles/Projet.dir/common/shader.cpp.o -c /home/fabien/Documents/FDS/M1/Moteur_de_jeux/Projet_code/common/shader.cpp

CMakeFiles/Projet.dir/common/shader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Projet.dir/common/shader.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/fabien/Documents/FDS/M1/Moteur_de_jeux/Projet_code/common/shader.cpp > CMakeFiles/Projet.dir/common/shader.cpp.i

CMakeFiles/Projet.dir/common/shader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Projet.dir/common/shader.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/fabien/Documents/FDS/M1/Moteur_de_jeux/Projet_code/common/shader.cpp -o CMakeFiles/Projet.dir/common/shader.cpp.s

CMakeFiles/Projet.dir/common/controls.cpp.o: CMakeFiles/Projet.dir/flags.make
CMakeFiles/Projet.dir/common/controls.cpp.o: ../common/controls.cpp
CMakeFiles/Projet.dir/common/controls.cpp.o: CMakeFiles/Projet.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/fabien/Documents/FDS/M1/Moteur_de_jeux/Projet_code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Projet.dir/common/controls.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Projet.dir/common/controls.cpp.o -MF CMakeFiles/Projet.dir/common/controls.cpp.o.d -o CMakeFiles/Projet.dir/common/controls.cpp.o -c /home/fabien/Documents/FDS/M1/Moteur_de_jeux/Projet_code/common/controls.cpp

CMakeFiles/Projet.dir/common/controls.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Projet.dir/common/controls.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/fabien/Documents/FDS/M1/Moteur_de_jeux/Projet_code/common/controls.cpp > CMakeFiles/Projet.dir/common/controls.cpp.i

CMakeFiles/Projet.dir/common/controls.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Projet.dir/common/controls.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/fabien/Documents/FDS/M1/Moteur_de_jeux/Projet_code/common/controls.cpp -o CMakeFiles/Projet.dir/common/controls.cpp.s

CMakeFiles/Projet.dir/common/texture.cpp.o: CMakeFiles/Projet.dir/flags.make
CMakeFiles/Projet.dir/common/texture.cpp.o: ../common/texture.cpp
CMakeFiles/Projet.dir/common/texture.cpp.o: CMakeFiles/Projet.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/fabien/Documents/FDS/M1/Moteur_de_jeux/Projet_code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Projet.dir/common/texture.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Projet.dir/common/texture.cpp.o -MF CMakeFiles/Projet.dir/common/texture.cpp.o.d -o CMakeFiles/Projet.dir/common/texture.cpp.o -c /home/fabien/Documents/FDS/M1/Moteur_de_jeux/Projet_code/common/texture.cpp

CMakeFiles/Projet.dir/common/texture.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Projet.dir/common/texture.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/fabien/Documents/FDS/M1/Moteur_de_jeux/Projet_code/common/texture.cpp > CMakeFiles/Projet.dir/common/texture.cpp.i

CMakeFiles/Projet.dir/common/texture.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Projet.dir/common/texture.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/fabien/Documents/FDS/M1/Moteur_de_jeux/Projet_code/common/texture.cpp -o CMakeFiles/Projet.dir/common/texture.cpp.s

CMakeFiles/Projet.dir/common/objloader.cpp.o: CMakeFiles/Projet.dir/flags.make
CMakeFiles/Projet.dir/common/objloader.cpp.o: ../common/objloader.cpp
CMakeFiles/Projet.dir/common/objloader.cpp.o: CMakeFiles/Projet.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/fabien/Documents/FDS/M1/Moteur_de_jeux/Projet_code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/Projet.dir/common/objloader.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Projet.dir/common/objloader.cpp.o -MF CMakeFiles/Projet.dir/common/objloader.cpp.o.d -o CMakeFiles/Projet.dir/common/objloader.cpp.o -c /home/fabien/Documents/FDS/M1/Moteur_de_jeux/Projet_code/common/objloader.cpp

CMakeFiles/Projet.dir/common/objloader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Projet.dir/common/objloader.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/fabien/Documents/FDS/M1/Moteur_de_jeux/Projet_code/common/objloader.cpp > CMakeFiles/Projet.dir/common/objloader.cpp.i

CMakeFiles/Projet.dir/common/objloader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Projet.dir/common/objloader.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/fabien/Documents/FDS/M1/Moteur_de_jeux/Projet_code/common/objloader.cpp -o CMakeFiles/Projet.dir/common/objloader.cpp.s

CMakeFiles/Projet.dir/common/text2D.cpp.o: CMakeFiles/Projet.dir/flags.make
CMakeFiles/Projet.dir/common/text2D.cpp.o: ../common/text2D.cpp
CMakeFiles/Projet.dir/common/text2D.cpp.o: CMakeFiles/Projet.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/fabien/Documents/FDS/M1/Moteur_de_jeux/Projet_code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/Projet.dir/common/text2D.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Projet.dir/common/text2D.cpp.o -MF CMakeFiles/Projet.dir/common/text2D.cpp.o.d -o CMakeFiles/Projet.dir/common/text2D.cpp.o -c /home/fabien/Documents/FDS/M1/Moteur_de_jeux/Projet_code/common/text2D.cpp

CMakeFiles/Projet.dir/common/text2D.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Projet.dir/common/text2D.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/fabien/Documents/FDS/M1/Moteur_de_jeux/Projet_code/common/text2D.cpp > CMakeFiles/Projet.dir/common/text2D.cpp.i

CMakeFiles/Projet.dir/common/text2D.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Projet.dir/common/text2D.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/fabien/Documents/FDS/M1/Moteur_de_jeux/Projet_code/common/text2D.cpp -o CMakeFiles/Projet.dir/common/text2D.cpp.s

CMakeFiles/Projet.dir/common/vboindexer.cpp.o: CMakeFiles/Projet.dir/flags.make
CMakeFiles/Projet.dir/common/vboindexer.cpp.o: ../common/vboindexer.cpp
CMakeFiles/Projet.dir/common/vboindexer.cpp.o: CMakeFiles/Projet.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/fabien/Documents/FDS/M1/Moteur_de_jeux/Projet_code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/Projet.dir/common/vboindexer.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Projet.dir/common/vboindexer.cpp.o -MF CMakeFiles/Projet.dir/common/vboindexer.cpp.o.d -o CMakeFiles/Projet.dir/common/vboindexer.cpp.o -c /home/fabien/Documents/FDS/M1/Moteur_de_jeux/Projet_code/common/vboindexer.cpp

CMakeFiles/Projet.dir/common/vboindexer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Projet.dir/common/vboindexer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/fabien/Documents/FDS/M1/Moteur_de_jeux/Projet_code/common/vboindexer.cpp > CMakeFiles/Projet.dir/common/vboindexer.cpp.i

CMakeFiles/Projet.dir/common/vboindexer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Projet.dir/common/vboindexer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/fabien/Documents/FDS/M1/Moteur_de_jeux/Projet_code/common/vboindexer.cpp -o CMakeFiles/Projet.dir/common/vboindexer.cpp.s

# Object files for target Projet
Projet_OBJECTS = \
"CMakeFiles/Projet.dir/Projet/Projet.cpp.o" \
"CMakeFiles/Projet.dir/common/shader.cpp.o" \
"CMakeFiles/Projet.dir/common/controls.cpp.o" \
"CMakeFiles/Projet.dir/common/texture.cpp.o" \
"CMakeFiles/Projet.dir/common/objloader.cpp.o" \
"CMakeFiles/Projet.dir/common/text2D.cpp.o" \
"CMakeFiles/Projet.dir/common/vboindexer.cpp.o"

# External object files for target Projet
Projet_EXTERNAL_OBJECTS =

Projet: CMakeFiles/Projet.dir/Projet/Projet.cpp.o
Projet: CMakeFiles/Projet.dir/common/shader.cpp.o
Projet: CMakeFiles/Projet.dir/common/controls.cpp.o
Projet: CMakeFiles/Projet.dir/common/texture.cpp.o
Projet: CMakeFiles/Projet.dir/common/objloader.cpp.o
Projet: CMakeFiles/Projet.dir/common/text2D.cpp.o
Projet: CMakeFiles/Projet.dir/common/vboindexer.cpp.o
Projet: CMakeFiles/Projet.dir/build.make
Projet: /usr/lib/x86_64-linux-gnu/libGL.so
Projet: /usr/lib/x86_64-linux-gnu/libGLU.so
Projet: external/glfw-3.1.2/src/libglfw3.a
Projet: external/libGLEW_1130.a
Projet: /usr/lib/x86_64-linux-gnu/libGL.so
Projet: /usr/lib/x86_64-linux-gnu/libGLU.so
Projet: external/glfw-3.1.2/src/libglfw3.a
Projet: external/libGLEW_1130.a
Projet: /usr/lib/x86_64-linux-gnu/librt.a
Projet: /usr/lib/x86_64-linux-gnu/libm.so
Projet: /usr/lib/x86_64-linux-gnu/libX11.so
Projet: /usr/lib/x86_64-linux-gnu/libXrandr.so
Projet: /usr/lib/x86_64-linux-gnu/libXinerama.so
Projet: /usr/lib/x86_64-linux-gnu/libXi.so
Projet: /usr/lib/x86_64-linux-gnu/libXxf86vm.so
Projet: /usr/lib/x86_64-linux-gnu/libXcursor.so
Projet: /usr/lib/x86_64-linux-gnu/librt.a
Projet: /usr/lib/x86_64-linux-gnu/libm.so
Projet: /usr/lib/x86_64-linux-gnu/libX11.so
Projet: /usr/lib/x86_64-linux-gnu/libXrandr.so
Projet: /usr/lib/x86_64-linux-gnu/libXinerama.so
Projet: /usr/lib/x86_64-linux-gnu/libXi.so
Projet: /usr/lib/x86_64-linux-gnu/libXxf86vm.so
Projet: /usr/lib/x86_64-linux-gnu/libXcursor.so
Projet: /usr/lib/x86_64-linux-gnu/libGL.so
Projet: /usr/lib/x86_64-linux-gnu/libGLU.so
Projet: /usr/lib/x86_64-linux-gnu/libGL.so
Projet: /usr/lib/x86_64-linux-gnu/libGLU.so
Projet: CMakeFiles/Projet.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/fabien/Documents/FDS/M1/Moteur_de_jeux/Projet_code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable Projet"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Projet.dir/link.txt --verbose=$(VERBOSE)
	/usr/bin/cmake -E copy /home/fabien/Documents/FDS/M1/Moteur_de_jeux/Projet_code/build/./Projet /home/fabien/Documents/FDS/M1/Moteur_de_jeux/Projet_code/Projet/

# Rule to build all files generated by this target.
CMakeFiles/Projet.dir/build: Projet
.PHONY : CMakeFiles/Projet.dir/build

CMakeFiles/Projet.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Projet.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Projet.dir/clean

CMakeFiles/Projet.dir/depend:
	cd /home/fabien/Documents/FDS/M1/Moteur_de_jeux/Projet_code/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/fabien/Documents/FDS/M1/Moteur_de_jeux/Projet_code /home/fabien/Documents/FDS/M1/Moteur_de_jeux/Projet_code /home/fabien/Documents/FDS/M1/Moteur_de_jeux/Projet_code/build /home/fabien/Documents/FDS/M1/Moteur_de_jeux/Projet_code/build /home/fabien/Documents/FDS/M1/Moteur_de_jeux/Projet_code/build/CMakeFiles/Projet.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Projet.dir/depend

