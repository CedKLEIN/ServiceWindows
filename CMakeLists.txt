cmake_minimum_required(VERSION 3.17.3)

project("ServiceWindows_VS")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_C_COMPILER "C:/mingw64/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "C:/mingw64/bin/g++.exe")


set(SOURCES
    main.cpp
	src/MsiObject.cpp
	src/App.cpp)
	
set(HEADERS
	src/MsiObject.hpp
	src/App.hpp)

add_executable(${CMAKE_PROJECT_NAME} ${HEADERS} ${SOURCES})

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE wbemuuid)
