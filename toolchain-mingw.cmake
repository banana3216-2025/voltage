set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR x86_64)

# Set the MinGW Compilers
set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)

# Tell CMake where the local Windows Vulkan SDK proxy root directory is located
set(Vulkan_ROOT "${CMAKE_SOURCE_DIR}/vulkan_windows_sdk")
set(ENV{VULKAN_SDK} "${CMAKE_SOURCE_DIR}/vulkan_windows_sdk")

add_compile_options(-Wno-error=format-security)

# Enforce clean cross-compilation search constraints
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
