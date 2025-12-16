if(WIN32)
    add_executable(launcher ${CMAKE_CURRENT_SOURCE_DIR}/launcher.c)
    target_link_libraries(launcher PUBLIC raylib opengl32 gdi32 winmm kernel32)
elseif(UNIX)
    add_executable(launcher ${CMAKE_CURRENT_SOURCE_DIR}/launcher_unix.c)
    target_link_libraries(launcher PUBLIC raylib opengl32 gdi32 )
endif()
message("configuration of launcher done")


#calls to subdirectory cmakelists to build sources
add_subdirectory(helpers)
add_subdirectory(Array)
add_subdirectory(LinkedList)
add_subdirectory(BSTree)
add_subdirectory(Graph)

