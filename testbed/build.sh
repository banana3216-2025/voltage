#!/usr/bin/env bash
# Build script for testbed
set echo on

mkdir -p ../bin

# Get a list of all the .c files.
cFilenames=$(find . -type f -name "*.c")

# echo "Files:" $cFilenames

assembly="testbed"
# FIXED: Added formatting silence flags along with non-optimization triggers
compilerFlags="-g -fdeclspec -fPIC -O0 -include ../engine/src/core/logger.h -Wno-format -Wno-format-security"
includeFlags="-Isrc -I../engine/src"
linkerFlags="-L../bin -lengine -Wl,-rpath,."
defines="-D_DEBUG -DKIMPORT"

echo "Building $assembly..."
clang $cFilenames $compilerFlags -o ../bin/$assembly $defines $includeFlags $linkerFlags