//
// Created by chais on 25.08.15.
//

#ifndef RAY_TRACER_INTERSECTION_H
#define RAY_TRACER_INTERSECTION_H

#include "normal.h"
#include "position.h"
#include "../math/vec2.h"
#include <memory>

class shape;

/**
 * Describes an intersection of a \ref ray with a \ref shape
 */
struct intersection {
	/**
	 * The intersected \ref shape
	 */
	std::shared_ptr<const shape> object;
	/**
	 * The normal at the intersection position
	 */
	std::shared_ptr<normal> norm;
	/**
	 * The \ref point "position" of the intersection in world coordinates
	 */
	std::shared_ptr<position> pos;
	/**
	 * The local (UV) coordinates at the intersection point.
	 */
	std::shared_ptr<vec2> local_pos;
};

#endif //RAY_TRACER_INTERSECTION_H
