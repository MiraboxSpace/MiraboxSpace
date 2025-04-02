cmake_minimum_required(VERSION 3.10)

project(com.hotspot.streamdockPluginExample VERSION 1.0)

# set the C++ standard to C++ 20
set(CMAKE_CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED true)
if (MSVC)
  add_definitions("/Zc:__cplusplus" -DUNICODE=1)
endif()
include_directories("${CMAKE_SOURCE_DIR}")

# StreamDock CPP SDK
add_subdirectory(StreamDockCPPSDK/Vendor)
add_subdirectory(StreamDockCPPSDK/StreamDockSDK)

set(
  SOURCES
  HSDExampleAction.cpp
  HSDExamplePlugin.cpp
  main.cpp
)
add_executable(
  streamdockPluginExample
  ${SOURCES}
)

# Link StreamDock CPP SDK
target_link_libraries(streamdockPluginExample StreamDockSDK)
# 如果运行时需要链接的dll动态库，同时需要把这些dll动态库拷贝到exe同级目录下
# 需要把lib文件拷贝到.sln文件所在目录下（也就是cmake的build目录下）
