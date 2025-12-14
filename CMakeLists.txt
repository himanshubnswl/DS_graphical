CMAKE_MINIMUM_REQUIRED(VERSION 3.70)
project(array_gui LANGUAGES C)


include(FetchContent)

set(RAYLIB_VERSION 5.5.0)

FetchContent_Declare(
        raylib
        URl https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
        GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
        GIT_TAG "master"
        FIND_PACKAGE_ARGS ${RAYLIB_VERSION}
)

set(BUILD_EXAMPLES OFF CACHE INTERNAL "")
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(raylib)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)