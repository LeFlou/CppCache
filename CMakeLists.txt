cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(CppCache CXX)

# Google C++ Testing Framework
# https://code.google.com/p/googletest/
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Enabling C++11 and pthread for Linux, this is not necessary for "Windows"
if("${CMAKE_SYSTEM_NAME}" MATCHES "Linux")                                                                                                                                                    
  list(APPEND CMAKE_CXX_FLAGS "-std=c++11 -pthread")
endif()

# Windows (x86 and x64) specific instructions for GTest
if (WIN32)
	# GTest is static compiled by default
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
endif()

include_directories(headers)

file(GLOB_RECURSE PERFORMANCE_TEST_FILES headers/LRUCache.hxx src/LRUCachePerformanceTests.cpp)
add_executable(LRUCachePerformanceTests ${PERFORMANCE_TEST_FILES})

file(GLOB_RECURSE UNIT_TESTS_FILES headers/LRUCache.hxx src/LRUCacheUnitTests.cpp)
add_executable(LRUCacheUnitTests ${UNIT_TESTS_FILES})
target_link_libraries(LRUCacheUnitTests ${GTEST_BOTH_LIBRARIES})
enable_testing()
add_test(NAME LRUCacheUnitTests COMMAND LRUCacheUnitTests)