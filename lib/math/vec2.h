/**
 * @file vec2.h
 * @Author Philip Abernethy
 * @date 2015-07-08
 * @brief Description of four-dimensional vectors
 */

#ifndef RAY_TRACER_vec2_H
#define RAY_TRACER_vec2_H

#include <ostream>
#include <cmath>
#include <algorithm>
#include <stdexcept>

/**
 * @name vec2
 * @brief Description of two-dimensional vectors
 * Defines constructors and basic operations
 */
class vec2 {
private:
	double a[2];

public:
	/**
	 * @brief Default constructor
	 * Creates a new 0 vector
	 */
	vec2();

	/**
	 * @brief Explicit constructor
	 * Creates a new vector with the values x, y, z and w
	 * @param *in the values
	 */
	vec2(const double *in);

	/**
	 * @brief Copy constructor
	 * Creates a new vector with values identical to the given vector
	 */
	vec2(const vec2 &in);

	/**
	 * @brief Assignment operator
	 * Assigns the values from the given vector
	 */
	vec2 &operator=(const vec2 &in);

	/**
	 * @brief Array subscript
	 * Allows access to the vector's values
	 * @param i the index
	 */
	double &operator[](const int i);

	/**
	 * @brief Array subscript
	 * Allows access to the vector's values
	 * @param i the index
	 */
	const double &operator[](const int i) const;

	/**
	 * Puts the vector on and output stream
	 * @param &out the output stream
	 * @param &a the vector
	 * @return the output stream
	 */
	friend std::ostream &operator<<(std::ostream &out, const vec2 &a);
};

/**
 * @brief Adds another vector to this one
 * Adds another vector component-wise to this one and assigns the sum to this vector's components
 * @param &b the other vector
 */
vec2 operator+(const vec2 &a, const vec2 &b);

/**
 * @brief Addition and assignment
 * b is added component-wise to the vector.
 * @param &b the vector to add
 * @return the updated vector
 */
vec2 &operator+=(vec2 &a, const vec2 &b);

/**
 * @brief Subtracts another vector from this one
 * Subtracts another vector component-wise from this one and assigns the difference to this vector's components
 * @param &b the subtrahend
 */
vec2 operator-(const vec2 &a, const vec2 &b);

/**
 * @brief Subtraction and assignment
 * b is subtracted component-wise from the vector.
 * @param &b the vector to subtract
 * @return the updated vector
 */
vec2 &operator-=(vec2 &a, const vec2 &b);

/**
 * @brief Negates the vector
 * Inverts each component of the vector.
 */
vec2 operator-(const vec2 &a);

/**
 * @brief Scale the vector by a scalar factor
 * Multiplies every component of this vector by the factor n, thus multiplying this vector's magnitude by the factor n
 * @param n the scaling factor
 */
vec2 operator*(const vec2 &lhs, const double rhs);

/**
 * @brief Scale the vector by a scalar factor
 * Multiplies every component of this vector by the factor n, thus multiplying this vector's magnitude by the factor n
 * @param lhs the scaling factor
 * @param rhs the vector to scale
 */
vec2 operator*(const double lhs, const vec2 &rhs);

/**
 * @brief Calculates the dot (scalar) product of this with another vector
 * Calculates the sum of the component-wise products and returns it
 * @param &b the other vector
 * @return the dot product
 */
double dot(const vec2 &a, const vec2 &b);

/**
 * @brief Scales the vector component-wise
 * Multiplies every component of this vector with its own scaling factor
 * @param f the array of scaling factors
 */
vec2 scale(const vec2 &a, const double *f);

/**
 * @brief Calculate the magnitude of the vector
 * Calculates the euclidean norm and returns the result
 * @return the magnitude (length) of this vector
 */
double length(const vec2 &a);

/**
 * @brief Normalises the vector
 * Calculates the magnitude of the vector and divides each component by it, thus bringing its magnitude to 1
 */
vec2 normalise(const vec2 &a);

#endif //RAY_TRACER_vec2_H