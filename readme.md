# Voltage

voltage is a game engine made with vulkan

## Building

Required programs for compiling

- Clang / LLVM
- Cmake
- Vulkan SDK

to setup cmake building run

```
cmake -B build -D CMAKE_C_COMPILER=clang -D CMAKE_EXPORT_COMPILE_COMMANDS=ON
```

to build run

```
cmake --build build
```
