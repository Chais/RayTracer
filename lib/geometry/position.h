//
// Created by chais on 25.08.15.
//

#ifndef RAY_TRACER_POSITION_H
#define RAY_TRACER_POSITION_H

#include "../math/vec4.h"
#include "direction.h"

/**
 * @brief Description of position vectors
 *
 * A vec4 specialisation that has the w component set to 1 by default.
 */
class position: public vec4 {
public:
	/**
	 * @brief Default constructor
	 *
	 * Creates a 0 position vector.
	 */
	position();

	/**
	 * @brief Explicit constructor
	 *
	 * Sets the x, y and z components. The w component defaults to 1.
	 * @param x the x component
	 * @param y the y component
	 * @param z the z component
	 */
	position(const float &x, const float &y, const float &z);

	/**
	 * @brief vec4 copy constructor
	 *
	 * Sets the x, y and z components. The values are taken from the vec4 parameter.
	 * @param in the vec4 of component values. Note that in[3] is ignored.
	 */
	position(const vec4 &in);

	/**
	 * @brief Copy constructor
	 *
	 * Creates a copy of the given position vector.
	 * @param in the original vector
	 */
	position(const position &in);
};

/**
 * @brief Addition operator
 *
 * Adds a position vector and a direction vector. The result is a position vector again.
 * @param lhs the position vector
 * @param rhs the direction vector
 * @return the resulting position vector
 */
position operator+(const position &lhs, const direction &rhs);

/**
 * @brief Addition assignment
 *
 * Adds a position vector and a direction vector. The resulting position vector is assigned to the input position.
 * @param lhs the position vector
 * @param rhs the direction vector
 * @return the updated lhs position vector
 */
position &operator+=(position &lhs, const direction &rhs);

/**
 * @brief Subtraction operator
 *
 * Subtracts to position vectors, resulting in a direction vector pointing from the right hand side to the left hand side
 * position.
 * @param lhs the 'target' position
 * @param rhs the 'source' position
 * @return the resulting direction vector
 */
direction operator-(const position &lhs, const position &rhs);

/**
 * @brief Addition operator
 *
 * Subtracts a direction vector from a position vector. The result is a position vector again. This is equivalent to
 * lhs+(-rhs).
 * @param lhs the position vector
 * @param rhs the direction vector
 * @return the resulting position vector
 */
position operator-(const position &lhs, const direction &rhs);

#endif //RAY_TRACER_POSITION_H
