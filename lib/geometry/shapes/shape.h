//
// Created by chais on 02.08.15.
//

#ifndef RAY_TRACER_SHAPE_H
#define RAY_TRACER_SHAPE_H

#include "../ray.h"
#include "../material/material.h"
#include "../transform.h"
#include "../intersection.h"
#include "../color.h"

/**
 * Models properties common to all geometry objects
 */
class shape : public std::enable_shared_from_this<shape> {
protected:
	shape() { };
	/**
	 * Stores the transformations necessary to convert object space into world space. Since this is a transform it also stores its inverse. However for ease of use and lower cognitive load both matrices are also accessible through \p world_to_object.
	 */
	transform object_to_world;

	/**
	 * This is effectively transform(object_to_world.inv_trans, object_to_world.trans). Since transform stores pointers next to no additional memory is required.
	 */
	transform world_to_object;

	/**
	 * This is an offset from the object coordinate origin. It is untracked in the \p object_to_world (and therefor also \p world_to_object). This effectively moves the center of rotation for the shape by \p -offset
	 */
	const direction offset;

	/**
	 * The shape's material
	 */
	std::shared_ptr<material> matrl;

	shape(const direction &offset, const std::shared_ptr<material> &matrl);

public:
	/**
	 * Checks whether the given ray intersects the shape.
	 * @param  r The ray
	 * @return   An intersection containing the necessary information to continue calculations if the ray intersects. An intersection with null pointers if it doesn't
	 */
	virtual intersection intersect_full(const ray &r) const = 0;

	/**
	 * Checks whether the given \ref position is shadows by the shape for light coming from \p o+d .
	 * @param  o The \ref position (in world coordinates) to check
	 * @param  d The vector pointing to the light source
	 * @return   true if the position is shadowed by the shape, false otherwise
	 */
	virtual bool intersect_shadow(const position &o, const direction &d) const = 0;

	/**
	 * @copydoc material::shade()
	 */
	virtual const std::shared_ptr<color> shade(const color &lcol, const direction &l, const normal &n,
											   const direction &v,
											   const vec2 &pos,
											   const bool &internal) const;

	/**
	 * @copydoc material::reflect()
	 */
	std::shared_ptr<ray> reflect(const direction &i, const normal &n, const position &x) const;

	std::shared_ptr<ray> scatter(const direction &i, const normal &n, const position &x) const;

	/**
	 * @copydoc material::refract()
	 */
	std::shared_ptr<ray> refract(const direction &i, const normal &n, const position &x, const bool internal) const;

	/**
	 * Translates the shape according to the given \ref direction vector
	 * @param t The vector to translate along
	 */
	void translate(const direction &t);

	/**
	 * @brief Non-uniform scaling
	 *
	 * Scales the shape according to the given factors
	 * @param sf The array of scaling factors
	 */
	void scale(const std::array<float, 3> &sf);

	/**
	 * @brief X rotation
	 *
	 * Rotates the shape around the X axis
	 * @param angle The angle (in degrees) to rotate around
	 */
	void rotateX(const float &angle);

	/**
	 * @brief Y rotation
	 *
	 * Rotates the shape around the Y axis
	 * @param angle The angle (in degrees) to rotate around
	 */
	void rotateY(const float &angle);

	/**
	 * @brief Z rotation
	 *
	 * Rotates the shape around the Z axis
	 * @param angle The angle (in degrees) to rotate around
	 */
	void rotateZ(const float &angle);

	/**
	 * Returns the reflectance of the shape's material
	 * @return The reflectance
	 */
	const float get_reflectance() const;

	/**
	 * Returns the transmittance of the shape's material
	 * @return The transmittance
	 */
	const float get_transmittance() const;
};

#endif //RAY_TRACER_SHAPE_H