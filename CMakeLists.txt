cmake_minimum_required(VERSION 3.2)
project(Ray_Tracer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(Ray_Tracer ${SOURCE_FILES} whitted_rt.cpp whitted_rt.h lib/math/vec3.cpp lib/math/vec3.h lib/math/vec4.cpp lib/math/vec4.h lib/math/vec2.cpp lib/math/vec2.h lib/math/mat4.cpp lib/math/mat4.h lib/camera/camera.cpp lib/camera/camera.h lib/camera/camera_exception.cpp lib/camera/camera_exception.h lib/geometry/ray.cpp lib/geometry/ray.h)
add_executable(Test test.cpp lib/math/vec3.cpp lib/math/vec3.h lib/math/vec4.cpp lib/math/vec4.h lib/math/vec2.h lib/math/mat4.cpp)
target_link_libraries(Ray_Tracer png16)