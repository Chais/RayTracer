/**
 * @file whittedrt.h
 * @author Philip Abernethy
 * @brief A Whitted ray tracer
 */

#ifndef RAY_TRACER_WHITTEDRT_H
#define RAY_TRACER_WHITTEDRT_H

#include "math/vec3.h"
#include "camera/camera.h"
#include "geometry/shape.h"

class whitted_rt {
private:
	struct intersect {
		shape *object;
		ray normal;
		intersect() : object(nullptr), normal(vec3(), vec3()){}
	};
	const vec3 backgroundColor;
	camera &cam;
	std::vector<shape*> scene;
	vec3 cast_ray(ray r);
	intersect find_nearest(ray r);

public:
	whitted_rt(const vec3 &backgroundColor, camera &cam, const std::vector<shape*> &scene);

	void render();
};

#endif //RAY_TRACER_WHITTEDRT_H