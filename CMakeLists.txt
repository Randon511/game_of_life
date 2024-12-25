cmake_minimum_required(VERSION 3.10)
project(GameOfLife)

# Set C++ standrd
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set the output binary directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)

# Add OpenGL
find_package(OpenGL REQUIRED)

# Add GLFW (build it from source if necessary)
set(GLFW_DIR ${PROJECT_SOURCE_DIR}/libs/glfw)
add_subdirectory(${GLFW_DIR} build)
include_directories(${GLFW_DIR}/include)

# Add ImGui
set(IMGUI_DIR ${PROJECT_SOURCE_DIR}/libs/imgui)
set(IMGUI_BACKENDS_DIR ${IMGUI_DIR}/backends)
file(GLOB IMGUI_SOURCES
    ${IMGUI_DIR}/*.cpp
    ${IMGUI_BACKENDS_DIR}/imgui_impl_glfw.cpp
    ${IMGUI_BACKENDS_DIR}/imgui_impl_opengl3.cpp
)
add_library(imgui STATIC ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC ${IMGUI_DIR} ${IMGUI_BACKENDS_DIR})

# Add executable
add_executable(GameOfLife src/main.cpp)

# Link libraries
target_link_libraries(GameOfLife PRIVATE OpenGL::GL glfw imgui)
target_link_libraries(GameOfLife PRIVATE -lstdc++)