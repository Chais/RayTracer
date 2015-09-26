//
// Created by chais on 25.08.15.
//

#ifndef RAY_TRACER_DIRECTION_H
#define RAY_TRACER_DIRECTION_H

#include "../math/vec4.h"

/**
 * @name direction
 *
 * @brief Description of direction vectors
 *
 * A vec4 specialisation that has the w component set to 0 by default.
 */
class direction: public vec4 {
 public:
  /**
   * @brief Default constructor
   *
   * Creates a 0 vector.
   */
  direction();

  /**
   * @brief Explicit constructor
   *
   * Sets the x, y and z components. The w component defaults to 0.
   *
   * @param &x the x component
   *
   * @param &y the y component
   *
   * @param &z the z component
   */
  direction(const float &x, const float &y, const float &z);

  /**
   * @brief vec4 copy constructor
   *
   * Sets the x, y and z components. The values are taken from the vec4 parameter.
   *
   * @param &in the vec4 of component values. Note that in[3] is ignored.
   */
  direction(const vec4 &in);

  /**
   * @brief Copy constructor
   *
   * Creates a copy of the given direction vector.
   *
   * @param &in the original vector
   */
  direction(const direction &in);
};

/**
 * @brief Cross product
 *
 * Calculates the cross product of two direction vectors. This results in a direction vector that is perpendicular to
 * both input vectors. The norm (length) of that vector equals the area of the parallelogram of the input vectors.
 *
 * @param &lhs the left operand
 *
 * @param &rhs the right operand
 *
 * @return the resulting direction vector
 */
direction cross(const direction &lhs, const direction &rhs);

#endif //RAY_TRACER_DIRECTION_H
