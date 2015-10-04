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
#include "geometry/material/transparent_material.h"
#include "tiny_obj_loader.h"
#include <pugixml.hpp>
#include <cassert>
#include <cstring>
#include <memory>
#include <iostream>

/**
 * @brief A parser for input files
 *
 *
 */
class parser {
private:
	/**
	 * @brief Parses a camera
	 *
	 * @param cam The \<camera\> node
	 * @return    A shared_ptr to the camera implementation described by the XML node
	 */
	static std::shared_ptr<camera> parse_camera(const pugi::xml_node &cam);

	/**
	 * @brief Parses all lights into a vector
	 *
	 * Iterates over all children of the \<lights\> node and passes them to their respective parsing functions, adding the result to a vector.
	 * @param lights The \<lights\> node
	 * @return       A shared_ptr to a std::vector containing all the lights
	 */
	static std::shared_ptr<std::vector<std::shared_ptr<light>>> parse_lights(const pugi::xml_node &lights);

	/**
	 * @brief Parses an ambient light
	 * @param l The \<ambient_light\> node
	 * @return  A shared_ptr to an ambient_light object
	 */
	static std::shared_ptr<ambient_light> parse_ambient_light(const pugi::xml_node &l);

	/**
	 * @brief Parses a parallel light
	 * @param l The \<parallel_light\> node
	 * @return  A shared_ptr to a parallel_light object
	 */
	static std::shared_ptr<parallel_light> parse_parallel_light(const pugi::xml_node &l);

	/**
	 * @brief Parses a point light
	 * @param l The \<point_light\> node
	 * @return  A shared_ptr to a point_light object
	 */
	static std::shared_ptr<point_light> parse_point_light(const pugi::xml_node &l);

	/**
	 * @brief Parses all surfaces into a vector
	 *
	 * Iterates over all children of the \<surfaces\> node and passes them to their respective parsing functions, adding the results to a vector. For each child transformations are parsed, if they exist.
	 * @param surfaces The \<surfaces\> node
	 * @return         A shared_ptr to a vector of shape implementations
	 */
	static std::shared_ptr<std::vector<std::shared_ptr<shape>>> parse_surfaces(const pugi::xml_node &surfaces);

	/**
	 * @brief Parses a sphere
	 * @param s The \<sphere\> node
	 * @return  A shared_ptr to a sphere object
	 */
	static std::shared_ptr<sphere> parse_sphere(pugi::xml_node &s);

	/**
	 * @brief Parses a mesh
	 *
	 * Passes the specified OBJ file to tiny_obj_loader for parsing. The result is then packaged into the internal representation.
	 * @param m The \<mesh\> node
	 * @return  A shared_ptr to a mesh object
	 */
	static std::shared_ptr<mesh> parse_mesh(const pugi::xml_node &m);

	/**
	 * @brief Parses materials
	 * @param m The \<material\> node
	 * @return  A shared_ptr to a material implementation
	 */
	static std::shared_ptr<material> parse_material(const pugi::xml_node &m);

	/**
	 * @brief Parses a transformation
	 * @param t The \<transform\> node
	 * @param s The shape implementation to apply the transform to
	 */
	static void parse_transform(const pugi::xml_node &t, std::shared_ptr<shape> s);

	/**
	 * @brief Parses a color
	 *
	 * Parses the RGB color ranging from 0 - 255 into the internal 0.0 - 1.0 representation.
	 * @param col The \<color\> node
	 * @return    A shared_ptr to a color object
	 */
	static std::shared_ptr<color> parse_color(const pugi::xml_node &col);

	/**
	 * @brief Parses a position
	 * @param p The \<position\> node
	 * @return  A shared_ptr to a point object
	 */
	static std::shared_ptr<point> parse_position(const pugi::xml_node &p);

	/**
	 * @brief Parses a direction
	 * @param d The \<direction\> node
	 * @return  A shared_ptr to a direction object
	 */
	static std::shared_ptr<direction> parse_direction(const pugi::xml_node &d);

	/**
	 * @brief Loads an image from the disk
	 *
	 * Iterates over all pixels in the image in a row-major order and parses the RGB color into the internal representation.
	 * @param path The path to the image file
	 * @return     A shared_ptr to a 2D vector of colors
	 */
	static std::shared_ptr<std::vector<std::vector<color>>> load_image(const std::string path);

public:
	/**
	 * @brief Parses an XML file
	 * @param in_path  The path of the XML file
	 * @param out_path The variable to store the output path (specified in the XML file)
	 * @return         A shared_ptr to a whitted_rt object that complies to the specifications in the XML file
	 */
	static std::shared_ptr<whitted_rt> parse(const char *in_path, std::string &out_path);
};

#endif //RAY_TRACER_PARSER_H
