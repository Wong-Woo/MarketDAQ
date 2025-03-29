cmake_minimum_required(VERSION 3.10)
project(MarketDAQ)
set(CMAKE_CXX_STANDARD 17)

# build option
option(RELEASE "Build RELEASE" OFF)
option(TEST_IMGUI "Build TEST_IMGUI" OFF)
option(TEST_IMGUI "Build TEST_CURL" OFF)

# list for dependenciy management
set(BUILD_LIBRARIES)

# dependency management by build option
if(RELEASE)
    list(APPEND BUILD_LIBRARIES imgui curl)
endif()
if(TEST_IMGUI)
    list(APPEND BUILD_LIBRARIES imgui)
endif()
if(TEST_CURL)
    list(APPEND BUILD_LIBRARIES curl)
endif()

# add library directory to project
# set INCLUDE_DIRECTORIES, LINK_DIRECTORIES, LINK_LIBRARIES in 'lib/CMakeLists.txt'
add_subdirectory(lib)

# target definition by option
if(RELEASE)
    message(STATUS "EXECUTABLE TARGET: RELEASE")
    add_executable(MarketDAQ src/main.cpp)
endif()
if(TEST_IMGUI)
    message(STATUS "EXECUTABLE TARGET: TEST_IMGUI")
    add_executable(MarketDAQ test/TEST_IMGUI.cpp)
endif()
if(TEST_CURL)
    message(STATUS "EXECUTABLE TARGET: TEST_CURL")
    add_executable(MarketDAQ test/TEST_CURL.cpp)
endif()

message("outer")
foreach(FILE IN LISTS INCLUDE_DIRECTORIES)
	message(${FILE} " is in the list outer")
endforeach()

target_include_directories(MarketDAQ PUBLIC ${INCLUDE_DIRECTORIES})
target_link_directories(MarketDAQ PRIVATE ${LINK_DIRECTORIES})
target_link_libraries(MarketDAQ PRIVATE ${LINK_LIBRARIES})