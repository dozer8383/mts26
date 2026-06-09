cmake_minimum_required(VERSION 3.10)
project(mts26 VERSION 0.1.0 LANGUAGES C)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Output directory for binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Find raylib
add_subdirectory(external/raylib)

# Add the executable
add_executable(mts26
    src/main.c
    src/platform/platform-raylib.c
)

# Link raylib and system libraries
target_link_libraries(mts26 PRIVATE
    raylib
)

# Compiler flags matching build.sh
target_compile_options(mts26 PRIVATE
    -Wall
    -Wextra
    -Wno-unused-variable
    -Wno-unused-parameter
)

# Include directories
target_include_directories(mts26 PRIVATE
    ${CMAKE_SOURCE_DIR}
)

# Define asset path as compile-time macro
target_compile_definitions(mts26 PRIVATE
    ASSET_PATH="${CMAKE_SOURCE_DIR}/assets/"
)
