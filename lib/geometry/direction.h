//
// Created by chais on 25.08.15.
//

#ifndef RAY_TRACER_DIRECTION_H
#define RAY_TRACER_DIRECTION_H

#include "../math/vec4.h"

/**
 * @name direction
 *
 * @brief Description of direction vectors
 *
 * A vec4 specialisation that has the w component set to 0 by default.
 */
class direction : public vec4 {
public:
	/**
	 * @brief Default constructor
	 *
	 * Creates a 0 vector.
	 */
	direction();

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
	direction(const float &x, const float &y, const float &z);

	/**
	 * @brief vec4 copy constructor
	 *
	 * Sets the x, y and z components. The values are taken from the vec4 parameter.
	 *
	 * @param &in the vec4 of component values. Note that in[3] is ignored.
	 */
	direction(const vec4 &in);

	/**
	 * @brief Copy constructor
	 *
	 * Creates a copy of the given direction vector.
	 *
	 * @param &in the original vector
	 */
	direction(const direction &in);

	/**
	 * @brief Output operator
	 *
	 * Puts the vector on an output stream in an Octave/Matlab-compatible format.
	 *
	 * @param &out the output stream
	 *
	 * @param &a the vector
	 *
	 * @return the output stream
	 */
	friend std::ostream &operator<<(std::ostream &out, const direction &a);
};

/**
 * @brief Addition operator
 *
 * Adds two direction vectors.
 *
 * @param &lhs the left operand
 *
 * @param &rhs the right operand
 *
 * @return the resulting direction vector
 */
direction operator+(const direction &lhs, const direction &rhs);

/**
 * @brief Addition assignment
 *
 * Adds two direction vectors. The result is assigned the left one. this is equivalent to lhs=lhs+rhs.
 *
 * @param &lhs the left operand
 *
 * @param &rhs the right operand
 *
 * @return the updated lhs vector
 */
direction &operator+=(direction &lhs, const direction &rhs);

/**
 * @brief Subtraction operator
 *
 * Subtracts two direction vectors.
 *
 * @param &lhs the left operand
 *
 * @param &rhs the right operand
 *
 * @return the resulting direction vector
 */
direction operator-(const direction &lhs, const direction &rhs);

/**
 * @brief Subtraction assignment
 *
 * Subtracts two direction vectors. The result is assigned the left one. this is equivalent to lhs=lhs-rhs.
 *
 * @param &lhs the left operand
 *
 * @param &rhs the right operand
 *
 * @return the updated lhs vector
 */
direction &operator-=(direction &lhs, const direction &rhs);

/**
 * @brief Multiplication operator
 *
 * Multiplies a direction vector by a scalar.
 *
 * @param &lhs the direction vector
 *
 * @param &rhs the scalar
 *
 * @return the scaled direction vector
 */
direction operator*(const direction &lhs, const float &rhs);

/**
 * @brief Multiplication operator
 *
 * Multiplies a direction vector by a scalar.
 *
 * @param &lhs the scalar
 *
 * @param &rhs the direction vector
 *
 * @return the scaled direction vector
 */
direction operator*(const float &lhs, const direction &rhs);

/**
 * @brief Multiplication assignment
 *
 * Multiplies a direction vector by a scalar and assigns the result to the original vector. This is equivalent to
 * lhs=lhs*rhs.
 *
 * @param &lhs the direction vector
 *
 * @param &rhs the scalar
 *
 * @return the updated lhs vector
 */
direction &operator*=(direction &lhs, const float &rhs);

/**
 * @brief Dot product
 *
 * Calculates the dot product of two direction vectors.
 *
 * @param &lhs the left operand
 *
 * @param &rhs the right operand
 *
 * @return the dot product
 */
float dot(const direction &lhs, const direction &rhs);

/**
 * @brief Cross product
 *
 * Calculates the cross product of two direction vectors. This results in a direction vector that is perpendicular to
 * both input vectors. The norm (length) of that vector equals the area of the parallelogram of the input vectors.
 *
 * @param &lhs the left operand
 *
 * @param &rhs the right operand
 *
 * @return the resulting direction vector
 */
direction cross(const direction &lhs, const direction &rhs);

#endif //RAY_TRACER_DIRECTION_H
