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
	 *
	 * @param o The point of origin of the ray
	 * @param d The direction of the ray. This will always be normalised.
	 */
	ray(const point &o, const direction &d);
};

#endif //RAY_TRACER_RAY_H
