//
// Created by chais on 10.07.15.
//

#ifndef RAY_TRACER_PERSPECTIVE_CAMERA_H
#define RAY_TRACER_PERSPECTIVE_CAMERA_H

#include "camera.h"

class perspective_camera: public camera {
protected:
	float fov;
	float stepwidth;
	direction start;
	float defocus;
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
	 * @param &offset the offset of the camera in world coordinates
	 *
	 * @param &look_at the offset the camera is centered on in world coordinates
	 *
	 * @param &up the up direction of the image
	 *
	 * @param &resolution the std::array with the x and y resolution of the image
	 *
	 * @param &samples the number of samples per pixel
	 *
	 * @param &fov the half horizontal field-of-view angle of the camera
	 */
	perspective_camera(const position &pos, const position &look_at, const direction &up,
					   const std::array<unsigned long, 2> &resolution,
					   const unsigned long max_bounces, const float &fov,
					   const unsigned long &samples, const unsigned long &sr,
					   const std::shared_ptr<sampler> s, const float &defocus);

	virtual std::shared_ptr<std::vector<ray>> get_rays(const unsigned long &x, const unsigned long &y);
};

#endif //RAY_TRACER_CAMERA_H
