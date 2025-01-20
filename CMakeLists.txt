cmake_minimum_required(VERSION 3.10)
project(GameOfLife)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g")

# Set C++ standrd
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)

# Add libs
set(LIB_DIR ${PROJECT_SOURCE_DIR}/libs)

# Raylib
include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
    GIT_TAG "master"
    GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(raylib)

# Add ImGui
set(IMGUI_DIR ${PROJECT_SOURCE_DIR}/libs/imgui)
set(IMGUI_BACKENDS_DIR ${IMGUI_DIR}/backends)
file(GLOB IMGUI_SOURCES
    ${IMGUI_DIR}/*.cpp
    ${IMGUI_BACKENDS_DIR}/imgui_impl_win32.cpp
    ${IMGUI_BACKENDS_DIR}/imgui_impl_dx11.cpp
)
add_library(imgui STATIC ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC ${IMGUI_DIR} ${IMGUI_BACKENDS_DIR} ${RAYLIB_DIR})

# Add executable
add_executable(GameOfLife src/main.cpp)
target_include_directories(GameOfLife PUBLIC ${LIB_DIR})

# Link libraries
target_link_libraries(GameOfLife PRIVATE imgui raylib)