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
CMAKE_SOURCE_DIR = /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build

# Include any dependencies generated for this target.
include external/glfw-3.1.2/src/CMakeFiles/glfw.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include external/glfw-3.1.2/src/CMakeFiles/glfw.dir/compiler_depend.make

# Include the progress variables for this target.
include external/glfw-3.1.2/src/CMakeFiles/glfw.dir/progress.make

# Include the compile flags for this target's objects.
include external/glfw-3.1.2/src/CMakeFiles/glfw.dir/flags.make

external/glfw-3.1.2/src/CMakeFiles/glfw.dir/context.c.o: external/glfw-3.1.2/src/CMakeFiles/glfw.dir/flags.make
external/glfw-3.1.2/src/CMakeFiles/glfw.dir/context.c.o: ../external/glfw-3.1.2/src/context.c
external/glfw-3.1.2/src/CMakeFiles/glfw.dir/context.c.o: external/glfw-3.1.2/src/CMakeFiles/glfw.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object external/glfw-3.1.2/src/CMakeFiles/glfw.dir/context.c.o"
	cd /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build/external/glfw-3.1.2/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT external/glfw-3.1.2/src/CMakeFiles/glfw.dir/context.c.o -MF CMakeFiles/glfw.dir/context.c.o.d -o CMakeFiles/glfw.dir/context.c.o -c /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/external/glfw-3.1.2/src/context.c

external/glfw-3.1.2/src/CMakeFiles/glfw.dir/context.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glfw.dir/context.c.i"
	cd /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build/external/glfw-3.1.2/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/external/glfw-3.1.2/src/context.c > CMakeFiles/glfw.dir/context.c.i

external/glfw-3.1.2/src/CMakeFiles/glfw.dir/context.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glfw.dir/context.c.s"
	cd /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build/external/glfw-3.1.2/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/external/glfw-3.1.2/src/context.c -o CMakeFiles/glfw.dir/context.c.s

external/glfw-3.1.2/src/CMakeFiles/glfw.dir/init.c.o: external/glfw-3.1.2/src/CMakeFiles/glfw.dir/flags.make
external/glfw-3.1.2/src/CMakeFiles/glfw.dir/init.c.o: ../external/glfw-3.1.2/src/init.c
external/glfw-3.1.2/src/CMakeFiles/glfw.dir/init.c.o: external/glfw-3.1.2/src/CMakeFiles/glfw.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object external/glfw-3.1.2/src/CMakeFiles/glfw.dir/init.c.o"
	cd /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build/external/glfw-3.1.2/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT external/glfw-3.1.2/src/CMakeFiles/glfw.dir/init.c.o -MF CMakeFiles/glfw.dir/init.c.o.d -o CMakeFiles/glfw.dir/init.c.o -c /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/external/glfw-3.1.2/src/init.c

external/glfw-3.1.2/src/CMakeFiles/glfw.dir/init.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glfw.dir/init.c.i"
	cd /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build/external/glfw-3.1.2/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/external/glfw-3.1.2/src/init.c > CMakeFiles/glfw.dir/init.c.i

external/glfw-3.1.2/src/CMakeFiles/glfw.dir/init.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glfw.dir/init.c.s"
	cd /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build/external/glfw-3.1.2/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/external/glfw-3.1.2/src/init.c -o CMakeFiles/glfw.dir/init.c.s

external/glfw-3.1.2/src/CMakeFiles/glfw.dir/input.c.o: external/glfw-3.1.2/src/CMakeFiles/glfw.dir/flags.make
external/glfw-3.1.2/src/CMakeFiles/glfw.dir/input.c.o: ../external/glfw-3.1.2/src/input.c
external/glfw-3.1.2/src/CMakeFiles/glfw.dir/input.c.o: external/glfw-3.1.2/src/CMakeFiles/glfw.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object external/glfw-3.1.2/src/CMakeFiles/glfw.dir/input.c.o"
	cd /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build/external/glfw-3.1.2/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT external/glfw-3.1.2/src/CMakeFiles/glfw.dir/input.c.o -MF CMakeFiles/glfw.dir/input.c.o.d -o CMakeFiles/glfw.dir/input.c.o -c /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/external/glfw-3.1.2/src/input.c

