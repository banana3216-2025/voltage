project(testbed C)

file(GLOB_RECURSE TESTBED_SRCS "src/*.c")
add_executable(testbed ${TESTBED_SRCS})

# Remove VAPI from here—keep only KIMPORT
target_compile_definitions(testbed PRIVATE VIMPORT)

target_compile_options(testbed PRIVATE -O0)
target_include_directories(testbed PRIVATE src)
target_link_libraries(testbed PRIVATE engine)
