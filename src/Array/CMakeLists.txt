add_executable(array ${CMAKE_CURRENT_SOURCE_DIR}/arrayGUI.c)
target_link_libraries(array PRIVATE raylib opengl32 gdi32 winmm support)