external/glfw-3.1.2/src/CMakeFiles/glfw.dir/input.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glfw.dir/input.c.i"
	cd /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build/external/glfw-3.1.2/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/external/glfw-3.1.2/src/input.c > CMakeFiles/glfw.dir/input.c.i

external/glfw-3.1.2/src/CMakeFiles/glfw.dir/input.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glfw.dir/input.c.s"
	cd /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build/external/glfw-3.1.2/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/external/glfw-3.1.2/src/input.c -o CMakeFiles/glfw.dir/input.c.s

external/glfw-3.1.2/src/CMakeFiles/glfw.dir/monitor.c.o: external/glfw-3.1.2/src/CMakeFiles/glfw.dir/flags.make
external/glfw-3.1.2/src/CMakeFiles/glfw.dir/monitor.c.o: ../external/glfw-3.1.2/src/monitor.c
external/glfw-3.1.2/src/CMakeFiles/glfw.dir/monitor.c.o: external/glfw-3.1.2/src/CMakeFiles/glfw.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object external/glfw-3.1.2/src/CMakeFiles/glfw.dir/monitor.c.o"
	cd /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build/external/glfw-3.1.2/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT external/glfw-3.1.2/src/CMakeFiles/glfw.dir/monitor.c.o -MF CMakeFiles/glfw.dir/monitor.c.o.d -o CMakeFiles/glfw.dir/monitor.c.o -c /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/external/glfw-3.1.2/src/monitor.c

external/glfw-3.1.2/src/CMakeFiles/glfw.dir/monitor.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glfw.dir/monitor.c.i"
	cd /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build/external/glfw-3.1.2/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/external/glfw-3.1.2/src/monitor.c > CMakeFiles/glfw.dir/monitor.c.i

external/glfw-3.1.2/src/CMakeFiles/glfw.dir/monitor.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glfw.dir/monitor.c.s"
	cd /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build/external/glfw-3.1.2/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/external/glfw-3.1.2/src/monitor.c -o CMakeFiles/glfw.dir/monitor.c.s

external/glfw-3.1.2/src/CMakeFiles/glfw.dir/window.c.o: external/glfw-3.1.2/src/CMakeFiles/glfw.dir/flags.make
external/glfw-3.1.2/src/CMakeFiles/glfw.dir/window.c.o: ../external/glfw-3.1.2/src/window.c
external/glfw-3.1.2/src/CMakeFiles/glfw.dir/window.c.o: external/glfw-3.1.2/src/CMakeFiles/glfw.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object external/glfw-3.1.2/src/CMakeFiles/glfw.dir/window.c.o"
	cd /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build/external/glfw-3.1.2/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT external/glfw-3.1.2/src/CMakeFiles/glfw.dir/window.c.o -MF CMakeFiles/glfw.dir/window.c.o.d -o CMakeFiles/glfw.dir/window.c.o -c /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/external/glfw-3.1.2/src/window.c

external/glfw-3.1.2/src/CMakeFiles/glfw.dir/window.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glfw.dir/window.c.i"
	cd /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build/external/glfw-3.1.2/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/external/glfw-3.1.2/src/window.c > CMakeFiles/glfw.dir/window.c.i

external/glfw-3.1.2/src/CMakeFiles/glfw.dir/window.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glfw.dir/window.c.s"
	cd /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build/external/glfw-3.1.2/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/external/glfw-3.1.2/src/window.c -o CMakeFiles/glfw.dir/window.c.s

external/glfw-3.1.2/src/CMakeFiles/glfw.dir/x11_init.c.o: external/glfw-3.1.2/src/CMakeFiles/glfw.dir/flags.make
external/glfw-3.1.2/src/CMakeFiles/glfw.dir/x11_init.c.o: ../external/glfw-3.1.2/src/x11_init.c
external/glfw-3.1.2/src/CMakeFiles/glfw.dir/x11_init.c.o: external/glfw-3.1.2/src/CMakeFiles/glfw.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object external/glfw-3.1.2/src/CMakeFiles/glfw.dir/x11_init.c.o"
	cd /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build/external/glfw-3.1.2/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT external/glfw-3.1.2/src/CMakeFiles/glfw.dir/x11_init.c.o -MF CMakeFiles/glfw.dir/x11_init.c.o.d -o CMakeFiles/glfw.dir/x11_init.c.o -c /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/external/glfw-3.1.2/src/x11_init.c

