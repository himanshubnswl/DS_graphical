add_executable(tree ${CMAKE_CURRENT_SOURCE_DIR}/BinarySearchTreeGUI.c
                    ${CMAKE_CURRENT_SOURCE_DIR}/TreeInternals.c)
target_link_libraries(tree PRIVATE raylib opengl32 gdi32 winmm support)