//
// Created by chais on 06.08.15.
//

#ifndef RAY_TRACER_PHONG_H
#define RAY_TRACER_PHONG_H

#include <ostream>
#include "solid_material.h"

struct phong_material : public solid_material {
private:
	float ambient, diffuse, specular, exponent;
public:
	phong_material(color col, float ambient, float diffuse, float specular, float exponent);

	friend std::ostream &operator<<(std::ostream &out, const phong_material &a);

	virtual color shade(const color &lcol, const direction &l, const normal &n, const direction &v, const vec2 &pos, const bool internal);
};

#endif //RAY_TRACER_PHONG_H