external/glfw-3.1.2/src/CMakeFiles/glfw.dir/x11_init.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glfw.dir/x11_init.c.i"
	cd /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build/external/glfw-3.1.2/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/external/glfw-3.1.2/src/x11_init.c > CMakeFiles/glfw.dir/x11_init.c.i

external/glfw-3.1.2/src/CMakeFiles/glfw.dir/x11_init.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glfw.dir/x11_init.c.s"
	cd /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build/external/glfw-3.1.2/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/external/glfw-3.1.2/src/x11_init.c -o CMakeFiles/glfw.dir/x11_init.c.s

external/glfw-3.1.2/src/CMakeFiles/glfw.dir/x11_monitor.c.o: external/glfw-3.1.2/src/CMakeFiles/glfw.dir/flags.make
external/glfw-3.1.2/src/CMakeFiles/glfw.dir/x11_monitor.c.o: ../external/glfw-3.1.2/src/x11_monitor.c
external/glfw-3.1.2/src/CMakeFiles/glfw.dir/x11_monitor.c.o: external/glfw-3.1.2/src/CMakeFiles/glfw.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object external/glfw-3.1.2/src/CMakeFiles/glfw.dir/x11_monitor.c.o"
	cd /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build/external/glfw-3.1.2/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT external/glfw-3.1.2/src/CMakeFiles/glfw.dir/x11_monitor.c.o -MF CMakeFiles/glfw.dir/x11_monitor.c.o.d -o CMakeFiles/glfw.dir/x11_monitor.c.o -c /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/external/glfw-3.1.2/src/x11_monitor.c

external/glfw-3.1.2/src/CMakeFiles/glfw.dir/x11_monitor.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glfw.dir/x11_monitor.c.i"
	cd /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build/external/glfw-3.1.2/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/external/glfw-3.1.2/src/x11_monitor.c > CMakeFiles/glfw.dir/x11_monitor.c.i

external/glfw-3.1.2/src/CMakeFiles/glfw.dir/x11_monitor.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glfw.dir/x11_monitor.c.s"
	cd /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build/external/glfw-3.1.2/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/external/glfw-3.1.2/src/x11_monitor.c -o CMakeFiles/glfw.dir/x11_monitor.c.s

external/glfw-3.1.2/src/CMakeFiles/glfw.dir/x11_window.c.o: external/glfw-3.1.2/src/CMakeFiles/glfw.dir/flags.make
external/glfw-3.1.2/src/CMakeFiles/glfw.dir/x11_window.c.o: ../external/glfw-3.1.2/src/x11_window.c
external/glfw-3.1.2/src/CMakeFiles/glfw.dir/x11_window.c.o: external/glfw-3.1.2/src/CMakeFiles/glfw.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object external/glfw-3.1.2/src/CMakeFiles/glfw.dir/x11_window.c.o"
	cd /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build/external/glfw-3.1.2/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT external/glfw-3.1.2/src/CMakeFiles/glfw.dir/x11_window.c.o -MF CMakeFiles/glfw.dir/x11_window.c.o.d -o CMakeFiles/glfw.dir/x11_window.c.o -c /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/external/glfw-3.1.2/src/x11_window.c

external/glfw-3.1.2/src/CMakeFiles/glfw.dir/x11_window.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glfw.dir/x11_window.c.i"
	cd /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build/external/glfw-3.1.2/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/external/glfw-3.1.2/src/x11_window.c > CMakeFiles/glfw.dir/x11_window.c.i

external/glfw-3.1.2/src/CMakeFiles/glfw.dir/x11_window.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glfw.dir/x11_window.c.s"
	cd /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build/external/glfw-3.1.2/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/external/glfw-3.1.2/src/x11_window.c -o CMakeFiles/glfw.dir/x11_window.c.s

