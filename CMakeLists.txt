project(AdaptiveControl)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)
find_package(Boost REQUIRED)


include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} lib src)
add_subdirectory(lib)
add_subdirectory(src bin)
#set(AdaptiveControl_SRCS src/AdaptiveControl.cpp src/main.cpp src/Math.cpp src/Robot.cpp)
#qt4_automoc(${AdaptiveControl_SRCS})
#add_executable(AdaptiveControl ${AdaptiveControl_SRCS})
#target_link_libraries(AdaptiveControl ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})
