//
// Created by chais on 02.08.15.
//

#include "sphere.h"

sphere::sphere(const float &radius, std::shared_ptr<direction> position, std::shared_ptr<material> matrl) : radius(
	radius), shape(position, matrl) {
	assert(radius > 0);
}

std::ostream &operator<<(std::ostream &out, const sphere &a) {
	out << "Radius: " << a.radius << ", Transformations: " << a.object_to_world;
	return out;
}

intersection sphere::intersect_full(const ray &r) {
	ray tr = this->world_to_object(r);
	direction c = point(-tr.o) + *this->offset;
	float a = std::max(float(0.0), dot(tr.d, c));
	float b = std::sqrt(std::pow(length(c), 2) - std::pow(a, 2));
	intersection out = intersection();
	if (b < this->radius - 1E-4) {
		float d = std::sqrt(std::pow(this->radius, 2) - std::pow(b, 2));
		std::shared_ptr<point> x;
		if (d < a - 1E-4)
			x = std::make_shared<point>(point(tr.o + direction(tr.d*(a - d))));
		else
			x = std::make_shared<point>(point(tr.o + direction(tr.d*(a + d))));
		std::shared_ptr<normal> norm = std::make_shared<normal>(normal(*x - *this->offset));
		float local_len = length(*norm);
		std::shared_ptr<vec2> local_pos = std::make_shared<vec2>(vec2((*norm)[0]/local_len, (*norm)[1]/local_len));
		*x = this->object_to_world(*x);
		*norm = normalise(this->object_to_world(*norm));
		out.object = shared_from_this();
		out.norm = norm;
		out.pos = x;
		out.local_pos = local_pos;
	}
	return out;
}

bool sphere::intersect_shadow(const point &o, const direction &d) const {
	if (d == direction())
		return false;
	point to = this->world_to_object(o);
	direction td = this->world_to_object(d);
	direction c = point(-to) + *this->offset;
	float a = std::max(float(0.0), dot(normalise(td), c));
	float b = std::sqrt(std::pow(length(c), 2) - std::pow(a, 2));
	return (length(td) > a && a > 0 && b < this->radius);
}