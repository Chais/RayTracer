/**
 * @file mat4.h
 * @Author Philip Abernethy
 * @date 2015-07-09
 * @brief Description of four-dimensional matrices
 */

#ifndef RAY_TRACER_MAT4_H
#define RAY_TRACER_MAT4_H

#include "vec4.h"
#include <assert.h>
#include <array>

/**
 * @brief Description of four-dimensional matrices
 *
 * Defines constructors and basic operations
 */
class mat4 {
private:
	std::array<std::array<float, 4>, 4> m;

public:
	/**
	 * @brief Default constructor
	 *
	 * Creates a 4x4 unity matrix
	 */
	mat4();

	/**
	 * @brief Explicit constructor
	 *
	 * Creates a 4x4 matrix copying the given array
	 * @param in The std::array of values
	 */
	mat4(const std::array<std::array<float, 4>, 4> &in);

	/**
	 * @brief Copy constructor
	 *
	 * Creates a 4x4 matrix from the given matrix
	 * @param in The original matrix
	 */
	mat4(const mat4 &in);

	/**
	 * @brief Assignment
	 *
	 * Assigns the values of the right matrix
	 * @param in The right operand
	 * @return The updated matrix
	 */
	mat4 &operator=(const mat4 &in);

	/**
	 * @brief Array subscript
	 *
	 * Allows access to the matrix' values
	 * @param i The index
	 */
	std::array<float, 4> operator[](const unsigned long i);

	/**
	 * @brief Array subscript
	 *
	 * Allows access to the matrix' values
	 * @param i The index
	 */
	const std::array<float, 4> operator[](const unsigned long i) const;

	/**
	 * @brief Stream output
	 *
	 * Puts the matrix on an output stream in an Octave/Matlab-compatible format
	 * @param out the output stream
	 * @param a The matrix
	 * @return The output stream
	 */
	friend std::ostream &operator<<(std::ostream &out, const mat4 &a);
};

/** @relates mat4
 * @brief Addition operator
 *
 * Adds the matrices lhs and rhs component-wise.
 * @param lhs The left operand
 * @param rhs The right operand
 * @return The resulting new matrix
 */
mat4 operator+(const mat4 &lhs, const mat4 &rhs);

/** @relates mat4
 * @brief Addition assignment
 *
 * Adds the matrices lhs and rhs component-wise. The result is assigned to lhs. This is equivalent to lhs=lhs+rhs.
 * @param lhs The left operand
 * @param rhs The right operand
 * @return The updated lhs matrix
 */
mat4 &operator+=(mat4 &lhs, const mat4 &rhs);

/** @relates mat4
 * @brief Subtraction operator
 *
 * Subtracts the matrix rhs component-wise from lhs.
 * @param lhs The left operand
 * @param rhs The right operand
 * @return The resulting  matrix
 */
mat4 operator-(const mat4 &lhs, const mat4 &rhs);

/** @relates mat4
 * @brief Subtraction assignment
 *
 * Subtracts the matrix rhs component-wise from lhs. The result is assigned to lhs. This is equivalent to lhs=lhs-rhs.
 * @param lhs The left operand
 * @param rhs The right operand
 * @return The updated lhs matrix
 */
mat4 &operator-=(mat4 &lhs, const mat4 &rhs);

/** @relates mat4
 * @brief Unitary minus operator
 *
 * Negates every value of the matrix
 * @param rhs The matrix
 * @return The resulting negated matrix
 */
mat4 operator-(const mat4 &rhs);

/** @relates mat4
 * @brief Scalar multiplication
 *
 * Multiplies every value of the matrix with the given scalar.
 * @param lhs The matrix
 * @param rhs The scaling factor
 * @return The scaled matrix
 */
mat4 operator*(const mat4 &lhs, const float &rhs);

/** @relates mat4
 * @brief Scalar multiplication
 *
 * Multiplies every value of the matrix with the given scalar.
 * @param lhs The scaling factor
 * @param rhs The matrix
 * @return The scaled matrix
 */
mat4 operator*(const float &lhs, const mat4 &rhs);

/** @relates mat4
 * @brief Matrix-vector multiplication
 *
 * Multiplies the matrix lhs with the column-vector rhs.
 * @param lhs The matrix
 * @param rhs The vector
 * @return The resulting row-vector
 */
vec4 operator*(const mat4 &lhs, const vec4 &rhs);

/** @relates mat4
 * @brief Vector-Matrix multiplication
 *
 * Multiplies the row-vector lhs with the matrix rhs.
 * @param lhs The left operand
 * @param rhs The right operand
 * @return The resulting column-vector
 */
vec4 operator*(const vec4 &a, const mat4 &b);

/** @relates mat4
 * @brief Matrix-matrix multiplication
 *
 * Multiplies the 4x4 matrix with another 4x4 matrix
 * @param a The left operand
 * @param b The right operand
 * @return The new resulting matrix
 */
mat4 operator*(const mat4 &a, const mat4 &b);

/** @relates mat4
 * @brief Multiplication assignment
 *
 * Mulitplies the matrix lhs with the scalar rhs. The result is assigned to lhs. This is equivalent to lhs=lhs*rhs.
 * @param lhs The left operand
 * @param rhs The right operand
 * @return The updated lhs matrix
 */
mat4 &operator*=(mat4 &lhs, const float &rhs);

/** @relates mat4
 * @brief Matrix inversion
 *
 * Calculates the inverse of the matrix a. No checks are done because transformation matrices are always invertible.
 * @param a The matrix
 * @return The new resulting matrix
 */
mat4 invert(const mat4 &a);

/** @relates mat4
 * @brief Matrix transposition
 *
 * Flips the matrix along its main diagonal.
 * @param a the matrix
 * @return The new resulting matrix
 */
mat4 transpose(const mat4 &a);

#endif //RAY_TRACER_MAT4_H
