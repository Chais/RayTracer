//
// Created by chais on 02.08.15.
//

#ifndef RAY_TRACER_SPHERE_H
#define RAY_TRACER_SPHERE_H

#include "shape.h"
#include <ostream>
#include <cassert>

class sphere : public shape {
private:
	float radius;
public:
	sphere(const float &radius, const direction *offset, material *matrl);

	friend std::ostream &operator<<(std::ostream &out, const sphere &a);

	virtual intersection intersect_full(const ray &r);

	virtual bool intersect_shadow(const ray &r);
};

#endif //RAY_TRACER_SPHERE_H