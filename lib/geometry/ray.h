//
// Created by chais on 23.07.15.
//

#ifndef RAY_TRACER_RAY_H
#define RAY_TRACER_RAY_H

#include "point.h"

/**
 * Models a ray with a \ref point of origin and a \ref direction. The direction is automatically normalised.
 */
class ray {
public:
	point o;
	direction d;

	/**
	 * Explicit constructor
	 */
	ray(const point &o, const direction &d);
};

#endif //RAY_TRACER_RAY_H
