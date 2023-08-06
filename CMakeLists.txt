cmake_minimum_required(VERSION 3.20)
project(HideSharedObject)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(HideSharedObject STATIC Source/HideSharedObject.cpp)
target_include_directories(HideSharedObject PUBLIC include)

# Setup length-disassembler
add_subdirectory("Dependencies/length-disassembler")
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC length-disassembler)

# Setup DetourHooking
add_subdirectory("Dependencies/DetourHooking")
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC DetourHooking)

add_executable(HideSharedObjectExample Example/Main.cpp)
target_link_libraries(HideSharedObjectExample PUBLIC HideSharedObject)

enable_testing()
add_test(NAME HideSharedObjectExample COMMAND $<TARGET_FILE:HideSharedObjectExample>)
