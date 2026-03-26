cmake_minimum_required(VERSION 4.0)
project(LmaoApp)

set(CMAKE_CXX_STANDARD 26)

# ========================
# OpenGL
# ========================
find_package(OpenGL REQUIRED)

# ========================
# GLFW (local)
# ========================
set(GLFW_DIR ${CMAKE_SOURCE_DIR}/external/glfw-3.4)

# Disable extras
set(GLFW_BUILD_DOCS OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_EXAMPLES OFF)

add_subdirectory(${GLFW_DIR})

# ========================
# fmt (local)
# ========================

set(FMT_DIR ${CMAKE_SOURCE_DIR}/external/fmt-12.1.0)
add_subdirectory(${FMT_DIR})

# ========================
# ImGui(local)
# ========================
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

# Treat ImGui like a system/external library
target_include_directories(imgui SYSTEM PUBLIC
        ${IMGUI_DIR}
)

# Link dependencies properly
target_link_libraries(imgui PUBLIC
        glfw
        OpenGL::GL
        fmt::fmt
)

# ========================
# App
# ========================
add_executable(LmaoApp src/main.cpp)

target_link_libraries(LmaoApp PUBLIC
        stdc++exp
        imgui
)

# ========================
# Assets copy
# ========================
file(GLOB ASSETS CONFIGURE_DEPENDS
        "${CMAKE_SOURCE_DIR}/src/assets/*"
)

add_custom_command(TARGET LmaoApp POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
        "$<TARGET_FILE_DIR:LmaoApp>/assets"

        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${ASSETS}
        "$<TARGET_FILE_DIR:LmaoApp>/assets"
)