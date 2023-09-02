cmake_minimum_required(VERSION 3.20)
project(HideSharedObject)

add_library(HideSharedObject STATIC "${PROJECT_SOURCE_DIR}/Source/HideSharedObject.cpp")
target_include_directories(HideSharedObject PUBLIC "${PROJECT_SOURCE_DIR}/Include")
target_compile_options(HideSharedObject PRIVATE "-Ofast")
target_compile_features(HideSharedObject PRIVATE cxx_std_20)

if(PROJECT_IS_TOP_LEVEL)
	add_executable(HideSharedObjectExample "${PROJECT_SOURCE_DIR}/Example/Main.cpp")
	target_link_libraries(HideSharedObjectExample PUBLIC HideSharedObject)

	include(FetchContent)
	
	FetchContent_Declare(LengthDisassembler
		GIT_REPOSITORY https://github.com/Jovvik/length-disassembler
		GIT_PROGRESS TRUE
		GIT_TAG 88fd89c)
	FetchContent_MakeAvailable(LengthDisassembler)
	target_link_libraries(HideSharedObjectExample PRIVATE length-disassembler)

	FetchContent_Declare(DetourHooking
		GIT_REPOSITORY https://github.com/Sumandora/DetourHooking
		GIT_PROGRESS TRUE
		GIT_TAG abcd850)
	FetchContent_MakeAvailable(DetourHooking)
	target_link_libraries(HideSharedObjectExample PRIVATE DetourHooking)

	enable_testing()
	add_test(NAME HideSharedObjectExample COMMAND $<TARGET_FILE:HideSharedObjectExample>)
endif()