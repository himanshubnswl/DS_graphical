add_executable(LinkedList ${CMAKE_CURRENT_SOURCE_DIR}/linkedListGUI.c)
target_link_libraries(LinkedList PUBLIC raylib opengl32 gdi32 winmm support)