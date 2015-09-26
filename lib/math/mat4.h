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
 * @class mat4
 * @brief Description of four-dimensional matrices
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
   *
   * @param &in the std::array of values
   */
  mat4(const std::array<std::array<float, 4>, 4> &in);

  /**
   * @brief Copy constructor
   *
   * Creates a 4x4 matrix from the given matrix
   *
   * @param &in the original matrix
   */
  mat4(const mat4 &in);

  /**
   * @brief Assignment
   *
   * Assigns the values of the right matrix
   *
   * @param &in the right operand
   *
   * @return the updated matrix
   */
  mat4 &operator=(const mat4 &in);

  /**
   * @brief Array subscript
   *
   * Allows access to the matrix' values
   */
  std::array<float, 4> operator[](const unsigned long i);

  /**
   * @brief Array subscript
   *
   * Allows access to the matrix' values
   */
  const std::array<float, 4> operator[](const unsigned long i) const;

  /**
   * @brief Stream output
   *
   * Puts the matrix on an output stream in an Octave/Matlab-compatible format
   *
   * @param &out the output stream
   *
   * @param &a the matrix
   *
   * @return the output stream
   */
  friend std::ostream &operator<<(std::ostream &out, const mat4 &a);
};

/**
 * @brief Addition operator
 *
 * Adds the matrices lhs and rhs component-wise.
 *
 * @param &lhs the left operand
 *
 * @param &rhs the right operand
 *
 * @return the resulting new matrix
 */
mat4 operator+(const mat4 &lhs, const mat4 &rhs);

/**
 * @brief Addition assignment
 *
 * Adds the matrices lhs and rhs component-wise. The result is assigned to lhs. This is equivalent to lhs=lhs+rhs.
 *
 * @param &lhs the left operand
 *
 * @param &rhs the right operand
 *
 * @return the updated lhs matrix
 */
mat4 &operator+=(mat4 &lhs, const mat4 &rhs);

/**
 * @brief Subtraction operator
 *
 * Subtracts the matrix rhs component-wise from lhs.
 *
 * @param &lhs the left operand
 *
 * @param &rhs the right operand
 *
 * @return the resulting  matrix
 */
mat4 operator-(const mat4 &lhs, const mat4 &rhs);

/**
 * @brief Subtraction assignment
 *
 * Subtracts the matrix rhs component-wise from lhs. The result is assigned to lhs. This is equivalent to lhs=lhs-rhs.
 *
 * @param &lhs the left operand
 *
 * @param &rhs the right operand
 *
 * @return the updated lhs matrix
 */
mat4 &operator-=(mat4 &lhs, const mat4 &rhs);

/**
 * @brief Unitary minus operator
 *
 * Negates every value of the matrix
 *
 * @param &rhs the matrix
 *
 * @return the resulting negated matrix
 */
mat4 operator-(const mat4 &rhs);

/**
 * @brief Scalar multiplication
 *
 * Multiplies every value of the matrix with the given scalar.
 *
 * @param &lhs the matrix
 *
 * @param &rhs the scaling factor
 *
 * @return the scaled matrix
 */
mat4 operator*(const mat4 &lhs, const float &rhs);

/**
 * @brief Scalar multiplication
 *
 * Multiplies every value of the matrix with the given scalar.
 *
 * @param &lhs the scaling factor
 *
 * @param &rhs the matrix
 *
 * @return the scaled matrix
 */
mat4 operator*(const float &lhs, const mat4 &rhs);

/**
 * @brief Matrix-vector multiplication
 *
 * Multiplies the matrix lhs with the column-vector rhs.
 *
 * @param &lhs the matrix
 *
 * @param &rhs the vector
 *
 * @return the resulting row-vector
 */
vec4 operator*(const mat4 &lhs, const vec4 &rhs);

/**
 * @brief Vector-Matrix multiplication
 *
 * Multiplies the row-vector lhs with the matrix rhs.
 *
 * @param &lhs the left operand
 *
 * @param &rhs the right operand
 *
 * @return the resulting column-vector
 */
vec4 operator*(const vec4 &a, const mat4 &b);

/**
 * @brief Matrix-matrix multiplication
 *
 * Multiplies the 4x4 matrix with another 4x4 matrix
 *
 * @param &a the left operand
 *
 * @param &b the right operand
 *
 * @return the new resulting matrix
 */
mat4 operator*(const mat4 &a, const mat4 &b);

/**
 * @brief Multiplication assignment
 *
 * Mulitplies the matrix lhs with the scalar rhs. The result is assigned to lhs. This is equivalent to lhs=lhs*rhs.
 *
 * @param &lhs the left operand
 *
 * @param &rhs the right operand
 *
 * @return the updated lhs matrix
 */
mat4 &operator*=(mat4 &lhs, const float &rhs);

/**
 * @brief Matrix inversion
 *
 * Calculates the inverse of the matrix a. No checks are done because transformation matrices are always invertible.
 *
 * @param &a the matrix
 *
 * @return the new resulting matrix
 */
mat4 invert(const mat4 &a);

/**
 * @brief Matrix transposition
 *
 * Flips the matrix along its main diagonal.
 *
 * @param &a the matrix
 *
 * @return the new resulting matrix
 */
mat4 transpose(const mat4 &a);

#endif //RAY_TRACER_MAT4_H
