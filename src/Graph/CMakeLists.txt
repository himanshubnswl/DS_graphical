add_executable(graph ${CMAKE_CURRENT_SOURCE_DIR}/graphGUI.c
                     ${CMAKE_CURRENT_SOURCE_DIR}/graphInternals.c)

target_link_libraries(graph PUBLIC raylib opengl32 gdi32 winmm support)