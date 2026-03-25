cmake_minimum_required(VERSION 4.0)
project(LmaoApp)

set(CMAKE_CXX_STANDARD 26)

# OpenGL
find_package(OpenGL REQUIRED)

# GLFW (local)
set(GLFW_DIR ${CMAKE_SOURCE_DIR}/external/glfw-3.4)

# Optional: disable extras
set(GLFW_BUILD_DOCS OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_EXAMPLES OFF)

add_subdirectory(${GLFW_DIR})

# ImGui
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/external/imgui)

set(IMGUI_SOURCES
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/imgui_demo.cpp
        ${IMGUI_DIR}/imgui_impl_glfw.cpp
        ${IMGUI_DIR}/imgui_impl_opengl3.cpp
)

add_library(imgui ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC
        ${IMGUI_DIR}
        ${GLFW_DIR}/include
)

# App
add_executable(LmaoApp src/main.cpp)

target_link_libraries(LmaoApp
        stdc++exp
        imgui
        glfw
        OpenGL::GL
)