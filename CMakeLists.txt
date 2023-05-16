cmake_minimum_required(VERSION 3.20)
project(HideSharedObject)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_executable(HideSharedObject Source/HideSharedObject.cpp Example/Main.cpp)
target_include_directories(HideSharedObject PRIVATE include)

# Setup length-disassembler
target_include_directories(HideSharedObject PUBLIC Dependencies/length-disassembler)
file(GLOB LDE_SOURCE_FILES "${CMAKE_SOURCE_DIR}/Dependencies/length-disassembler/*.cpp")
target_sources(HideSharedObject PUBLIC ${LDE_SOURCE_FILES})

# Setup DetourHooking
target_include_directories(HideSharedObject PUBLIC Dependencies/DetourHooking/include)
file(GLOB DETOURHOOKING_SOURCE_FILES "${CMAKE_SOURCE_DIR}/Dependencies/DetourHooking/Source/*.cpp")
target_sources(HideSharedObject PUBLIC ${DETOURHOOKING_SOURCE_FILES})
