cmake_minimum_required(VERSION 3.2)
project(Ray_Tracer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(OpenMP)
if (OPENMP_FOUND)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif ()

set(SOURCE_FILES lib/whitted_rt.cpp lib/whitted_rt.h lib/math/vec4.cpp lib/math/vec4.h lib/math/vec2.cpp lib/math/vec2.h
        lib/math/mat4.cpp lib/math/mat4.h lib/camera/perspective_camera.cpp lib/camera/perspective_camera.h
        lib/geometry/ray.h lib/geometry/shapes/sphere.cpp lib/geometry/shapes/sphere.h lib/geometry/shapes/shape.cpp
        lib/geometry/shapes/shape.h lib/math/helper.cpp lib/math/helper.h lib/light/light.cpp lib/light/light.h
        lib/light/parallel_light.cpp lib/light/parallel_light.h lib/geometry/material/material.h
        lib/geometry/material/phong_material.cpp lib/geometry/material/phong_material.h
        lib/geometry/material/solid_material.h lib/geometry/point.cpp lib/geometry/point.h lib/geometry/direction.cpp
        lib/geometry/direction.h lib/geometry/normal.cpp lib/geometry/normal.h lib/geometry/transform.cpp
        lib/geometry/transform.h lib/geometry/intersection.h lib/geometry/color.cpp lib/geometry/color.h
        lib/geometry/material/lambertian_material.cpp lib/geometry/material/lambertian_material.h
        lib/light/ambient_light.cpp lib/light/ambient_light.h lib/camera/camera.h lib/camera/camera.cpp
        lib/geometry/ray.cpp lib/geometry/material/solid_material.cpp lib/light/point_light.cpp lib/light/point_light.h
        lib/parser.cpp lib/parser.h lib/geometry/shapes/mesh.cpp lib/geometry/shapes/mesh.h
        lib/geometry/shapes/triangle.cpp lib/geometry/shapes/triangle.h lib/tiny_obj_loader.cpp lib/tiny_obj_loader.h
        lib/geometry/material/specular_material.cpp lib/geometry/material/specular_material.h
        lib/geometry/material/textured_material.cpp lib/geometry/material/textured_material.h
        lib/geometry/material/transparent_material.cpp lib/geometry/material/transparent_material.h lib/sampler/sampler.h lib/sampler/random_sampler.cpp lib/sampler/random_sampler.h lib/sampler/sampler.cpp lib/camera/realistic_camera.cpp lib/camera/realistic_camera.h)
add_executable(Ray_Tracer ${SOURCE_FILES} main.cpp)
add_executable(Test ${SOURCE_FILES} test.cpp)
target_link_libraries(Ray_Tracer X11 png pugixml)
target_link_libraries(Test X11 png pugixml)