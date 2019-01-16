#!/bin/bash

rm ./build -rf
#mkdir -p build/Release
mkdir -p build/Debug
#mkdir -p build/C64
#mkdir -p build/Unix

#cmake -E chdir build/Release cmake -G"Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ../../src
cmake -E chdir build/Debug cmake -G"Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug ../../project
# cmake -E chdir build/C64 cmake -G"Eclipse CDT4 - Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=../../cc65-toolchain.cmake ../../src


#cmake -E chdir build/Unix cmake -G"Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug ../../src
 



