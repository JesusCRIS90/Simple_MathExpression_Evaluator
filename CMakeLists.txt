cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(Tutorial VERSION 1.0)
set(CMAKE_BUILD_TYPE Release)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#Bring the headers to the project
include_directories(include)

#The file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "source/*.cpp")

add_library(MyFirstSharedLib SHARED ${SOURCES})
