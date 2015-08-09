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
 * Multiplies the matrix a with the vector b
 *
 * @param &a the lhs matrix
 *
 * @param &b the rhs vector
 *
 * @return the new resulting vector
 */
vec4 operator*(const mat4 &a, const vec4 &b);

/**
 * @brief Matrix-vector multiplication
 * Multiplies the matrix a with the vec3 b as if b was a vec4 with its homogenous coordinate set to 1
 *
 * @param &a the lhs matrix
 *
 * @param &b the rhs vector
 *
 * @return the new resulting vector
 */
vec3 operator*(const mat4 &a, const vec3 &b);

/**
 * @brief Vector-Matrix multiplication
 * Multiplies the vector a with the matrix b
 *
 * @param &a the lhs vector
 *
 * @param &b the rhs matrix
 *
 * @return the new resulting vector
 */
vec4 operator*(const vec4 &a, const mat4 &b);

/**
 * @brief Matrix-matrix multiplication
 * Multiplies the 4x4 matrix with another 4x4 matrix
 * @param &a the left operand
 * @param &b the right operand
 * @return the new resulting matrix
 */
mat4 operator*(const mat4 &a, const mat4 &b);

/**
 * @brief Multiplication assignment
 * Equivalent to a=a*b where a and b are matrices
 * @parameter &a the left operand
 * @param &b the right operand
 * @return the updated left operand
 */
mat4 &operator*=(mat4 &a, const mat4 &b);

/**
 * /**
 * @brief Multiplication assignment
 * Equivalent to a=a*n where a is a matrix and n is a scalar
 * @parameter &a the left operand
 * @param n the right operand
 * @return the updated left operand
 */
mat4 &operator*=(mat4 &a, const double n);

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

#endif //RAY_TRACER_MAT4_H
