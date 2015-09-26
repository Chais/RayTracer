//
// Created by chais on 25.08.15.
//

#ifndef RAY_TRACER_POINT_H
#define RAY_TRACER_POINT_H

#include "../math/vec4.h"
#include "direction.h"

/**
 * @name direction
 *
 * @brief Description of point vectors
 *
 * A vec4 specialisation that has the w component set to 1 by default.
 */
class point: public vec4 {
 public:
  /**
   * @brief Default constructor
   *
   * Creates a 0 point vector.
   */
  point();

  /**
   * @brief Explicit constructor
   *
   * Sets the x, y and z components. The w component defaults to 1.
   *
   * @param &x the x component
   *
   * @param &y the y component
   *
   * @param &z the z component
   */
  point(const float &x, const float &y, const float &z);

  /**
   * @brief vec4 copy constructor
   *
   * Sets the x, y and z components. The values are taken from the vec4 parameter.
   *
   * @param &in the vec4 of component values. Note that in[3] is ignored.
   */
  point(const vec4 &in);

  /**
   * @brief Copy constructor
   *
   * Creates a copy of the given point vector.
   *
   * @param &in the original vector
   */
  point(const point &in);
};

/**
 * @brief Addition operator
 *
 * Adds a point vector and a direction vector. The result is a point vector again.
 *
 * @param &lhs the point vector
 *
 * @param &rhs the direction vector
 *
 * @return the resulting point vector
 */
point operator+(const point &lhs, const direction &rhs);

/**
 * @brief Addition assignment
 *
 * Adds a point vector and a direction vector. The resulting point vector is assigned to the input point.
 *
 * @param &lhs the point vector
 *
 * @param &rhs the direction vector
 *
 * @return the updated lhs point vector
 */
point &operator+=(point &lhs, const direction &rhs);

/**
 * @brief Subtraction operator
 *
 * Subtracts to point vectors, resulting in a direction vector pointing from the right hand side to the left hand side
 * point.
 *
 * @param &lhs the 'target' point
 *
 * @param &rhs the 'source' point
 *
 * @return the resulting direction vector
 */
direction operator-(const point &lhs, const point &rhs);

/**
 * @brief Addition operator
 * Subtracts a direction vector from a point vector. The result is a point vector again. This is equivalent to
 * lhs+(-rhs).
 * @param &lhs the point vector
 * @param &rhs the direction vector
 * @return the resulting point vector
 */
point operator-(const point &lhs, const direction &rhs);

#endif //RAY_TRACER_POINT_H