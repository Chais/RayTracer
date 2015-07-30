/**
 * @file vec3.h
 * @Author Philip Abernethy
 * @date 2015-07-08
 * @brief Description of three-dimensional vectors
 */

#ifndef RAY_TRACER_VEC3_H
#define RAY_TRACER_VEC3_H

#include <ostream>
#include <cmath>
#include <algorithm>
#include <stdexcept>

/**
 * @name vec3
 * @brief Description of three-dimensional vectors
 * Defines constructors and basic operations
 */
class vec3 {
private:
	double a[3];

public:
	/**
	 * @brief Default constructor
	 * Creates a new 0 vector
	 */
	vec3();

	/**
	 * @brief Explicit constructor
	 * Creates a new vector with the values x, y and z
	 * @param x the x value
	 * @param y the y value
	 * @param z the z value
	 */
	vec3(const double x, const double y, const double z);

	/**
	 * @brief Explicit constructor
	 * Creates a new vector with the values x, y and z
	 * @param *in the values
	 */
	vec3(const double *in);

	/**
	 * @brief Copy constructor
	 * Creates a new vector with values identical to the given vector
	 */
	vec3(const vec3 &in);

	/**
	 * @brief Assignment operator
	 * Copies the values from the given vector
	 */
	vec3 &operator=(const vec3 &in);

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
	friend std::ostream &operator<<(std::ostream &out, const vec3 &a);
};

/**
 * @brief Adds another vector to this one
 * Adds another vector component-wise to this one and assigns the sum to this vector's components
 * @param &b the other vector
 */
vec3 operator+(const vec3 &a, const vec3 &b);

/**
 * @brief Addition and assignment
 * b is added component-wise to the vector.
 * @param &b the vector to add
 * @return the updated vector
 */
vec3 &operator+=(vec3 &a, const vec3 &b);

/**
 * @brief Subtracts another vector from this one
 * Subtracts another vector component-wise from this one and assigns the difference to this vector's components
 * @param &b the subtrahend
 */
vec3 operator-(const vec3 &a, const vec3 &b);

/**
 * @brief Subtraction and assignment
 * b is subtracted component-wise from the vector.
 * @param &b the vector to subtract
 * @return the updated vector
 */
vec3 &operator-=(vec3 &a, const vec3 &b);

/**
 * @brief Negates the vector
 * Inverts each component of the vector.
 */
vec3 operator-(const vec3 &a);

/**
 * @brief Scale the vector by a scalar factor
 * Multiplies every component of this vector by the factor n, thus multiplying this vector's magnitude by the factor n
 * @param lhs the vector to scale
 * @param rhs the scaling factor
 */
vec3 operator*(const vec3 &lhs, const double rhs);

/**
 * @brief Scale the vector by a scalar factor
 * Multiplies every component of this vector by the factor n, thus multiplying this vector's magnitude by the factor n
 * @param lhs the scaling factor
 * @param rhs the vector to scale
 */
vec3 operator*(const double lhs, const vec3 &rhs);

/**
 * @brief Multiplication and assignment
 */
vec3 &operator*=(vec3 &a, const double n);

/**
 * @brief Calculates the dot (scalar) product of this with another vector
 * Calculates the sum of the component-wise products and returns it
 * @param &b the other vector
 * @return the dot product
 */
double dot(const vec3 &a, const vec3 &b);

/**
 * @brief Calculates the cross (vector) product of this vector with another one
 * Calculates a x b, where a is this vector and b is the parameter vector.
 * The result is a vector perpendicular to a and b
 * @param &b the right-hand-side vector
 * @return the result
 */
vec3 cross(const vec3 &a, const vec3 &b);

/**
 * @brief Scales the vector component-wise
 * Multiplies every component of this vector with its own scaling factor
 * @param fx the scaling factor in x direction
 * @param fy the scaling factor in y direction
 * @param fz the scaling factor in z direction
 */
vec3 scale(const vec3 &a, const double *f);

/**
 * @brief Calculate the magnitude of the vector
 * Calculates the euclidean norm and returns the result
 * @return the magnitude (length) of this vector
 */
double length(const vec3 &a);

/**
 * @brief Normalises the vector
 * Calculates the magnitude of the vector and divides each component by it, thus bringing its magnitude to 1
 */
vec3 normalise(const vec3 &a);

/**
 * @brief Converts the coordinates to color
 * Makes a normalised copy fo the vector and converts the values to a scale 0 - 255
 * @return an int array of values from 0 - 255
 */
vec3 to_color(const vec3 &a);

#endif //RAY_TRACER_VEC3_H