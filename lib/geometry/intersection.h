//
// Created by chais on 25.08.15.
//

#ifndef RAY_TRACER_INTERSECTION_H
#define RAY_TRACER_INTERSECTION_H

#include "normal.h"
#include "point.h"
#include "../math/vec2.h"

class shape;

struct intersection {
	shape *object = nullptr;
	normal *norm = nullptr;
	point *pos = nullptr;
	vec2 *local_pos = nullptr;
};

#endif //RAY_TRACER_INTERSECTION_H