cmake_minimum_required(VERSION 3.8)
project(SPL1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp include/Environment.h include/Commands.h include/Files.h include/FileSystem.h include/GlobalVariables.h src/Files.cpp)
add_executable(SPL1 ${SOURCE_FILES} include/Environment.h include/Commands.h include/Files.h include/GlobalVariables.h src/Files.cpp)