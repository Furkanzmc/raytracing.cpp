cmake_minimum_required(VERSION 3.20)
project(raytracing.cpp CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
  set(CMAKE_CXX_FLAGS
      "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror -Wno-implicit-int-float-conversion"
  )
else()
  message(
    FATAL_ERROR
      "This project is only compatible with Clang. Please use a Clang compiler."
  )
endif()

add_executable(${CMAKE_PROJECT_NAME} src/color.cpp src/ray.cpp src/vec3.cpp
                                     src/main.cpp src/image.cpp src/ppm.cpp)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ./src)
