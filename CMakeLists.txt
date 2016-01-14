cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(CppCache CXX)

# Enabling C++11 and pthread for Linux, this is not necessary for "Windows"
if("${CMAKE_SYSTEM_NAME}" MATCHES "Linux")                                                                                                                                                    
  list(APPEND CMAKE_CXX_FLAGS "-std=c++11 -pthread")
endif()

include_directories(headers)

file(GLOB_RECURSE SOURCE_FILES headers/* src/*)

add_executable(CppCache ${SOURCE_FILES})
