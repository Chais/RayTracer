//
// Created by chais on 25.08.15.
//

#ifndef RAY_TRACER_TRANSFORM_H
#define RAY_TRACER_TRANSFORM_H

#include "../math/mat4.h"
#include "point.h"
#include "normal.h"
#include <array>
#include "../math/helper.h"

/**
 * @name transform
 *
 * @brief Describes any series of transformations
 *
 * A transform consists of two transformation matrices. The transformation matrix and its inverse. The inverse is
 * constructed alongside the transformation matrix. For every transformation applied to the transformation matrix, the
 * inverse transformation is applied to the inverse matrix from the opposite direction.
 */
class transform {
private:
	mat4 trans;
	mat4 inv_trans;
public:
	/**
	 * @brief Default constructor
	 *
	 * Creates an empty transform with two unity matrices.
	 */
	transform();

	/**
	 * @brief Explicit constructor
	 *
	 * Copies the values of the input matrices into its own matrices. If the input matrices aren't each other's inverse
	 * the results will be incorrect.
	 */
	transform(const mat4 &trans, const mat4 &inv_trans);

	/**
	 * @brief Copy constructor
	 *
	 * Copies the matrices from an existing transform.
	 */
	transform(const transform &in);

	/**
	 * @brief Transform application to transform
	 *
	 * Applies its transformations from the left to the given transform. The inverse is applied from the right to the
	 * parameter's inverse.
	 *
	 * @param &t the transformation to be transformed
	 *
	 * @return the resulting chained transform
	 */
	transform operator()(const transform &t) const;

	/**
	 * @brief Transform application to point
	 *
	 * Applies its transformations from the left to the given point.
	 *
	 * @param &p the point to be transformed
	 *
	 * @returned the new, transformed point
	 */
	point operator()(const point &p) const;

	/**
	 * @brief Transform application to direction
	 *
	 * Applies its transformations from the left to the given direction.
	 *
	 * @param &v the direction to be transformed
	 *
	 * @return the new, transformed direction
	 */
	direction operator()(const direction &v) const;

	/**
	 * @brief Transform application to normal
	 *
	 * Applies its transposed inverse transformations from the left to the given normal.
	 *
	 * @param &n the normal to be transformed
	 *
	 * @return the new, transformed normal
	 */
	normal operator()(const normal &n) const;

	/**
	 * @brief Translate transform
	 *
	 * Applies an additional translation along the direction vector t to the existing transformations. The translation
	 * matrix is applied from the right to the existing transformations, its inverse is applied from the left to the
	 * existing inverse.
	 *
	 * @param &t the direction vector to translate along
	 */
	void translate(const direction t);

	/**
	 * @brief Scale transform
	 *
	 * Applies an additional non-uniform scaling to the existing transformations. The scaling matrix is applied from the
	 * right to the existing transformations, its inverse is applied from the left to the existing inverse.
	 *
	 * @param &sf the std::array of scaling factors in x, y and z direction
	 */
	void scale(const std::array<float, 3> sf);

	/**
	 * @brief Rotate transform around X-axis
	 *
	 * Applies an additional rotation around the X-axis to the existing transformations. The rotation matrix is applied
	 * from the right to the existing transformations, its inverse is applied from the left to the existing inverse.
	 *
	 * @param &angle the angle in degrees to rotate by
	 */
	void rotateX(const float &angle);

	/**
	 * @brief Rotate transform around Y-axis
	 *
	 * Applies an additional rotation around the Y-axis to the existing transformations. The rotation matrix is applied
	 * from the right to the existing transformations, its inverse is applied from the left to the existing inverse.
	 *
	 * @param &angle the angle in degrees to rotate by
	 */
	void rotateY(const float &angle);

	/**
	 * @brief Rotate transform around Z-axis
	 *
	 * Applies an additional rotation around the Z-axis to the existing transformations. The rotation matrix is applied
	 * from the right to the existing transformations, its inverse is applied from the left to the existing inverse.
	 *
	 * @param &angle the angle in degrees to rotate by
	 */
	void rotateZ(const float &angle);
};

#endif //RAY_TRACER_TRANSFORM_H