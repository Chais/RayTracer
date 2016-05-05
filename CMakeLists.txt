cmake_minimum_required(VERSION 3.2)
project(Ray_Tracer)

# Prevent compilation in-source
if (${CMAKE_BINARY_DIR} STREQUAL ${PROJECT_SOURCE_DIR})
	Message(" ")
	Message(FATAL_ERROR "Source and build  directories are the same.
 Create an empty build directory,
 change into it and re-invoke cmake")
endif ()

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if (COMPILER_SUPPORTS_CXX11)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif (COMPILER_SUPPORTS_CXX0X)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else ()
	message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif ()

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/extern)

find_package(CImg REQUIRED)
list(APPEND PROJ_INCLUDE_DIRS ${CImg_INCLUDE_DIRS})
list(APPEND PROJ_LIBRARY_DIRS ${CImg_SYSTEM_LIBS_DIR})

# Add CIMG Flags to Compilation Flags
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CIMG_CFLAGS}")

link_directories(${CImg_SYSTEM_LIBS_DIR})
include_directories(${CImg_INCLUDE_DIRS})

find_package(pugixml REQUIRED)

find_package(OpenMP)
if (OPENMP_FOUND)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif ()

add_library(math STATIC lib/math/vec4.cpp lib/math/vec2.cpp lib/math/mat4.cpp lib/math/helper.cpp)

add_library(sampler STATIC lib/sampler/random_sampler.cpp lib/sampler/sampler.cpp)
target_link_libraries(sampler math)

add_library(geometry STATIC lib/geometry/color.cpp lib/geometry/direction.cpp lib/geometry/normal.cpp
		lib/geometry/position.cpp lib/geometry/ray.cpp lib/geometry/transform.cpp lib/geometry/intersection.h
		lib/geometry/shapes/shape.cpp lib/geometry/shapes/sphere.cpp lib/geometry/shapes/triangle.cpp
		lib/geometry/shapes/mesh.cpp lib/geometry/material/material.cpp lib/geometry/material/solid_material.cpp
		lib/geometry/material/phong_material.cpp lib/geometry/material/lambertian_material.cpp
		lib/geometry/material/specular_material.cpp lib/geometry/material/textured_material.cpp
		lib/geometry/material/transparent_material.cpp lib/geometry/shapes/point.cpp)
target_link_libraries(geometry math)

add_library(light STATIC lib/light/light.cpp lib/light/ambient_light.cpp lib/light/parallel_light.cpp
		lib/light/point_light.cpp lib/light/cosine_light.cpp lib/light/mesh_light.cpp lib/light/sphere_light.cpp
		lib/light/hemisphere_light.cpp)
target_link_libraries(light geometry)

add_library(camera STATIC lib/camera/camera.cpp lib/camera/perspective_camera.cpp lib/camera/realistic_camera.cpp)
target_link_libraries(camera sampler geometry)

add_library(renderer STATIC lib/renderer/renderer.cpp lib/renderer/whitted_rt.cpp lib/renderer/pathtracer.cpp
		lib/renderer/vpl.cpp)
target_link_libraries(renderer camera light)

add_library(parser STATIC lib/parser.cpp lib/tiny_obj_loader.cpp)
target_link_libraries(parser renderer pugixml ${CImg_SYSTEM_LIBS})

add_executable(Ray_Tracer main.cpp)
target_link_libraries(Ray_Tracer parser)