cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

project(thread_safe_ostream)

set(Boost_USE_STATIC_LIBS ON) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 

# Disable auto-linking as per https://stackoverflow.com/a/6469314/7644584
add_definitions(-DBOOST_ALL_NO_LIB)

find_package(threads)
find_package(Boost COMPONENTS thread REQUIRED)

if (NOT Boost_FOUND)
  message(FATAL_ERROR "Boost is required")
endif()

# build in Release-mode by default if not explicitly set
if( NOT CMAKE_BUILD_TYPE )
  set(CMAKE_BUILD_TYPE "RelWithDebInfo")
endif()

add_subdirectory(test)