external/glfw-3.1.2/src/CMakeFiles/glfw.dir/xkb_unicode.c.o: external/glfw-3.1.2/src/CMakeFiles/glfw.dir/flags.make
external/glfw-3.1.2/src/CMakeFiles/glfw.dir/xkb_unicode.c.o: ../external/glfw-3.1.2/src/xkb_unicode.c
external/glfw-3.1.2/src/CMakeFiles/glfw.dir/xkb_unicode.c.o: external/glfw-3.1.2/src/CMakeFiles/glfw.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object external/glfw-3.1.2/src/CMakeFiles/glfw.dir/xkb_unicode.c.o"
	cd /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build/external/glfw-3.1.2/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT external/glfw-3.1.2/src/CMakeFiles/glfw.dir/xkb_unicode.c.o -MF CMakeFiles/glfw.dir/xkb_unicode.c.o.d -o CMakeFiles/glfw.dir/xkb_unicode.c.o -c /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/external/glfw-3.1.2/src/xkb_unicode.c

external/glfw-3.1.2/src/CMakeFiles/glfw.dir/xkb_unicode.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glfw.dir/xkb_unicode.c.i"
	cd /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build/external/glfw-3.1.2/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/external/glfw-3.1.2/src/xkb_unicode.c > CMakeFiles/glfw.dir/xkb_unicode.c.i

external/glfw-3.1.2/src/CMakeFiles/glfw.dir/xkb_unicode.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glfw.dir/xkb_unicode.c.s"
	cd /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build/external/glfw-3.1.2/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/external/glfw-3.1.2/src/xkb_unicode.c -o CMakeFiles/glfw.dir/xkb_unicode.c.s

external/glfw-3.1.2/src/CMakeFiles/glfw.dir/linux_joystick.c.o: external/glfw-3.1.2/src/CMakeFiles/glfw.dir/flags.make
external/glfw-3.1.2/src/CMakeFiles/glfw.dir/linux_joystick.c.o: ../external/glfw-3.1.2/src/linux_joystick.c
external/glfw-3.1.2/src/CMakeFiles/glfw.dir/linux_joystick.c.o: external/glfw-3.1.2/src/CMakeFiles/glfw.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object external/glfw-3.1.2/src/CMakeFiles/glfw.dir/linux_joystick.c.o"
	cd /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build/external/glfw-3.1.2/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT external/glfw-3.1.2/src/CMakeFiles/glfw.dir/linux_joystick.c.o -MF CMakeFiles/glfw.dir/linux_joystick.c.o.d -o CMakeFiles/glfw.dir/linux_joystick.c.o -c /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/external/glfw-3.1.2/src/linux_joystick.c

external/glfw-3.1.2/src/CMakeFiles/glfw.dir/linux_joystick.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glfw.dir/linux_joystick.c.i"
	cd /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build/external/glfw-3.1.2/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/external/glfw-3.1.2/src/linux_joystick.c > CMakeFiles/glfw.dir/linux_joystick.c.i

external/glfw-3.1.2/src/CMakeFiles/glfw.dir/linux_joystick.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glfw.dir/linux_joystick.c.s"
	cd /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build/external/glfw-3.1.2/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/external/glfw-3.1.2/src/linux_joystick.c -o CMakeFiles/glfw.dir/linux_joystick.c.s

external/glfw-3.1.2/src/CMakeFiles/glfw.dir/posix_time.c.o: external/glfw-3.1.2/src/CMakeFiles/glfw.dir/flags.make
external/glfw-3.1.2/src/CMakeFiles/glfw.dir/posix_time.c.o: ../external/glfw-3.1.2/src/posix_time.c
external/glfw-3.1.2/src/CMakeFiles/glfw.dir/posix_time.c.o: external/glfw-3.1.2/src/CMakeFiles/glfw.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building C object external/glfw-3.1.2/src/CMakeFiles/glfw.dir/posix_time.c.o"
	cd /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build/external/glfw-3.1.2/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT external/glfw-3.1.2/src/CMakeFiles/glfw.dir/posix_time.c.o -MF CMakeFiles/glfw.dir/posix_time.c.o.d -o CMakeFiles/glfw.dir/posix_time.c.o -c /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/external/glfw-3.1.2/src/posix_time.c

