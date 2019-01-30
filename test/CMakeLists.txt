# Test program for thread safe ostream
add_executable(logtest logtest.cpp "${CMAKE_CURRENT_SOURCE_DIR}/../Log.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/../Log.hpp")

target_include_directories(logtest PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../" "${Boost_INCLUDE_DIRS}")
target_link_libraries(logtest Boost::thread)
