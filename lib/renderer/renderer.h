//
// Created by chais on 01/04/16.
//

#ifndef RAY_TRACER_RENDERER_H
#define RAY_TRACER_RENDERER_H

#include "../geometry/color.h"
#include "../camera/camera.h"
#include "../light/light.h"
#include "../geometry/shapes/shape.h"
#include <iostream>

class renderer {
protected:
	const std::shared_ptr<color> background_color;
	std::shared_ptr<camera> cam;
	std::shared_ptr<std::vector<std::shared_ptr<light>>> lights;
	std::shared_ptr<std::vector<std::shared_ptr<shape>>> scene;

	renderer(const std::shared_ptr<color> &background_color, const std::shared_ptr<camera> &cam,
			 const std::shared_ptr<std::vector<std::shared_ptr<light>>> &lights,
			 const std::shared_ptr<std::vector<std::shared_ptr<shape>>> &scene);

	/**
	 * @brief Casts the ray \p r and returns the color it produces.
	 *
	 * To do this it first determines the object closest to \p r's origin in \p r's direction. It then shades the position of intersection according to the light situation and material. If necessary it recurses to handle reflection and refraction. The colors of reflected/refracted rays are added to the local color after multiplication with a material factor. If step reaches the camera's \p max_bounces no recursion will be done.
	 * @param  r        The ray
	 * @param  step     The current recursion level
	 * @param  internal A flag for whether or not the ray is inside a geometry
	 * @return          The color produced by that ray
	 */
	virtual color cast_ray(ray r, int step, bool internal) = 0;

	/**
	 * @brief Casts a shadow ray from the position \p o in the direction of \p d.
	 *
	 * \p d is expected to be not normalised and position exactly on the light source. If any geometry intersects that ray between \p o and \verbatim o+d\endverbatim \p o is considered to be in the shadow with respect to that light source.
	 * @param  o The position (in world coordinates) to check
	 * @param  d The vector from \p o to the light source
	 * @return   true if any geometry lies between \p o and the light source, false otherwise
	 */
	bool cast_shadow(const position &o, const direction &d);

	/**
	 * @brief Finds the object closest to \p r.o in the direction \p r.d.
	 *
	 * Checks for intersection of every object in \p scene with \p r. If an intersection is found the distance to \p r.o is calculated. If it is shorter than the previous one the new intersection replaces the old one.
	 * @param  r The ray to intersect with \p scene
	 * @return   If an intersection was found the intersection object contains a reference to the geometry that intersected as well as important surface properties and the world coordinates of the intersection. If no intersection was found the intersection object contains only null pointers.
	 */
	intersection find_nearest(ray r);

public:
	/**
	 * @brief Fetches the color of a pixel from the camera and returns it.
	 * @param x The x-coordinate of the pixel
	 * @param y the y-coordinate of the pixel
	 * @return The color of the pixel
	 */
	const color & get_pixel(const unsigned long &x, const unsigned long &y) const;

	/**
	 * @brief Returns the resolution of the camera and thus the image
	 * @return The resolution as a std::array
	 */
	const std::array<unsigned long, 2> &get_resolution() const;

	void render();
};

#endif //RAY_TRACER_RENDERER_H