external/glfw-3.1.2/src/CMakeFiles/glfw.dir/posix_time.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glfw.dir/posix_time.c.i"
	cd /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build/external/glfw-3.1.2/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/external/glfw-3.1.2/src/posix_time.c > CMakeFiles/glfw.dir/posix_time.c.i

external/glfw-3.1.2/src/CMakeFiles/glfw.dir/posix_time.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glfw.dir/posix_time.c.s"
	cd /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build/external/glfw-3.1.2/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/external/glfw-3.1.2/src/posix_time.c -o CMakeFiles/glfw.dir/posix_time.c.s

external/glfw-3.1.2/src/CMakeFiles/glfw.dir/posix_tls.c.o: external/glfw-3.1.2/src/CMakeFiles/glfw.dir/flags.make
external/glfw-3.1.2/src/CMakeFiles/glfw.dir/posix_tls.c.o: ../external/glfw-3.1.2/src/posix_tls.c
external/glfw-3.1.2/src/CMakeFiles/glfw.dir/posix_tls.c.o: external/glfw-3.1.2/src/CMakeFiles/glfw.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building C object external/glfw-3.1.2/src/CMakeFiles/glfw.dir/posix_tls.c.o"
	cd /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build/external/glfw-3.1.2/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT external/glfw-3.1.2/src/CMakeFiles/glfw.dir/posix_tls.c.o -MF CMakeFiles/glfw.dir/posix_tls.c.o.d -o CMakeFiles/glfw.dir/posix_tls.c.o -c /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/external/glfw-3.1.2/src/posix_tls.c

external/glfw-3.1.2/src/CMakeFiles/glfw.dir/posix_tls.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glfw.dir/posix_tls.c.i"
	cd /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build/external/glfw-3.1.2/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/external/glfw-3.1.2/src/posix_tls.c > CMakeFiles/glfw.dir/posix_tls.c.i

external/glfw-3.1.2/src/CMakeFiles/glfw.dir/posix_tls.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glfw.dir/posix_tls.c.s"
	cd /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build/external/glfw-3.1.2/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/external/glfw-3.1.2/src/posix_tls.c -o CMakeFiles/glfw.dir/posix_tls.c.s

external/glfw-3.1.2/src/CMakeFiles/glfw.dir/glx_context.c.o: external/glfw-3.1.2/src/CMakeFiles/glfw.dir/flags.make
external/glfw-3.1.2/src/CMakeFiles/glfw.dir/glx_context.c.o: ../external/glfw-3.1.2/src/glx_context.c
external/glfw-3.1.2/src/CMakeFiles/glfw.dir/glx_context.c.o: external/glfw-3.1.2/src/CMakeFiles/glfw.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building C object external/glfw-3.1.2/src/CMakeFiles/glfw.dir/glx_context.c.o"
	cd /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build/external/glfw-3.1.2/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT external/glfw-3.1.2/src/CMakeFiles/glfw.dir/glx_context.c.o -MF CMakeFiles/glfw.dir/glx_context.c.o.d -o CMakeFiles/glfw.dir/glx_context.c.o -c /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/external/glfw-3.1.2/src/glx_context.c

external/glfw-3.1.2/src/CMakeFiles/glfw.dir/glx_context.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glfw.dir/glx_context.c.i"
	cd /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build/external/glfw-3.1.2/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/external/glfw-3.1.2/src/glx_context.c > CMakeFiles/glfw.dir/glx_context.c.i

external/glfw-3.1.2/src/CMakeFiles/glfw.dir/glx_context.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glfw.dir/glx_context.c.s"
	cd /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build/external/glfw-3.1.2/src && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/external/glfw-3.1.2/src/glx_context.c -o CMakeFiles/glfw.dir/glx_context.c.s

