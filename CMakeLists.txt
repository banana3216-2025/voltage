cmake_minimum_required(VERSION 3.20)
project(VulkanGameEngine C)

# Set common compiler options for Clang on Windows
if(CMAKE_C_COMPILER_ID MATCHES "Clang")
    add_compile_options(-g -fdeclspec -Wno-format -Wno-format-security)
endif()

# Global macro definitions from your Makefiles
add_compile_definitions(_DEBUG)

# Output all compiled binaries directly to the root /bin folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Discover and configure Vulkan SDK
find_package(Vulkan REQUIRED)

# Add subdirectories (replaces root Makefile targets)
add_subdirectory(engine)
add_subdirectory(testbed)

