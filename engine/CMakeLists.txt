project(engine C)

# Find all C files recursively
file(GLOB_RECURSE ENGINE_SRCS "src/*.c")

# Create the shared library target (libengine.so)
add_library(engine SHARED ${ENGINE_SRCS})

# Compile definitions
target_compile_definitions(engine PRIVATE VEXPORT)

# Include paths
target_include_directories(engine PUBLIC src)

# Platform-specific linking logic
if(WIN32)
    # Windows specific directories and libraries
    target_link_directories(engine PRIVATE $ENV{VULKAN_SDK}/lib)
    target_link_libraries(engine PRIVATE Vulkan::Vulkan user32)
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
