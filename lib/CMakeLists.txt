# ImGUI
list(FIND BUILD_LIBRARIES imgui imgui_index)
if(${imgui_index} GREATER_EQUAL 0)
    message("LIBRARY TARGET: ImGUI")

    if(WIN32)
        # Windows: Use DirectX11
        add_library(imgui STATIC
            imgui/imgui.cpp
            imgui/imgui_demo.cpp
            imgui/imgui_draw.cpp
            imgui/imgui_tables.cpp
            imgui/imgui_widgets.cpp
            imgui/backends/imgui_impl_win32.cpp
            imgui/backends/imgui_impl_dx11.cpp
            implot/implot.cpp
            implot/implot_demo.cpp
            implot/implot_items.cpp
        )

        target_include_directories(imgui PUBLIC imgui imgui/backends implot)

        # Windows 시스템 라이브러리 연결 (DX11, WinAPI)
        target_link_libraries(imgui PUBLIC d3d11 dxgi dxguid)

    else()
        # Linux: Use OpenGL and GLFW
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

        target_include_directories(imgui PUBLIC imgui imgui/backends implot)
        target_link_libraries(imgui PUBLIC glfw OpenGL::GL dl)
    endif()

    list(APPEND INCLUDE_DIRECTORIES lib/imgui lib/imgui/backends lib/implot)
    list(APPEND LINK_DIRECTORIES ${CMAKE_BINARY_DIR}/lib/imgui)
    list(APPEND LINK_LIBRARIES imgui)
endif()

# CURL
list(FIND BUILD_LIBRARIES curl curl_index)
if(${curl_index} GREATER_EQUAL 0)
    message("LIBRARY TARGET: CURL")
    find_package(CURL REQUIRED)

    list(APPEND LINK_LIBRARIES curl)
endif()

# JSON
list(APPEND INCLUDE_DIRECTORIES lib/json)

# TIME
list(FIND BUILD_LIBRARIES timeconv timeconv_index)
if(${timeconv_index} GREATER_EQUAL 0)
    message("LIBRARY TARGET: TIMECONV")
    add_library(timeconv STATIC timeconv/timeconv.cpp)
    
    list(APPEND INCLUDE_DIRECTORIES lib/timeconv)
    list(APPEND LINK_DIRECTORIES ${CMAKE_BINARY_DIR}/lib/timeconv)
    list(APPEND LINK_LIBRARIES timeconv)
endif()

# make directory configuration shared with parent cmake file.
set(INCLUDE_DIRECTORIES ${INCLUDE_DIRECTORIES} PARENT_SCOPE)
set(LINK_DIRECTORIES ${LINK_DIRECTORIES} PARENT_SCOPE)
set(LINK_LIBRARIES ${LINK_LIBRARIES} PARENT_SCOPE)
