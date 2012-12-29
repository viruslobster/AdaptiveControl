set(AdaptiveControl_SRCS AdaptiveControl.cpp main.cpp)
qt4_wrap_cpp(OUTFILES AdaptiveControl.h)
add_executable(AdaptiveControlGUI ${AdaptiveControl_SRCS} ${OUTFILES})
target_link_libraries(AdaptiveControlGUI AdaptiveControl ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})
