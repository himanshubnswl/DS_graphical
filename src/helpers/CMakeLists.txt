add_library(support ${CMAKE_CURRENT_SOURCE_DIR}/helper.c)
target_link_libraries(support PRIVATE raylib gdi32 winmm opengl32)