//
// Created by chais on 25.08.15.
//

#ifndef RAY_TRACER_TRANSFORM_H
#define RAY_TRACER_TRANSFORM_H

#include "../math/mat4.h"
#include "position.h"
#include "normal.h"
#include <array>
#include <memory>
#include "../math/helper.h"
#include "ray.h"

/**
 * @brief Describes any series of transformations
 *
 * A transform consists of two transformation matrices. The transformation matrix and its inverse. The inverse is
 * constructed alongside the transformation matrix. For every transformation applied to the transformation matrix, the
 * inverse transformation is applied to the inverse matrix from the opposite direction.
 *
 * In this implementation new transformations are applied to existing ones from the left
 */
class transform {
public:
	std::shared_ptr<mat4> trans;
	std::shared_ptr<mat4> inv_trans;

	/**
	 * @brief Default constructor
	 *
	 * Creates an empty transform with two unity matrices.
	 */
	transform();

	/**
	 * @brief Explicit constructor
	 *
	 * Copies the values of the input matrix into its own matrices. For inv_trans the input matrix is inverted.
	 * @param trans The forward transformation matrix
	 */
	transform(std::shared_ptr<mat4> trans);

	/**
	 * @brief Explicit constructor
	 *
	 * Copies the values of the input matrices into its own matrices. If the input matrices aren't each other's inverse
	 * the results will be incorrect.
	 * @param trans     The forward transformation matrix
	 * @param inv_trans The inverse transformation matrix
	 */
	transform(std::shared_ptr<mat4> trans, std::shared_ptr<mat4> inv_trans);

	/**
	 * @brief Copy constructor
	 *
	 * Copies the matrices from an existing transform.
	 * @param in The original transform
	 */
	transform(const transform &in);

/**
	 * @brief Transform application to transform
	 *
	 * Applies its transformations from the left to the given transform. The inverse is applied from the right to the
	 * parameter's inverse.
	 * @param t The transformation to be transformed
	 * @return  The resulting chained transform
	 */
	transform operator()(const transform &t) const;

	/**
	 * @brief Transform application to position
	 *
	 * Applies its transformations from the left to the given position.
	 * @param p The position to be transformed
	 * @return  The new, transformed position
	 */
	position operator()(const position &p) const;

	/**
	 * @brief Transform application to direction
	 *
	 * Applies its transformations from the left to the given direction.
	 * @param v The direction to be transformed
	 * @return  The new, transformed direction
	 */
	direction operator()(const direction &v) const;

	/**
	 * @brief Transform application to normal
	 *
	 * Applies its transposed inverse transformations from the left to the given normal.
	 * @param n The normal to be transformed
	 * @return  The new, transformed normal
	 */
	normal operator()(const normal &n) const;

	/**
	 * @brief Transform application to ray
	 *
	 * Applies its inverse transformations to the given ray.
	 * @param r The ray to be transformed
	 * @return  The new, transformed ray
	 */
	ray operator()(const ray &r) const;

	friend std::ostream &operator<<(std::ostream &out, const transform &a);

	/**
	 * @brief Translate transform
	 *
	 * Applies an additional translation along the direction vector t to the existing transformations. The translation
	 * matrix is applied from the right to the existing transformations, its inverse is applied from the left to the
	 * existing inverse.
	 * @param t The direction vector to translate along
	 */
	void translate(const direction t);

	/**
	 * @brief Scale transform
	 *
	 * Applies an additional non-uniform scaling to the existing transformations. The scaling matrix is applied from the
	 * right to the existing transformations, its inverse is applied from the left to the existing inverse.
	 * @param sf The std::array of scaling factors in x, y and z direction
	 */
	void scale(const std::array<float, 3> sf);

	/**
	 * @brief Rotate transform around X-axis
	 *
	 * Applies an additional rotation around the X-axis to the existing transformations. The rotation matrix is applied
	 * from the right to the existing transformations, its inverse is applied from the left to the existing inverse.
	 * @param angle The angle in degrees to rotate by
	 */
	void rotateX(const float &angle);

	/**
	 * @brief Rotate transform around Y-axis
	 *
	 * Applies an additional rotation around the Y-axis to the existing transformations. The rotation matrix is applied
	 * from the right to the existing transformations, its inverse is applied from the left to the existing inverse.
	 * @param angle The angle in degrees to rotate by
	 */
	void rotateY(const float &angle);

	/**
	 * @brief Rotate transform around Z-axis
	 *
	 * Applies an additional rotation around the Z-axis to the existing transformations. The rotation matrix is applied
	 * from the right to the existing transformations, its inverse is applied from the left to the existing inverse.
	 * @param angle The angle in degrees to rotate by
	 */
	void rotateZ(const float &angle);
};

#endif //RAY_TRACER_TRANSFORM_H
