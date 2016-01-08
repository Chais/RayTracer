/**
 * @file whittedrt.h
 * @author Philip Abernethy
 */

#ifndef RAY_TRACER_WHITTEDRT_H
#define RAY_TRACER_WHITTEDRT_H

#include "camera/camera.h"
#include "light/light.h"
#include "geometry/shapes/shape.h"
#include <typeinfo>
#include <iostream>

/**
 * @brief A whitted ray tracer.
 */
class whitted_rt {
private:
	const std::shared_ptr<color> background_color;
	std::shared_ptr<camera> cam;
	std::shared_ptr<std::vector<std::shared_ptr<light>>> lights;
	std::shared_ptr<std::vector<std::shared_ptr<shape>>> scene;

	/**
	 * @brief Casts the ray \p r and returns the color it produces.
	 *
	 * To do this it first determines the object closest to \p r's origin in \p r's direction. It then shades the point of intersection according to the light situation and material. If necessary it recurses to handle reflection and refraction. The colors of reflected/refracted rays are added to the local color after multiplication with a material factor. If step reaches the camera's \p max_bounces no recursion will be done.
	 * @param  r        The ray
	 * @param  step     The current recursion level
	 * @param  internal A flag for whether or not the ray is inside a geometry
	 * @return          The color produced by that ray
	 */
	color cast_ray(ray r, int step, bool internal);

	/**
	 * @brief Casts a shadow ray from the point \p o in the direction of \p d.
	 *
	 * \p d is expected to be not normalised and point exactly on the light source. If any geometry intersects that ray between \p o and \verbatim o+d\endverbatim \p o is considered to be in the shadow with respect to that light source.
	 * @param  o The point (in world coordinates) to check
	 * @param  d The vector from \p o to the light source
	 * @return   true if any geometry lies between \p o and the light source, false otherwise
	 */
	bool cast_shadow(const point &o, const direction &d);

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
	 * Constructor
	 * @param background_color The color to user in case no geometry is hit by a ray
     * @param cam    The camera to use
     * @param lights A vector of all the lights in the scene, including the ambient light
     * @param scene  A vector of all the geometry in the scene
	 */
	whitted_rt(std::shared_ptr<color> background_color,
			   std::shared_ptr<camera> cam,
			   std::shared_ptr<std::vector<std::shared_ptr<light>>> lights,
			   std::shared_ptr<std::vector<std::shared_ptr<shape>>> scene);

	/**
	 * @brief The main render loop
	 *
	 * Retrieves the ray(s) for all pixels from the camera and casts them. The returned color is saved to the camera's data vector. Produces a single '.' on stdout for every line finished of pixels.
	 */
	void render();

	/**
	 * @brief Fetches the color of a pixel from the camera and returns it.
	 * @param x The x-coordinate of the pixel
	 * @param y the y-coordinate of the pixel
	 * @return The color of the pixel
	 */
	std::shared_ptr<color> get_pixel(const unsigned long &x, const unsigned long &y) const;

	/**
	 * @brief Returns the resolution of the camera and thus the image
	 * @return The resolution as a std::array
	 */
	const std::array<unsigned long, 2> &get_resolution() const;
};

#endif //RAY_TRACER_WHITTEDRT_H
