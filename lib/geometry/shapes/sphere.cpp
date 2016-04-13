//
// Created by chais on 02.08.15.
//

#include "sphere.h"

sphere::sphere(const direction &position, const std::shared_ptr<material> &matrl, const float &radius) : radius(
	radius), shape(position, matrl) {
	assert(radius > 0);
}

std::ostream &operator<<(std::ostream &out, const sphere &a) {
	out << "Radius: " << a.radius << ", Transformations: " << a.object_to_world;
	return out;
}

intersection sphere::intersect_full(const ray &r) const {
	ray tr = world_to_object(r);
	direction c = position(-tr.o) + offset;
	float a = std::max(float(0.0), dot(tr.d, c));
	float b = std::sqrt(std::pow(length(c), 2) - std::pow(a, 2));
	intersection out = intersection();
	if (b < radius - 1E-4) {
		float d = std::sqrt(std::pow(radius, 2) - std::pow(b, 2));
		std::shared_ptr<position> x;
		if (d < a - 1E-4)
			x = std::make_shared<position>(position(tr.o + direction(tr.d*(a - d))));
		else
			x = std::make_shared<position>(position(tr.o + direction(tr.d*(a + d))));
		std::shared_ptr<normal> norm = std::make_shared<normal>(normal(*x - offset));
		float local_len = length(*norm);
		std::shared_ptr<vec2> local_pos = std::make_shared<vec2>(vec2((*norm)[0]/local_len, (*norm)[1]/local_len));
		*x = object_to_world(*x);
		*norm = normalise(object_to_world(*norm));
		out.object = shared_from_this();
		out.norm = norm;
		out.pos = x;
		out.local_pos = local_pos;
	}
	return out;
}

bool sphere::intersect_shadow(const position &o, const direction &d) const {
	if (d == direction())
		return false;
	position to = world_to_object(o);
	direction td = world_to_object(d);
	direction c = position(-to) + offset;
	float a = std::max(float(0.0), dot(normalise(td), c));
	float b = std::sqrt(std::pow(length(c), 2) - std::pow(a, 2));
	return (length(td) > a && a > 0 && b < radius);
}