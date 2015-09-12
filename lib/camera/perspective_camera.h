//
// Created by chais on 10.07.15.
//

#ifndef RAY_TRACER_PERSPECTIVE_CAMERA_H
#define RAY_TRACER_PERSPECTIVE_CAMERA_H

#include "camera.h"

class perspective_camera : public camera {
private:
	float fov;
	double stepwidth;
	direction start;
public:
	/**
	 * @brief Default constructor
	 *
	 * Creates a perspective camera with the following specification:
	 * \p position = [0, 0, 0]
	 * \p look_at = [0, 0, -1]
	 * \p up = [0, 1, 0]
	 * \p resolution = [1024, 768]
	 * \p samples = 1
	 * \p fov = 45
	 */
	perspective_camera();

	/**
	 * @brief Explicit constructor
	 *
	 * Creates a perspective camera with the given parameters
	 *
	 * @param &position the position of the camera in world coordinates
	 *
	 * @param &look_at the position the camera is centered on in world coordinates
	 *
	 * @param &up the up direction of the image
	 *
	 * @param &resolution the std::array with the x and y resolution of the image
	 *
	 * @param &samples the number of samples per pixel
	 *
	 * @param &fov the half horizontal field-of-view angle of the camera
	 */
	perspective_camera(const point &position, const point &look_at, const direction &up,
					   const std::array<unsigned long, 2> &resolution, const unsigned long &samples, const float &fov);

	virtual std::vector<ray> *get_rays(const unsigned long &x, const unsigned long &y);
};

#endif //RAY_TRACER_CAMERA_H
