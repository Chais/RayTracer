//
// Created by chais on 26.08.15.
//

#ifndef RAY_TRACER_CAMERA_H
#define RAY_TRACER_CAMERA_H

#include "../geometry/transform.h"
#include "../geometry/ray.h"
#include "../geometry/color.h"

class camera {
protected:
	transform transforms;
	unsigned long resolution[2];
	std::vector<color> data;

	virtual camera() { };
public:
	virtual ray &get_ray(const int &x, const int &y) const = 0;

	virtual color &get_pixel(const int &x, const int &y) const = 0;
};

#endif //RAY_TRACER_CAMERA_H
