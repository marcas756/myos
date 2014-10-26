#!/bin/bash

rm ./build -r
mkdir -p build/Release
mkdir -p build/Debug

cmake -E chdir build/Release cmake -G"Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ../../src
cmake -E chdir build/Debug cmake -G"Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug ../../src

 



