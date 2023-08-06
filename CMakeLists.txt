cmake_minimum_required(VERSION 3.20)
project(HideSharedObject)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(HideSharedObject STATIC Source/HideSharedObject.cpp)
target_include_directories(HideSharedObject PUBLIC include)

add_executable(HideSharedObjectExample Example/Main.cpp)
target_link_libraries(HideSharedObjectExample PRIVATE HideSharedObject)

# Setup length-disassembler
add_subdirectory("Dependencies/length-disassembler")
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE length-disassembler)

# Setup DetourHooking
add_subdirectory("Dependencies/DetourHooking")
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE DetourHooking)
