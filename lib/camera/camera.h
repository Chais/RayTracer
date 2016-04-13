//
// Created by chais on 26.08.15.
//

#ifndef RAY_TRACER_CAMERA_H
#define RAY_TRACER_CAMERA_H

#include "../geometry/transform.h"
#include "../geometry/ray.h"
#include "../geometry/color.h"
#include "../sampler/sampler.h"
#include "../sampler/random_sampler.h"

class camera {
protected:
	transform transforms;
	std::vector<std::vector<std::vector<color>>> data;

	camera() { };

	/**
	 * @brief Explicit constructor
	 *
	 * Initialises the values common to all camera implementations. Transforms and resolution are set as given. Memory
	 * for the data variable is allocated according to the resolution.
	 *
	 * @param &offset the offset of the camera
	 *
	 * @param &look_at the offset the camera is centred on
	 *
	 * @param &up the up direction of the image
	 *
	 * @param &resolution the resolution of the image
	 *
	 * @param &samples the number of samples per pixel
	 */
	camera(const position &pos, const position &look_at, const direction &up,
		   const std::array<unsigned long, 2> &resolution, const unsigned long max_bounces,
		   const unsigned long &samples, const unsigned long &sr, const std::shared_ptr<sampler> s);

public:
	const std::array<unsigned long, 2> resolution = {{1024, 768}};
	const unsigned long max_bounces = 0;
	const unsigned long samples = 1;
	const unsigned long shadow_rays = 1;
	const std::shared_ptr<sampler> s;
/**
	 * @brief Grants access to the initial rays of the camera
	 *
	 * Calculates the rays for the given image coordinates and returns them.
	 *
	 * @param &x the x coordinate
	 *
	 * @param &y the y coordinate
	 *
	 * @return a std::vector containing all rays contributing to the pixel with the given coordinates
	 */
	virtual std::shared_ptr<std::vector<ray>> get_rays(const unsigned long &x, const unsigned long &y) = 0;

	/**
	 * @brief Sets the data for the designated pixel
	 *
	 * @param &x the X coordinate
	 *
	 * @param &y the Y coordinate
	 *
	 * @param &data the std::vector of colors contributing the the pixel
	 */
	void set_data(const unsigned long &x, const unsigned long &y, const std::vector<color> data);

	/**
	 * @brief Returns the color of a pixel
	 *
	 * Calculates the final color of a pixel from all colors contributing to it.
	 *
	 * @param &x the x coordinate
	 *
	 * @param &y the y coordinate
	 *
	 * @return the final color of the pixel with the given coordinates
	 */
	std::shared_ptr<color> get_pixel(const unsigned long &x, const unsigned long &y) const;
};

#endif //RAY_TRACER_CAMERA_H