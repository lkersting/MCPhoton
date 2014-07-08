# Define the minimum required version of CMake (required)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

ADD_DEFINITIONS(-std=c++11)

# Set up the project directory hierarchy
ADD_SUBDIRECTORY(src)
