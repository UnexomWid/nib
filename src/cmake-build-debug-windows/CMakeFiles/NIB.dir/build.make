# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.15

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2019.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2019.2\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Data\Programs\C\NIB\src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Data\Programs\C\NIB\src\cmake-build-debug-windows

# Include any dependencies generated for this target.
include CMakeFiles/NIB.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/NIB.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/NIB.dir/flags.make

CMakeFiles/NIB.dir/main.c.obj: CMakeFiles/NIB.dir/flags.make
CMakeFiles/NIB.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Data\Programs\C\NIB\src\cmake-build-debug-windows\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/NIB.dir/main.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\NIB.dir\main.c.obj   -c D:\Data\Programs\C\NIB\src\main.c

CMakeFiles/NIB.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/NIB.dir/main.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\Data\Programs\C\NIB\src\main.c > CMakeFiles\NIB.dir\main.c.i

CMakeFiles/NIB.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/NIB.dir/main.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\Data\Programs\C\NIB\src\main.c -o CMakeFiles\NIB.dir\main.c.s

CMakeFiles/NIB.dir/nib.c.obj: CMakeFiles/NIB.dir/flags.make
CMakeFiles/NIB.dir/nib.c.obj: ../nib.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Data\Programs\C\NIB\src\cmake-build-debug-windows\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/NIB.dir/nib.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\NIB.dir\nib.c.obj   -c D:\Data\Programs\C\NIB\src\nib.c

CMakeFiles/NIB.dir/nib.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/NIB.dir/nib.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\Data\Programs\C\NIB\src\nib.c > CMakeFiles\NIB.dir\nib.c.i

CMakeFiles/NIB.dir/nib.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/NIB.dir/nib.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\Data\Programs\C\NIB\src\nib.c -o CMakeFiles\NIB.dir\nib.c.s

# Object files for target NIB
NIB_OBJECTS = \
"CMakeFiles/NIB.dir/main.c.obj" \
"CMakeFiles/NIB.dir/nib.c.obj"

# External object files for target NIB
NIB_EXTERNAL_OBJECTS =

NIB.exe: CMakeFiles/NIB.dir/main.c.obj
NIB.exe: CMakeFiles/NIB.dir/nib.c.obj
NIB.exe: CMakeFiles/NIB.dir/build.make
NIB.exe: CMakeFiles/NIB.dir/linklibs.rsp
NIB.exe: CMakeFiles/NIB.dir/objects1.rsp
NIB.exe: CMakeFiles/NIB.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Data\Programs\C\NIB\src\cmake-build-debug-windows\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable NIB.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\NIB.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/NIB.dir/build: NIB.exe

.PHONY : CMakeFiles/NIB.dir/build

CMakeFiles/NIB.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\NIB.dir\cmake_clean.cmake
.PHONY : CMakeFiles/NIB.dir/clean

CMakeFiles/NIB.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Data\Programs\C\NIB\src D:\Data\Programs\C\NIB\src D:\Data\Programs\C\NIB\src\cmake-build-debug-windows D:\Data\Programs\C\NIB\src\cmake-build-debug-windows D:\Data\Programs\C\NIB\src\cmake-build-debug-windows\CMakeFiles\NIB.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/NIB.dir/depend
