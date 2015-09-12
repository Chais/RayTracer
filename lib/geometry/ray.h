//
// Created by chais on 23.07.15.
//

#ifndef RAY_TRACER_RAY_H
#define RAY_TRACER_RAY_H

#include "point.h"

class ray {
public:
	point o;
	direction d;

	ray(const point &o, const direction &d);
};

#endif //RAY_TRACER_RAY_H
