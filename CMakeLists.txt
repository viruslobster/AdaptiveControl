project(AdaptiveControl)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(AdaptiveControl_SRCS Robot.cpp AdaptiveControl.cpp main.cpp)
qt4_automoc(${AdaptiveControl_SRCS})
add_executable(AdaptiveControl ${AdaptiveControl_SRCS})
target_link_libraries(AdaptiveControl ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})
