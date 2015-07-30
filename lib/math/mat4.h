/**
 * @file mat4.h
 * @Author Philip Abernethy
 * @date 2015-07-09
 * @brief Description of four-dimensional matrices
 */

#ifndef RAY_TRACER_MAT4_H
#define RAY_TRACER_MAT4_H

#include "vec4.h"
#include "vec3.h"
#include <cstring>

/**
 * @class mat4
 * @brief Description of four-dimensional matrices
 * Defines constructors and basic operations
 */
class mat4 {
private:
	double a[16];

public:
	/**
	 * @brief Default constructor
	 * Creates a 4x4 unity matrix
	 */
	mat4();

	/**
	 * @brief Explicit constructor
	 * Creates a 4x4 matrix copying the given array
	 * @param *in the array of values
	 */
	mat4(const double *in);

	/**
	 * @brief Copy constructor
	 * Creates a 4x4 matrix from the given matrix
	 * @param &in the original matrix
	 */
	mat4(const mat4 &in);

	/**
	 * @brief Assignment
	 * Assigns the values of the right matrix
	 * @param &in the right operand
	 * @return the updated matrix
	 */
	mat4 &operator=(const mat4 &in);

	/**
	 * @brief Array subscript
	 * Allows access to the matrix' values
	 */
	double &operator[](const int i);

	/**
	 * @brief Array subscript
	 * Allows access to the matrix' values
	 */
	const double &operator[](const int i) const;

	/**
	 * @brief Stream output
	 * Puts the matrix on an output stream in an Octave/Matlab-compatible format
	 * @param &out the output stream
	 * @param &a the matrix
	 * @return the output stream
	 */
	friend std::ostream &operator<<(std::ostream &out, const mat4 &a);
};

/**
 * @brief Addition operator
 * Adds two 4x4 matrices component-wise
 * @param &b the right operand
 * @return the resulting new matrix
 */
mat4 operator+(const mat4 &a, const mat4 &b);

/**
 * @brief Addition assignment
 * Adds a 4x4 matrix to this one
 * @param &b the right operand
 * @return the updated matrix
 */
mat4 &operator+=(mat4 &a, const mat4 &b);

/**
 * @brief Subtraction operator
 * Component-wise subtracts the right 4x4 matrix from the left one
 * @param &b the right operand
 * @return the resulting new matrix
 */
mat4 operator-(const mat4 &a, const mat4 &b);

/**
 * @brief Subtraction assignment
 * Subtracts a 4x4 matrix from this one
 * @param &b the right operand
 * @return the updated matrix
 */
mat4 &operator-=(mat4 &a, const mat4 &b);

/**
 * @brief Negate operator
 * Negates every value of the matrix
 * @return the resulting new matrix
 */
mat4 operator-(const mat4 &a);

/**
 * @brief Scaling operation
 * Multiplies every value of the matrix with the given scalar
 * @param n the scaling factor
 * @return the new resulting matrix
 */
mat4 operator*(const mat4 &a, const double n);

/**
 * @brief Matrix-vector multiplication
 * Multiplies the matrix with a vector
 * @param &b the right operand
 * @return the new resulting vector
 */
vec4 operator*(const mat4 &a, const vec4 &b);

/**
 * @brief Matrix-matrix multiplication
 * Multiplies the 4x4 matrix with another 4x4 matrix
 * @param &b the right operand
 * @return the new resulting matrix
 */
mat4 operator*(const mat4 &a, const mat4 &b);

/**
 * @brief Matrix inversion
 * Calculates the inverse of the matrix. No checks are made, because transformation matrices are always invertible.
 * @return the new resulting matrix
 */
mat4 invert(const mat4 &a);

/**
 * @brief Vector transformation
 * Multiplies the upper left 3x3 submatrix with the vector
 * @param &b the right operand
 * @return the new resulting vector
 */
vec3 transform(const mat4 &a, const vec3 &b);

/**
 * @brief Matrix transposition
 * Flips the matrix along its main diagonal
 * @return the new resulting matrix
 */
mat4 transpose(const mat4 &a);

/**
 * @brief Matrix translation
 * 'Moves' the matrix by a vector. The vector is added to the upper rightmost 3:1 column vector of the matrix.
 * @param &b the vector to translate by
 * @return the new resulting matrix
 */
mat4 translate(const mat4 &a, const vec3 &b);

#endif //RAY_TRACER_MAT4_H
