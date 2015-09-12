/**
 * @file whittedrt.h
 * @author Philip Abernethy
 * @brief A Whitted ray tracer
 */

#ifndef RAY_TRACER_WHITTEDRT_H
#define RAY_TRACER_WHITTEDRT_H

#include "camera/camera.h"
#include "light/light.h"
#include "geometry/shape.h"
#include <typeinfo>

class whitted_rt {
private:
	const color background_color;
	camera *cam;
	std::vector<light *> lights;
	std::vector<shape *> scene;
	const unsigned long max_bounces;

	color cast_ray(ray r, int step, bool internal);

	bool cast_shadow(const ray &r);

	intersection find_nearest(ray r);

public:
	whitted_rt(const color &background_color, camera *cam, const std::vector<light *> &lights,
			   const std::vector<shape *> &scene, const unsigned long &max_bounces);

	void render();
};

#endif //RAY_TRACER_WHITTEDRT_H