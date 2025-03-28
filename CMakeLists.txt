cmake_minimum_required(VERSION 3.10)
project(MarketDAQ)

set(CMAKE_CXX_STANDARD 17)

# add library directory to project
add_subdirectory(lib)

# option for test
option(TEST_IMGUI "Build TEST_IMGUI" OFF)

# option for release
option(RELEASE "Build TEST_IMGUI" OFF)

# target definition by option
if(TEST_IMGUI)
    message(STATUS "EXECUTABLE TARGET: TEST_IMGUI")
    add_executable(MarketDAQ test/TEST_IMGUI.cpp)
endif()

if(TEST_CURL)
    message(STATUS "EXECUTABLE TARGET: TEST_CURL")
    add_executable(MarketDAQ test/TEST_CURL.cpp)
endif()

if(RELEASE)
    message(STATUS "EXECUTABLE TARGET: RELEASE")
    add_executable(MarketDAQ src/MarketDAQ.cpp)
endif()

# add library directory to project
target_include_directories(MarketDAQ PUBLIC lib/imgui lib/imgui/backends lib/json)
target_link_directories(MarketDAQ PRIVATE ${CMAKE_BINARY_DIR}/lib/imgui)
target_link_libraries(MarketDAQ PRIVATE imgui curl)