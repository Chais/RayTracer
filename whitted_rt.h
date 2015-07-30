/**
 * @file whittedrt.h
 * @author Philip Abernethy
 * @brief A Whitted ray tracer
 */

#ifndef RAY_TRACER_WHITTEDRT_H
#define RAY_TRACER_WHITTEDRT_H

#include "lib/math/vec3.h"
#include "lib/camera/camera.h"

class whitted_rt {
private:
	const vec3 backgroundColor;
	camera &cam;
	vec3 cast_ray(ray r);

public:
	whitted_rt(const vec3 &backgroundColor, camera &cam);
	void render();
};

#endif //RAY_TRACER_WHITTEDRT_H