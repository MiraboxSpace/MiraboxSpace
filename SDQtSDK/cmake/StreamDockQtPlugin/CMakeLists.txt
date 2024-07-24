cmake_minimum_required(VERSION 3.5)

project(StreamDockQtPlugin VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# widgets
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
# core
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
# websocket
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS WebSockets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS WebSockets)

# SDK
include_directories(../../SDK)
set(
  PROJECT_SOURCES
  ../../SDK/Action.cpp
  ../../SDK/Action.h
  ../../SDK/BasePlugin.cpp
  ../../SDK/BasePlugin.h
  ../../SDK/ConnectionManager.cpp
  ../../SDK/ConnectionManager.h
  ../../SDK/CustomMain.cpp
  ../../SDK/CustomMain.h
  ../../SDK/Localizer.cpp
  ../../SDK/Localizer.h
  ../../SDK/Logger.cpp
  ../../SDK/Logger.h
  ../../SDK/Plugin.cpp
  ../../SDK/Plugin.h
)
add_library(
  ProjectQtSDK
  STATIC
  ${PROJECT_SOURCES}
)
target_link_libraries(ProjectQtSDK PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(ProjectQtSDK PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(ProjectQtSDK PRIVATE Qt${QT_VERSION_MAJOR}::WebSockets)

# project
set(PROJECT_SOURCES
        main.cpp
        ExampleAction.cpp
        ExampleAction.h
        ExamplePlugin.cpp
        ExamplePlugin.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(StreamDockQtPlugin
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET StreamDockQtPlugin APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(StreamDockQtPlugin SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(StreamDockQtPlugin
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(StreamDockQtPlugin PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(StreamDockQtPlugin PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(ProjectQtSDK PRIVATE Qt${QT_VERSION_MAJOR}::WebSockets)

# Link SDK
target_link_libraries(StreamDockQtPlugin PRIVATE ProjectQtSDK)

set_target_properties(StreamDockQtPlugin PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(StreamDockQtPlugin)
endif()
