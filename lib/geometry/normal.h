//
// Created by chais on 25.08.15.
//

#ifndef RAY_TRACER_NORMAL_H
#define RAY_TRACER_NORMAL_H

#include "../math/vec4.h"

/**
 * @name normal
 *
 * @brief Description of normal vectors
 *
 * A vec4 specialisation that has the w component set to 0 by default. This differs from direction only in how it has to
 * be transformed.
 */
class normal : public vec4 {
public:
	/**
	 * @brief Default constructor
	 *
	 * Creates a 0 vector.
	 */
	normal();

	/**
	 * @brief Explicit constructor
	 *
	 * Sets the x, y and z components. The w component defaults to 0.
	 *
	 * @param &x the x component
	 *
	 * @param &y the y component
	 *
	 * @param &z the z component
	 */
	normal(const float &x, const float &y, const float &z);

	/**
	 * @brief vec4 copy constructor
	 *
	 * Sets the x, y and z components. The values are taken from the vec4 parameter.
	 *
	 * @param &in the vec4 of component values. Note that in[3] is ignored.
	 */
	normal(const vec4 &in);

	/**
	 * @brief Copy constructor
	 *
	 * Creates a copy of the given normal vector.
	 *
	 * @param &in the original vector
	 */
	normal(const normal &in);
};

#endif //RAY_TRACER_NORMAL_H