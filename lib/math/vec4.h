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

/**
 * @name vec4
 *
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
	 * Creates m new vector with the values x, y, z and w
	 *
	 * @param x the x value
	 *
	 * @param y the y value
	 *
	 * @param z the z value
	 *
	 * @param w the w value
	 */
	vec4(const float &x, const float &y, const float &z, const float &w);

	/**
	 * @brief Explicit constructor
	 *
	 * Creates a new vector with the values x, y, z and w
	 *
	 * @param &in the values
	 */
	vec4(const std::array<const float, 4> &in);

	/**
	 * @brief Copy constructor
	 *
	 * Creates a new vector with values identical to the given vector
	 */
	vec4(const vec4 &in);

	virtual ~vec4();

/**
	 * @brief Assignment operator
	 *
	 * Assigns the values from the given vector.
	 *
	 * @param &in the rvalue vector
	 */
	vec4 &operator=(const vec4 &in);

	/**
	 * @brief Array subscript
	 *
	 * Allows access to the vector's values.
	 *
	 * @param i the index
	 */
	float &operator[](const unsigned long i);

	/**
	 * @brief Array subscript
	 *
	 * Allows access to the vector's values.
	 *
	 * @param i the index
	 */
	const float &operator[](const unsigned long i) const;

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
	friend std::ostream &operator<<(std::ostream &out, const vec4 &a);
};

/**
 * @brief Adds two vectors
 *
 * Adds the vectors lhs and rhs component-wise.
 *
 * @param &lhs the left operand
 *
 * @param &rhs the right operand
 *
 * @return the resulting vector
 */
vec4 operator+(const vec4 &lhs, const vec4 &rhs);

/**
 * @brief Vector addition and assignment
 *
 * The vector rhs is added component-wise to lhs. The result is assigned to lhs. This is equivalent to lhs=lhs+rhs.
 *
 * @param &lhs the left operand
 *
 * @param &rhs the right operand
 *
 * @return the updated lhs vector
 */
vec4 &operator+=(vec4 &a, const vec4 &b);

/**
 * @brief Subtracts two vectors
 *
 * Subtracts the vector rhs from lhs.
 *
 * @param &lhs the left operand
 *
 * @param &rhs the right operand
 *
 * @return the resulting vector
 */
vec4 operator-(const vec4 &a, const vec4 &b);

/**
 * @brief Vector subtraction and assignment
 *
 * The vector rhs is subtracted component-wise from lhs. The result is assigned to lhs. This is equivalent to
 * lhs=lhs-rhs.
 *
 * @param &lhs the left operand
 *
 * @param &rhs the right operand
 *
 * @return the updated lhs vector
 */
vec4 &operator-=(vec4 &a, const vec4 &b);

/**
 * @brief Unary minus operator
 *
 * Inverts/negates each component of the vector.
 *
 * @param &rhs the right operand
 *
 * @return the resulting vector
 */
vec4 operator-(const vec4 &rhs);

/**
 * @brief Scale a vector by a scalar factor
 *
 * Multiplies every component of the vector lhs by the factor rhs, thus multiplying this vector's magnitude by the
 * factor rhs.
 *
 * @param &lhs the vector
 *
 * @param &rhs the scaling factor
 *
 * @return the scaled vector
 */
vec4 operator*(const vec4 &lhs, const float &rhs);

/**
 * @brief Scale a vector by a scalar factor
 *
 * Multiplies every component of the vector rhs by the factor lhs, thus multiplying this vector's magnitude by the
 * factor lhs.
 *
 * @param lhs the scaling factor
 *
 * @param rhs the vector
 *
 * @return the scaled vector
 */
vec4 operator*(const float &lhs, const vec4 &rhs);

/**
 * @brief Equal to
 *
 * Checks whether two vectors are (almost) equal. If all components are within an epsilon of each other they are
 * considered equal. This does not check if the vectors are multiples of each other. So for a vec4 v, v == 2*v will
 * evaluate to false.
 *
 * @param &lhs the left operand
 *
 * @param &rhs the right operand
 *
 * @return true if all components lie within one machine epsilon of each other, false otherwise.
 */
bool operator==(const vec4 &lhs, const vec4 &rhs);

/**
 * @brief Not equal to
 *
 * Checks whether two vectors are (almost) unequal. If all components are within an epsilon of each other they are
 * considered equal. This does not check if the vectors are multiples of each other. So for a vec4 v, v == 2*v will
 * evaluate to true.
 *
 * @param &lhs the left operand
 *
 * @param &rhs the right operand
 *
 * @return false if all components lie within one machine epsilon of each other, true otherwise.
 */
bool operator!=(const vec4 &lhs, const vec4 &rhs);

/**
 * @brief Scales the vector component-wise
 *
 * Multiplies every component of the vector a with its own scaling factor. This allows for non-uniform scaling.
 *
 * @param &a the vector
 *
 * @param f the array of scaling factors
 *
 * @return the scaled vector
 */
vec4 scale(const vec4 &a, const float f[4]);

/**
 * @brief Calculates the dot (scalar) product of this with another vector
 *
 * Calculates the sum of the component-wise products of the vectors lhs and rhs
 *
 * @param &lhs the left operand
 *
 * @param &rhs the right operand
 *
 * @return the dot product
 */
float dot(const vec4 &lhs, const vec4 &rhs);

/**
 * @brief Calculates the magnitude of the vector
 *
 * Calculates the euclidean norm of the vector.
 *
 * @param &a the vector
 *
 * @return the magnitude (length) of the vector
 */
float length(const vec4 &a);

/**
 * @brief Normalises the vector
 *
 * Calculates the magnitude of the vector and divides each component by it, thus bringing its magnitude to 1.
 *
 * @param &a the vector
 *
 * @return the normalised vector
 */
vec4 normalise(const vec4 &a);

#endif //RAY_TRACER_VEC4_H