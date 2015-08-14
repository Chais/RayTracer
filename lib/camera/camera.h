//
// Created by chais on 10.07.15.
//

#ifndef RAY_TRACER_CAMERA_H
#define RAY_TRACER_CAMERA_H

#include "../math/vec3.h"
#include "camera_exception.h"
#include "../geometry/ray.h"
#include <ostream>
#include <vector>
#include <cmath>

class camera {
private:
	vec3 position, direction, down, right;
	double fov;
	int maxbounces;
	std::vector<ray> rays;
public:

	camera();

	camera(const vec3 &position, const vec3 &direction, const vec3 &down, const vec3 &right, const double fov,
		   const int *resolution, const int maxbounces);

	/**
	 * @brief Puts a description of the camera on the stream
	 * Puts the names of all variables followed by their values on the stream, one variable per line
	 */
	friend std::ostream &operator<<(std::ostream &out, const camera &cam);

	/**
	 * @brief Grants easy access to the camera's rays
	 * Allows access to the rays cast by the camera. Index 0 is the upper left corner pixel, 1 the next one to the right.
	 * @param i the index to access
	 */
	ray &operator[](const int i);

	/**
	 * Returns the camera's position vector
	 * @return the position vector
	 */
	const vec3 &getPosition() const;

	/**
	 * @brief Returns the camera's viewing direction vector
	 * The camera is pointed along this vector. The direction vector can be added to the position to get the lookAt
	 * position.
	 * @return the direction vector
	 */
	const vec3 &getDirection() const;

	/**
	 * @brief Returns the camera's down direction
	 * The down and right directions span the picture plane.
	 * The down direction is considered down in the picture.
	 * @return the down direction vector
	 */
	const vec3 &getDown() const;

	/**
	 * @brief Returns the camera's right direction
	 * The down and right directions span the picture plane.
	 * The right direction is considered down in the picture.
	 */
	const vec3 &getRight() const;

	/**
	 * @brief Returns the camera's Field Of View angle
	 * The FOV is the angle between the center of the picture and the right border.
	 * @return the field of view
	 */
	double getFov() const;

	/**
	 * @brief Returns the maximum number of bounces
	 * After the maximum number of reflections/refractions a straight line to each light source is drawn to determine
	 * the lighting.
	 * @return the maximum number of bounces
	 */
	int getMaxbounces() const;

	/**
	 * @brief Returns an iterator to the first ray
	 */
	std::vector<ray>::iterator begin();

	/**
	 * @brief Returns an iterator behind the last ray
	 */
	std::vector<ray>::iterator end();
};

#endif //RAY_TRACER_CAMERA_H
