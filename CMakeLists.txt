CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
project(array_gui)

set(CMAKE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/backend)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/libs")

add_executable(run ${CMAKE_CURRENT_SOURCE_DIR}/src/DrawingStuff/BinarySearchTreeGUI.c)

target_include_directories(run PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_directories(run PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/libs")

add_library(support STATIC  "${CMAKE_SOURCE_DIR}/helpers/helper.c"
                            "${CMAKE_SOURCE_DIR}/TreeInternals.c")

target_include_directories(support PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_directories(support PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/libs")

message(${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(run PUBLIC raylib opengl32 gdi32 winmm support)
target_compile_options(run PUBLIC -Wall)