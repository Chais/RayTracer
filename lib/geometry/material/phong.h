//
// Created by chais on 06.08.15.
//

#ifndef RAY_TRACER_PHONG_H
#define RAY_TRACER_PHONG_H

#include "material_exception.h"
#include <ostream>

struct phong {
public:
	double ambient, diffuse, specular;
	int exponent;

	phong(double ambient, double diffuse, double specular, int exponent);
	friend std::ostream &operator<<(std::ostream &out, const phong &a);
};

#endif //RAY_TRACER_PHONG_H
