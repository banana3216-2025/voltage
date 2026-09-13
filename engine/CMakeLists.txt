project(engine C)

# Find all C files EXCEPT your explicit platform directories first
file(GLOB_RECURSE ENGINE_SRCS 
    "src/containers/*.c"
    "src/core/*.c"
    "src/renderer/*.c"
)

# Append ONLY the correct platform layer file depending on the compilation target OS
if(WIN32)
    list(APPEND ENGINE_SRCS "src/platform/platform_win32.c")
else()
    list(APPEND ENGINE_SRCS "src/platform/platform_linux.c")
endif()

# Create the shared library target
add_library(engine SHARED ${ENGINE_SRCS})

target_compile_definitions(engine PRIVATE VEXPORT)
target_include_directories(engine PUBLIC src)

# Platform-specific linking logic
if(WIN32)
    # ws2_32 provides WSAStartup and networking implementations on Windows systems
    target_link_libraries(engine PRIVATE Vulkan::Vulkan user32 ws2_32)
else()
    find_package(PkgConfig REQUIRED)
    
    pkg_check_modules(X11 REQUIRED x11)
    pkg_check_modules(XCB REQUIRED xcb)
    pkg_check_modules(X11_XCB REQUIRED x11-xcb)

    target_include_directories(engine PRIVATE 
        ${X11_INCLUDE_DIRS} 
        ${XCB_INCLUDE_DIRS} 
        ${X11_XCB_INCLUDE_DIRS}
    )

    target_link_libraries(engine PRIVATE 
        Vulkan::Vulkan 
        ${X11_LIBRARIES} 
        ${XCB_LIBRARIES} 
        ${X11_XCB_LIBRARIES}
    )
endif()
