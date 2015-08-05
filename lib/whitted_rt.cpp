//
// Created by chais on 08.07.15.
//

#include "whitted_rt.h"
#include "geometry/geometry_exception.h"

whitted_rt::whitted_rt(const vec3 &backgroundColor, camera &cam, const std::vector<shape *> &scene) : backgroundColor(
		backgroundColor), cam(cam), scene(scene) { }

vec3 whitted_rt::cast_ray(ray r) {
	try {
		whitted_rt::intersect intersection = this->find_nearest(r);
		shape *object = intersection.object;
		ray normal = intersection.normal;
		vec3 *base_color = normal.getColor();
		return *base_color*dot(normal.getDirection(), -r.getDirection());
	} catch (geometry_exception &e) { }
	return r.getDirection();
}

void whitted_rt::render() {
	for (ray &r : cam)
		r.setColor(cast_ray(r));
}

whitted_rt::intersect whitted_rt::find_nearest(ray r) {
	struct whitted_rt::intersect out;
	double dist = std::numeric_limits<double>::max();
	for (shape *object : scene)
		try {
			ray normal = object->intersect(r);
			double new_dist = length(r.getOrigin()-normal.getOrigin());
			if (new_dist < dist) {
				dist = new_dist;
				out.object = object;
				out.normal = normal;
			}
		} catch (geometry_exception &e) { }
	if (dist == std::numeric_limits<double>::max())
		throw geometry_exception("No intersection");
	return out;
}
