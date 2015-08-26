//
// Created by chais on 02.08.15.
//

#ifndef RAY_TRACER_GEOMETRY_H
#define RAY_TRACER_GEOMETRY_H

#include "ray.h"
#include "material/material.h"
#include "transform.h"
#include "intersection.h"
#include "color.h"

class shape {
protected:
	transform transforms;
	material *matrl;

public:
	shape(material *matrl);

	virtual intersection intersect_full(ray r) = 0;

	virtual bool intersect_shadow(vec3 origin, vec3 direction) = 0;

	virtual color shade(const direction &l, const normal &n, const direction &v, const vec2 &pos, const bool internal);
};

#endif //RAY_TRACER_GEOMETRY_H
