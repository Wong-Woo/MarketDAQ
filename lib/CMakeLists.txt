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

    # curl 빌드 옵션 설정
    set(BUILD_CURL_EXE OFF CACHE BOOL "Build curl executable" FORCE)
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared libraries" FORCE)
    set(CURL_STATICLIB ON CACHE BOOL "Build static library" FORCE)
    set(BUILD_TESTING OFF CACHE BOOL "Build tests" FORCE)
    set(HTTP_ONLY ON CACHE BOOL "Build HTTP only" FORCE)
    set(CURL_DISABLE_INSTALL ON CACHE BOOL "Disable install" FORCE)

    # 불필요한 의존성 비활성화
    set(CURL_USE_LIBPSL OFF CACHE BOOL "Disable libpsl" FORCE)
    set(CURL_USE_LIBSSH2 OFF CACHE BOOL "Disable libssh2" FORCE)
    set(CURL_ZLIB OFF CACHE BOOL "Disable zlib" FORCE)
    set(USE_LIBIDN2 OFF CACHE BOOL "Disable libidn2" FORCE)
    set(CURL_USE_LIBSSH OFF CACHE BOOL "Disable libssh" FORCE)
    set(USE_NGHTTP2 OFF CACHE BOOL "Disable nghttp2" FORCE)
    set(CURL_BROTLI OFF CACHE BOOL "Disable brotli" FORCE)
    set(CURL_ZSTD OFF CACHE BOOL "Disable zstd" FORCE)

    # Windows와 Linux 모두에서 curl 프로젝트 추가
    add_subdirectory(curl)

    # curl 라이브러리 연결
    list(APPEND LINK_LIBRARIES libcurl)
    list(APPEND INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/curl/include)
endif()

# JSON
list(APPEND INCLUDE_DIRECTORIES lib/json)

# make directory configuration shared with parent cmake file.
set(INCLUDE_DIRECTORIES ${INCLUDE_DIRECTORIES} PARENT_SCOPE)
set(LINK_DIRECTORIES ${LINK_DIRECTORIES} PARENT_SCOPE)
set(LINK_LIBRARIES ${LINK_LIBRARIES} PARENT_SCOPE)
