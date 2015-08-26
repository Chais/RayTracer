/**
 * @file whittedrt.h
 * @author Philip Abernethy
 * @brief A Whitted ray tracer
 */

#ifndef RAY_TRACER_WHITTEDRT_H
#define RAY_TRACER_WHITTEDRT_H

#include "perspective_camera.h"
#include "light/light.h"
#include "geometry/shape.h"
#include <typeinfo>

class whitted_rt {
private:
	const vec3 backgroundColor;
	perspective_camera &cam;
	std::vector<light *> lights;
	std::vector<shape *> scene;

	vec3 cast_ray(ray r, int step, bool internal);

	bool cast_shadow(vec3 origin, vec3 direction);
	intersection find_nearest(ray r);

public:
	whitted_rt(const vec3 &backgroundColor, perspective_camera &cam, const std::vector<light *> &lights,
			   const std::vector<shape *> &scene);

	void render();
};

#endif //RAY_TRACER_WHITTEDRT_H