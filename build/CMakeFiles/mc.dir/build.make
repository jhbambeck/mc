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
CMAKE_SOURCE_DIR = /home/jake/Code/mc3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jake/Code/mc3/build

# Include any dependencies generated for this target.
include CMakeFiles/mc.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mc.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mc.dir/flags.make

CMakeFiles/mc.dir/main.cpp.o: CMakeFiles/mc.dir/flags.make
CMakeFiles/mc.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jake/Code/mc3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/mc.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mc.dir/main.cpp.o -c /home/jake/Code/mc3/main.cpp

CMakeFiles/mc.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mc.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jake/Code/mc3/main.cpp > CMakeFiles/mc.dir/main.cpp.i

CMakeFiles/mc.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mc.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jake/Code/mc3/main.cpp -o CMakeFiles/mc.dir/main.cpp.s

CMakeFiles/mc.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/mc.dir/main.cpp.o.requires

CMakeFiles/mc.dir/main.cpp.o.provides: CMakeFiles/mc.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/mc.dir/build.make CMakeFiles/mc.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/mc.dir/main.cpp.o.provides

CMakeFiles/mc.dir/main.cpp.o.provides.build: CMakeFiles/mc.dir/main.cpp.o


# Object files for target mc
mc_OBJECTS = \
"CMakeFiles/mc.dir/main.cpp.o"

# External object files for target mc
mc_EXTERNAL_OBJECTS =

mc: CMakeFiles/mc.dir/main.cpp.o
mc: CMakeFiles/mc.dir/build.make
mc: liblang.a
mc: /usr/lib/llvm-3.8/lib/libLLVMX86CodeGen.a
mc: /usr/lib/llvm-3.8/lib/libLLVMAsmPrinter.a
mc: /usr/lib/llvm-3.8/lib/libLLVMSelectionDAG.a
mc: /usr/lib/llvm-3.8/lib/libLLVMCodeGen.a
mc: /usr/lib/llvm-3.8/lib/libLLVMBitWriter.a
mc: /usr/lib/llvm-3.8/lib/libLLVMInstrumentation.a
mc: /usr/lib/llvm-3.8/lib/libLLVMProfileData.a
mc: /usr/lib/llvm-3.8/lib/libLLVMScalarOpts.a
mc: /usr/lib/llvm-3.8/lib/libLLVMInstCombine.a
mc: /usr/lib/llvm-3.8/lib/libLLVMTransformUtils.a
mc: /usr/lib/llvm-3.8/lib/libLLVMTarget.a
mc: /usr/lib/llvm-3.8/lib/libLLVMAnalysis.a
mc: /usr/lib/llvm-3.8/lib/libLLVMX86AsmParser.a
mc: /usr/lib/llvm-3.8/lib/libLLVMX86Desc.a
mc: /usr/lib/llvm-3.8/lib/libLLVMX86AsmPrinter.a
mc: /usr/lib/llvm-3.8/lib/libLLVMX86Utils.a
mc: /usr/lib/llvm-3.8/lib/libLLVMObject.a
mc: /usr/lib/llvm-3.8/lib/libLLVMMCParser.a
mc: /usr/lib/llvm-3.8/lib/libLLVMBitReader.a
mc: /usr/lib/llvm-3.8/lib/libLLVMCore.a
mc: /usr/lib/llvm-3.8/lib/libLLVMX86Disassembler.a
mc: /usr/lib/llvm-3.8/lib/libLLVMX86Info.a
mc: /usr/lib/llvm-3.8/lib/libLLVMMCDisassembler.a
mc: /usr/lib/llvm-3.8/lib/libLLVMMC.a
mc: /usr/lib/llvm-3.8/lib/libLLVMSupport.a
mc: CMakeFiles/mc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jake/Code/mc3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable mc"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mc.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mc.dir/build: mc

.PHONY : CMakeFiles/mc.dir/build

CMakeFiles/mc.dir/requires: CMakeFiles/mc.dir/main.cpp.o.requires

.PHONY : CMakeFiles/mc.dir/requires

CMakeFiles/mc.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mc.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mc.dir/clean

CMakeFiles/mc.dir/depend:
	cd /home/jake/Code/mc3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jake/Code/mc3 /home/jake/Code/mc3 /home/jake/Code/mc3/build /home/jake/Code/mc3/build /home/jake/Code/mc3/build/CMakeFiles/mc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mc.dir/depend

