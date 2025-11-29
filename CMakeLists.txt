CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
project(array_gui)

set(CMAKE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/libs")

add_executable(array src/Array/arrayGUI.c)
add_executable(LinkedList src/LinkedList/linkedlistGUI.c)
add_executable(tree src/BSTree/BinarySearchTreeGUI.c)
add_executable(graph src/Graph/graphGUI.c)

target_include_directories(array PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_directories(array PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/libs")

target_include_directories(LinkedList PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_directories(LinkedList PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/libs")

target_include_directories(tree PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_directories(tree PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/libs")

target_include_directories(graph PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_directories(graph PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/libs")

add_library(support STATIC  "${CMAKE_SOURCE_DIR}/helpers/helper.c")

target_include_directories(support PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_directories(support PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/libs")

message(${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(array PUBLIC raylib opengl32 gdi32 winmm support)
target_link_libraries(LinkedList PUBLIC raylib opengl32 gdi32 winmm support)
target_link_libraries(tree PUBLIC raylib opengl32 gdi32 winmm support)
target_link_libraries(graph PUBLIC raylib opengl32 gdi32 winmm support)

target_compile_options(array PUBLIC -Wall)
target_compile_options(LinkedList PUBLIC -Wall)
target_compile_options(tree PUBLIC -Wall)
target_compile_options(graph PUBLIC -Wall)

