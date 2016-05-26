/**
 * @file vec2.h
 * @Author Philip Abernethy
 * @date 2015-07-08
 * @brief Description of four-dimensional vectors
 */

#ifndef RAY_TRACER_vec2_H
#define RAY_TRACER_vec2_H

#include <ostream>
#define _USE_MATH_DEFINES
#include <cmath>
#include <array>
#include <cassert>

/**
 * @brief Description of two-dimensional vectors
 *
 * Defines constructors and basic operations
 */
class vec2 {
private:
	std::array<float, 2> a;

public:
	/**
	 * @brief Default constructor
	 *
	 * Creates a new 0 vector
	 */
	vec2();

	/**
	 * @brief Explicit constructor
	 *
	 * Creates a new vector with the values u and v
	 * @param u the u component
	 * @param v the v component
	 */
	vec2(const float &u, const float &v);

	/**
	 * @brief Explicit constructor
	 *
	 * Creates a new vector with the values u and v.
	 * @param in the std::array of values
	 */
	vec2(const std::array<float, 2> &in);

	/**
	 * @brief Copy constructor
	 *
	 * Creates a new vector with values identical to the given vector.
	 * @param in The original vector
	 */
	vec2(const vec2 &in);

	/**
	 * @brief Assignment operator
	 *
	 * Assigns the values from the given vector
	 * @param in The rvalue vector
	 */
	vec2 &operator=(const vec2 &in);

	/**
	 * @brief Array subscript
	 *
	 * Allows access to the vector's values
	 * @param i the index
	 */
	float &operator[](const unsigned long i);

	/**
	 * @brief Array subscript
	 *
	 * Allows access to the vector's values
	 * @param i the index
	 */
	const float &operator[](const unsigned long i) const;

	/**
	 * Puts the vector on an output stream in an Octave/Matlab-compatible format.
	 * @param out the output stream
	 * @param m the vector
	 * @return The output stream
	 */
	friend std::ostream &operator<<(std::ostream &out, const vec2 &a);
};

/** @relates vec2
 * @brief Adds two vectors
 *
 * Component-wise adds two vectors lhs and rhs.
 * @param lhs The left operand
 * @param rhs The right operand
 * @return The resulting new vector
 */
vec2 operator+(const vec2 &lhs, const vec2 &rhs);

/** @relates vec2
 * @brief Addition and assignment
 *
 * Adds the vector rhs To lhs. The result is assigned to lhs. This is equivalent to lhs=lhs+rhs
 * @param lhs The left operand and target
 * @param rhs The right operand
 * @return The updated vector lhs
 */
vec2 &operator+=(vec2 &lhs, const vec2 &rhs);

/** @relates vec2
 * @brief Subtracts two vectors
 *
 * Component-wise subtracts the vector rhs from lhs.
 * @param lhs The left operand
 * @param rhs The right operand
 */
vec2 operator-(const vec2 &lhs, const vec2 &rhs);

/** @relates vec2
 * @brief Subtraction and assignment
 *
 * The vector rhs is subtracted component-wise from lhs. The result is assigned to lhs. This is equivalent to
 * lhs=lhs-rhs
 * @param lhs The left operand and target
 * @param rhs The right operand
 * @return The updated vector a
 */
vec2 &operator-=(vec2 &lhs, const vec2 &rhs);

/** @relates vec2
 * @brief Unitary minus operator
 *
 * Inverts each component of the vector.
 * @param rhs The right operand
 * @return The inverse vector
 */
vec2 operator-(const vec2 &rhs);

/** @relates vec2
 * @brief Scale a vector by a scalar factor
 *
 * Multiplies every component of the vector lhs by the factor rhs, thus multiplying this vector's magnitude by the
 * factor rhs.
 * @param lhs The vector
 * @param rhs The scaling factor
 * @return The scaled vector
 */
vec2 operator*(const vec2 &lhs, const float &rhs);

/** @relates vec2
 * @brief Scale a vector by a scalar factor
 *
 * Multiplies every component of the vector rhs by the factor lhs, thus multiplying this vector's magnitude by the
 * factor lhs.
 * @param lhs The scaling factor
 * @param rhs The vector
 * @return The scaled vector
 */
vec2 operator*(const float &lhs, const vec2 &rhs);

/** @relates vec2
 * @brief Calculates the dot (scalar) product of this with another vector
 *
 * Calculates the sum of the component-wise products of the vectors lhs and rhs
 * @param lhs The left operand
 * @param rhs The right operand
 * @return The dot product
 */
float dot(const vec2 &lhs, const vec2 &rhs);

/** @relates vec2
 * @brief Scales the vector component-wise
 *
 * Multiplies every component of the vector a with its own scaling factor. This allows for non-uniform scaling.
 * @param a The vector
 * @param f The array of scaling factors
 * @return The scaled vector
 */
vec2 scale(const vec2 &a, const float f[2]);

/** @relates vec2
 * @brief Calculates the magnitude of the vector
 *
 * Calculates the euclidean norm of the vector.
 * @param a The vector
 * @return The magnitude (length) of the vector
 */
float length(const vec2 &a);

/** @relates vec2
 * @brief Normalises the vector
 *
 * Calculates the magnitude of the vector and divides each component by it, thus bringing its magnitude to 1.
 * @param a The vector
 * @return The normalised vector
 */
vec2 normalise(const vec2 &a);

#endif //RAY_TRACER_vec2_H
