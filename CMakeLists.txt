CMAKE_MINIMUM_REQUIRED(VERSION 4.00)
project(DSA_graphical LANGUAGES C)


#include(FetchContent)
find_package(raylib REQUIRED)
#FetchContent_Declare(
#        raylib
#        URl https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
#        GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
#        GIT_TAG "master"
#        FIND_PACKAGE_ARGS ${RAYLIB_VERSION}
#)

#set(BUILD_EXAMPLES OFF CACHE INTERNAL "")
#set(BUILD_GAMES OFF CACHE BOOL "" FORCE)
#FetchContent_MakeAvailable(raylib)
message(top level dir: ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)