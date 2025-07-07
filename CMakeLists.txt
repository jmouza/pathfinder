cmake_minimum_required(VERSION 3.14)
project(pathfinder_visualization)
include(FetchContent)

# C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Warning flags
if(MSVC)
  add_compile_options(/W4 /WX)
else()
  add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

# SDL2
find_package(SDL2 REQUIRED)
if(NOT SDL2_FOUND)
  message(FATAL_ERROR "SDL2 not found. Please install it (e.g., 'apt-get install libsdl2-dev' on Linux, 'brew install sdl2' on macOS, or 'pacman -S mingw-w64-i686-SDL2' on MSYS2).")
endif()

# OpenGL
if(UNIX AND NOT APPLE)
  find_package(OpenGL REQUIRED)
endif()

# GTest
cmake_policy(SET CMP0135 NEW) # avoid warning about DOWNLOAD_EXTRACT_TIMESTAMP
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_subdirectory(lib/imgui)
add_subdirectory(src/gui)
add_subdirectory(src/pathfinder)
add_subdirectory(src/main) 
add_subdirectory(test)