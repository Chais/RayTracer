//
// Created by chais on 18.09.15.
//

#ifndef RAY_TRACER_TRIANGLE_H
#define RAY_TRACER_TRIANGLE_H

#include "../point.h"
#include "../normal.h"
#include "../../math/vec2.h"
#include "../intersection.h"
#include "../ray.h"
#include <memory>

/**
 * Models a triangle
 */
class triangle {
protected:
	/**
	 * The coordinates of the corners. The coordinates are expected to be in an object space shared between all triangles of a mesh.
	 */
	std::shared_ptr<std::array<point, 3>> vertices;

	/**
	 * The normals corresponding to the vertices.
	 */
	std::shared_ptr<std::array<normal, 3>> normals;

	/**
	 * The texture coordinates corresponding to the vertices.
	 */
	std::shared_ptr<std::array<vec2, 3>> texture_coords;

	/**
	 * The minimal and maximal corners of the Axis Aligned Bounding Box of the triangle.
	 */
	std::array<point, 2> aabb;

	/**
	 * Returns the normal at the given barycentric coordinates. The normals are scaled with their respective factors, then added, the result normalised.
	 * @param a The scaling factor for normals[0]
	 * @param b The scaling factor for normals[1]
	 * @param c The scaling factor for normals[2]
	 * @return  The resulting normal
	 */
	virtual std::shared_ptr<normal> get_barycentric_normal(const float &a, const float &b, const float &c) const;
public:
	triangle(std::shared_ptr<std::array<point, 3>> vertices,
			 std::shared_ptr<std::array<normal, 3>> normals,
			 std::shared_ptr<std::array<vec2, 3>> texture_coords);

	/**
	 * Checks whether the \ref ray \p r hits the triangle. First it checks whether the bounding box is hit. If not, an empty intersection is returned. If it is hit it checks whether the plane of the triangle is intersected. If not, an empty intersection is returned. If it is hit it checks whether the intersection occurs inside the triangle. If not an empty intersection is returned. If it is hit the returned intersection contains the normal, texture coordinates and position (in object coordinates) of the intersection.
	 * @param  r The ray
	 * @return   An intersction containing the necessary information to continue calculations if the ray intersects. An intersection with null pointers if it doesn't
	 */
	virtual intersection intersect_full(const ray &r) const;

	/**
	 * Checks whether the given \ref point is shadows by the shape for light coming from \p o+d . First it checks whether the bounding box is hit. If not, false is returned. If it is hit it checks whether the plane of the triangle is intersected. If not, false is returned. If it is hit it checks whether the intersection occurs inside the triangle. If not false is returned. If it is hit returns true.
	 * @param  o The \ref point (in world coordinates) to check
	 * @param  d The vector pointing to the light source
	 * @return   true if the point is shadowed by the shape, false otherwise
	 */
	virtual bool intersect_shadow(const point &o, const direction &d) const;

	/**
	 * Checks whether the bounding box is hit. For faster calculation \p d is expected to be 1/r.d of the original intersection ray.
	 * @param  o The \ref point "origin" (in world coordinates) of the ray
	 * @param  d The inverted direction of the ray
	 * @return   true if bound box is hit, false otherwise
	 */
	virtual bool intersect_quick(const point &o, const direction &inv_d) const;

	/**
	 * Returns the averaged normal of the triangle. All normals are added up and the result normalised.
	 * @return The averaged normal
	 */
	virtual std::shared_ptr<normal> get_avg_normal() const;

	/**
	 * Returns the (object space) coordinates of the Axis Aligned Bounding Box.
	 * @return The array of points.
	 */
	const std::array<point, 2> &get_aabb() const;
};

#endif //RAY_TRACER_TRIANGLE_H
