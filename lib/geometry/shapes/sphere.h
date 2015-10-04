//
// Created by chais on 02.08.15.
//

#ifndef RAY_TRACER_SPHERE_H
#define RAY_TRACER_SPHERE_H

#include "shape.h"
#include <ostream>
#include <cassert>

/**
 * Models a sphere
 */
class sphere: public shape {
private:
	/**
	 * The un-transformed radius of the sphere
	 */
	float radius;
public:
	sphere(const float &radius, std::shared_ptr<direction> offset, std::shared_ptr<material> matrl);

	friend std::ostream &operator<<(std::ostream &out, const sphere &a);

	/**
	 * Checks whether the \ref ray \p r intersects the sphere. This is done by constructing a right triangle between \p r.o, the centre of the sphere and the projection of the vector centre-p.o onto r.d. If the leg perpendicular to r.d is longer than the \p radius there's no intersection. If it's shorter further calculationsare necessary to determine which of the two possible intersection points is valid.
	 * @param  r The ray
	 * @return   An intersction containing the necessary information to continue calculations if the ray intersects. An intersection with null pointers if it doesn't
	 */
	virtual intersection intersect_full(const ray &r);

	/**
	 * Checks whether the \ref ray \p r intersects the sphere. This is done by constructing a right triangle between \p r.o, the centre of the sphere and the projection of the vector centre-p.o onto r.d. If the leg perpendicular to r.d is longer than the \p radius there's no intersection.
	 * @param  o The \ref point (in world coordinates) to check
	 * @param  d The vector pointing to the light source
	 * @return   true if the point is shadowed by the shape, false otherwise
	 */
	virtual bool intersect_shadow(const point &o, const direction &d) const;
};

#endif //RAY_TRACER_SPHERE_H
