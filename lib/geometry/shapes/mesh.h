//
// Created by chais on 18.09.15.
//

#ifndef RAY_TRACER_MESH_H
#define RAY_TRACER_MESH_H

#include "shape.h"
#include "triangle.h"

/**
 * Models a mesh consisting of triangles
 */
class mesh: public shape {
protected:
	/**
	 * A vector containing all triangles of the mesh
	 */
	std::shared_ptr<std::vector<std::shared_ptr<triangle>>> faces;

	/**
	 * The minimal and maximal corners of the Axis Aligned Bounding Box of the triangle.
	 */
	std::array<point, 2> aabb;

	/**
	 * Checks whether the bounding box is hit. For faster calculation \p d is expected to be 1/r.d of the original intersection ray.
	 * @param  o The \ref point "origin" (in world coordinates) of the ray
	 * @param  d The inverted direction of the ray
	 * @return   true if bound box is hit, false otherwise
	 */
	virtual bool intersect_quick(const point &o, const direction &inv_d) const;
public:
	mesh(std::shared_ptr<direction> offset, std::shared_ptr<material> matrl,
		 std::shared_ptr<std::vector<std::shared_ptr<triangle>>> faces);

	/**
	 * @brief Checks whether the given ray intersects the mesh.
	 *
	 * First does an intersection with its bounding box. If it succeeds it iterates over all triangles. For each triangle a bounding box intersection is made. If it succeeds checks whether the face can be culled by checking the dot product of the averaged normal with \p r.d . If it can't be culled a full intersection is made. If succeeds the distance is calculated. This way the closest intersection is found.
	 * @param  r The ray
	 * @return   An intersction containing the necessary information to continue calculations if the ray intersects. An intersection with null pointers if it doesn't
	 */
	virtual intersection intersect_full(const ray &r);

	/**
	 * @brief Checks whether the given \ref point is shadows by the shape for light coming from \p o+d .
	 *
	 * First does an intersection with its bounding box. If it succeeds it iterates over all triangles. For each triangle a bounding box intersection is made. If it succeeds a shadow intersection is made. If it succeeds it returns true, otherwise it moves on to the next triangle. If all triangles were checked and none intersected false is returned.
	 * @param  o The \ref point (in world coordinates) to check
	 * @param  d The vector pointing to the light source
	 * @return   true if the point is shadowed by the shape, false otherwise
	 */
	virtual bool intersect_shadow(const point &o, const direction &d) const;
};

#endif //RAY_TRACER_MESH_H
