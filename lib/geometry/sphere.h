//
// Created by chais on 02.08.15.
//

#ifndef RAY_TRACER_SPHERE_H
#define RAY_TRACER_SPHERE_H

#include "shape.h"
#include "geometry_exception.h"

class sphere : public shape {
private:
	double radius;
public:
	sphere(double radius);

	friend std::ostream &operator<<(std::ostream &out, const sphere &a);

	virtual ray intersect(ray r) override;

	virtual bool getShadow(vec3 origin, vec3 direction) override;
};

#endif //RAY_TRACER_SPHERE_H