# Object files for target glfw
glfw_OBJECTS = \
"CMakeFiles/glfw.dir/context.c.o" \
"CMakeFiles/glfw.dir/init.c.o" \
"CMakeFiles/glfw.dir/input.c.o" \
"CMakeFiles/glfw.dir/monitor.c.o" \
"CMakeFiles/glfw.dir/window.c.o" \
"CMakeFiles/glfw.dir/x11_init.c.o" \
"CMakeFiles/glfw.dir/x11_monitor.c.o" \
"CMakeFiles/glfw.dir/x11_window.c.o" \
"CMakeFiles/glfw.dir/xkb_unicode.c.o" \
"CMakeFiles/glfw.dir/linux_joystick.c.o" \
"CMakeFiles/glfw.dir/posix_time.c.o" \
"CMakeFiles/glfw.dir/posix_tls.c.o" \
"CMakeFiles/glfw.dir/glx_context.c.o"

# External object files for target glfw
glfw_EXTERNAL_OBJECTS =

external/glfw-3.1.2/src/libglfw3.a: external/glfw-3.1.2/src/CMakeFiles/glfw.dir/context.c.o
external/glfw-3.1.2/src/libglfw3.a: external/glfw-3.1.2/src/CMakeFiles/glfw.dir/init.c.o
external/glfw-3.1.2/src/libglfw3.a: external/glfw-3.1.2/src/CMakeFiles/glfw.dir/input.c.o
external/glfw-3.1.2/src/libglfw3.a: external/glfw-3.1.2/src/CMakeFiles/glfw.dir/monitor.c.o
external/glfw-3.1.2/src/libglfw3.a: external/glfw-3.1.2/src/CMakeFiles/glfw.dir/window.c.o
external/glfw-3.1.2/src/libglfw3.a: external/glfw-3.1.2/src/CMakeFiles/glfw.dir/x11_init.c.o
external/glfw-3.1.2/src/libglfw3.a: external/glfw-3.1.2/src/CMakeFiles/glfw.dir/x11_monitor.c.o
external/glfw-3.1.2/src/libglfw3.a: external/glfw-3.1.2/src/CMakeFiles/glfw.dir/x11_window.c.o
external/glfw-3.1.2/src/libglfw3.a: external/glfw-3.1.2/src/CMakeFiles/glfw.dir/xkb_unicode.c.o
external/glfw-3.1.2/src/libglfw3.a: external/glfw-3.1.2/src/CMakeFiles/glfw.dir/linux_joystick.c.o
external/glfw-3.1.2/src/libglfw3.a: external/glfw-3.1.2/src/CMakeFiles/glfw.dir/posix_time.c.o
external/glfw-3.1.2/src/libglfw3.a: external/glfw-3.1.2/src/CMakeFiles/glfw.dir/posix_tls.c.o
external/glfw-3.1.2/src/libglfw3.a: external/glfw-3.1.2/src/CMakeFiles/glfw.dir/glx_context.c.o
external/glfw-3.1.2/src/libglfw3.a: external/glfw-3.1.2/src/CMakeFiles/glfw.dir/build.make
external/glfw-3.1.2/src/libglfw3.a: external/glfw-3.1.2/src/CMakeFiles/glfw.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Linking C static library libglfw3.a"
	cd /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build/external/glfw-3.1.2/src && $(CMAKE_COMMAND) -P CMakeFiles/glfw.dir/cmake_clean_target.cmake
	cd /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build/external/glfw-3.1.2/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/glfw.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
external/glfw-3.1.2/src/CMakeFiles/glfw.dir/build: external/glfw-3.1.2/src/libglfw3.a
.PHONY : external/glfw-3.1.2/src/CMakeFiles/glfw.dir/build

external/glfw-3.1.2/src/CMakeFiles/glfw.dir/clean:
	cd /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build/external/glfw-3.1.2/src && $(CMAKE_COMMAND) -P CMakeFiles/glfw.dir/cmake_clean.cmake
.PHONY : external/glfw-3.1.2/src/CMakeFiles/glfw.dir/clean

external/glfw-3.1.2/src/CMakeFiles/glfw.dir/depend:
	cd /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/external/glfw-3.1.2/src /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build/external/glfw-3.1.2/src /home/fabien/Documents/FDS/M1/Moteur_de_jeux/TP1_code/build/external/glfw-3.1.2/src/CMakeFiles/glfw.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : external/glfw-3.1.2/src/CMakeFiles/glfw.dir/depend

