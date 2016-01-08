/**
 * @file vec4.h
 * @Author Philip Abernethy
 * @date 2015-07-08
 * @brief Description of four-dimensional vectors
 */

#ifndef RAY_TRACER_VEC4_H
#define RAY_TRACER_VEC4_H

#include <ostream>
#include <algorithm>
#include <array>
#include <cassert>
#include <limits>
#include "helper.h"

/**
 * @brief Description of four-dimensional vectors
 *
 * Defines constructors and basic operations
 */
class vec4 {
protected:
	std::array<float, 4> a;

public:
	/**
	 * @brief Default constructor
	 *
	 * Creates a new 0 vector
	 */
	vec4();

	/**
	 * @brief Explicit constructor
	 *
	 * Creates a new vector with the values x, y, z and w
	 * @param x The x value
	 * @param y The y value
	 * @param z The z value
	 * @param w The w value
	 */
	vec4(const float &x, const float &y, const float &z, const float &w);

	/**
	 * @brief Explicit constructor
	 *
	 * Creates a new vector with the values x, y, z and w
	 * @param in The values
	 */
	vec4(const std::array<float, 4> &in);

	/**
	 * @brief Copy constructor
	 *
	 * Creates a new vector with values identical to the given vector
	 * @param in The original vector
	 */
	vec4(const vec4 &in);

	/**
	 * @brief Assignment operator
	 *
	 * Assigns the values from the given vector.
	 * @param in The rvalue vector
	 */
	virtual vec4 &operator=(const vec4 &in);

	/**
	 * @brief Array subscript
	 *
	 * Allows access to the vector's values.
	 * @param i The index
	 */
	float &operator[](const unsigned long i);

	/**
	 * @brief Array subscript
	 *
	 * Allows access to the vector's values.
	 * @param i The index
	 */
	const float &operator[](const unsigned long i) const;

	/**
	 * @brief Output operator
	 *
	 * Puts the vector on an output stream in an Octave/Matlab-compatible format.
	 * @param out The output stream
	 * @param a The vector
	 * @return The output stream
	 */
	friend std::ostream &operator<<(std::ostream &out, const vec4 &a);
};

/** @relates vec4
 * @brief Adds two vectors
 *
 * Adds the vectors lhs and rhs component-wise.
 * @param lhs The left operand
 * @param rhs The right operand
 * @return The resulting vector
 */
vec4 operator+(const vec4 &lhs, const vec4 &rhs);

/** @relates vec4
 * @brief Vector addition and assignment
 *
 * The vector rhs is added component-wise to lhs. The result is assigned to lhs. This is equivalent to lhs=lhs+rhs.
 * @param lhs The left operand
 * @param rhs The right operand
 * @return The updated lhs vector
 */
vec4 &operator+=(vec4 &a, const vec4 &b);

/** @relates vec4
 * @brief Subtracts two vectors
 *
 * Subtracts the vector rhs from lhs.
 * @param lhs The left operand
 * @param rhs The right operand
 * @return The resulting vector
 */
vec4 operator-(const vec4 &a, const vec4 &b);

/** @relates vec4
 * @brief Vector subtraction and assignment
 *
 * The vector rhs is subtracted component-wise from lhs. The result is assigned to lhs. This is equivalent to
 * lhs=lhs-rhs.
 * @param lhs The left operand
 * @param rhs The right operand
 * @return The updated lhs vector
 */
vec4 &operator-=(vec4 &a, const vec4 &b);

/** @relates vec4
 * @brief Unary minus operator
 *
 * Inverts/negates each component of the vector.
 * @param rhs The right operand
 * @return The resulting vector
 */
vec4 operator-(const vec4 &rhs);

/** @relates vec4
 * @brief Scale a vector by a scalar factor
 *
 * Multiplies every component of the vector lhs by the factor rhs, thus multiplying this vector's magnitude by the
 * factor rhs.
 * @param lhs The vector
 * @param rhs The scaling factor
 * @return The scaled vector
 */
vec4 operator*(const vec4 &lhs, const float &rhs);

/** @relates vec4
 * @brief Scale a vector by a scalar factor
 *
 * Multiplies every component of the vector rhs by the factor lhs, thus multiplying this vector's magnitude by the
 * factor lhs.
 * @param lhs The scaling factor
 * @param rhs The vector
 * @return The scaled vector
 */
vec4 operator*(const float &lhs, const vec4 &rhs);

/** @relates vec4
 * @brief Equal to
 *
 * Checks whether two vectors are (almost) equal. If all components are within an epsilon of each other they are
 * considered equal. This does not check if the vectors are multiples of each other. So for a vec4 v, v == 2*v will
 * evaluate to false.
 * @param lhs The left operand
 * @param rhs The right operand
 * @return True if all components lie within one machine epsilon of each other, false otherwise.
 */
bool operator==(const vec4 &lhs, const vec4 &rhs);

/** @relates vec4
 * @brief Not equal to
 *
 * Checks whether two vectors are (almost) unequal. If all components are within an epsilon of each other they are
 * considered equal. This does not check if the vectors are multiples of each other. So for a vec4 v, v == 2*v will
 * evaluate to true.
 * @param lhs The left operand
 * @param rhs The right operand
 * @return false if all components lie within one machine epsilon of each other, true otherwise.
 */
bool operator!=(const vec4 &lhs, const vec4 &rhs);

/** @relates vec4
 * @brief Scales the vector component-wise
 *
 * Multiplies every component of the vector a with its own scaling factor. This allows for non-uniform scaling.
 * @param a The vector
 * @param f The array of scaling factors
 * @return The scaled vector
 */
vec4 scale(const vec4 &a, const float f[4]);

/** @relates vec4
 * @brief Calculates the dot (scalar) product of two vectors
 *
 * Calculates the sum of the component-wise products of the vectors lhs and rhs
 * @param lhs The left operand
 * @param rhs The right operand
 * @return The dot product
 */
float dot(const vec4 &lhs, const vec4 &rhs);

/** @relates vec4
 * @brief Calculates the magnitude of the vector
 *
 * Calculates the euclidean norm of the vector.
 * @param a The vector
 * @return The magnitude (length) of the vector
 */
float length(const vec4 &a);

/** @relates vec4
 * @brief Normalises the vector
 *
 * Calculates the magnitude of the vector and divides each component by it, thus bringing its magnitude to 1.
 * @param a The vector
 * @return The normalised vector
 */
vec4 normalise(const vec4 &a);

#endif //RAY_TRACER_VEC4_H
