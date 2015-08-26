//
// Created by chais on 10.07.15.
//

#ifndef RAY_TRACER_CAMERA_H
#define RAY_TRACER_CAMERA_H

#include "../geometry/ray.h"
#include "camera.h"
#include <ostream>
#include <vector>
#include <cmath>

class perspective_camera : public camera {
private:
	float fov;
public:
	/**
	 * @brief Default constructor
	 *
	 * Creates a perspective camera at world origin looking down the negative Z-axis.
	 */
	perspective_camera();

	perspective_camera(const point &position, const point &look_at, const direction &up, const float fov,
					   const unsigned long resolution[2]);

	/**
	 * @brief Puts m description of the camera on the stream
	 * Puts the names of all variables followed by their values on the stream, one variable per line
	 */
	friend std::ostream &operator<<(std::ostream &out, const perspective_camera &cam);

	/**
	 * @brief Grants easy access to the camera's rays
	 * Allows access to the rays cast by the camera. Index 0 is the upper left corner pixel, 1 the next one to the right.
	 * @param i the index to access
	 */
	ray &operator[](const int i);

	/**
	 * @brief Returns the camera's Field Of View angle
	 * The FOV is the angle between the center of the picture and the right border.
	 * @return the field of view
	 */
	double getFov() const;
};

#endif //RAY_TRACER_CAMERA_H
