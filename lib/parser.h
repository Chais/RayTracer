//
// Created by chais on 15.09.15.
//

#ifndef RAY_TRACER_PARSER_H
#define RAY_TRACER_PARSER_H

#include "whitted_rt.h"
#include "camera/perspective_camera.h"
#include "light/ambient_light.h"
#include "light/parallel_light.h"
#include "light/point_light.h"
#include "geometry/shapes/sphere.h"
#include "geometry/shapes/mesh.h"
#include "geometry/material/phong_material.h"
#include "geometry/material/lambertian_material.h"
#include "geometry/material/specular_material.h"
#include "geometry/material/textured_material.h"
#include "tiny_obj_loader.h"
#include <pugixml.hpp>
#include <cassert>
#include <cstring>
#include <iostream>

class parser {
 private:
  static camera *parse_camera(const pugi::xml_node &cam);

  static std::vector<light *> *parse_lights(const pugi::xml_node &lights);

  static ambient_light *parse_ambient_light(const pugi::xml_node &l);

  static parallel_light *parse_parallel_light(const pugi::xml_node &l);

  static point_light *parse_point_light(const pugi::xml_node &l);

  static std::vector<shape *> *parse_surfaces(const pugi::xml_node &surfaces);

  static sphere *parse_sphere(pugi::xml_node &s);

  static mesh *parse_mesh(const pugi::xml_node &m);

  static material *parse_material(const pugi::xml_node &m);

  static void parse_transform(const pugi::xml_node &t, shape *s);

  static color *parse_color(const pugi::xml_node &col);

  static point *parse_position(const pugi::xml_node &p);

  static direction *parse_direction(const pugi::xml_node &d);

  static std::vector<std::vector<color>> *load_image(const std::string path);

 public:
  static whitted_rt *parse(const char *in_path, std::string &out_path);
};

#endif //RAY_TRACER_PARSER_H