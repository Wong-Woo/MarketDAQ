# ImGUI
message("LIBRARY TARGET: ImGUI")

find_package(glfw3 REQUIRED)

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

add_library(imgui STATIC
    imgui/imgui.cpp
    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/backends/imgui_impl_glfw.cpp
    imgui/backends/imgui_impl_opengl3.cpp
    implot/implot.cpp
    implot/implot_demo.cpp
    implot/implot_items.cpp
)

target_include_directories(imgui PUBLIC imgui imgui/backends)
target_link_libraries(imgui PUBLIC glfw OpenGL::GL dl)