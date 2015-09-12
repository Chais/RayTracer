//
// Created by chais on 02.08.15.
//

#include "sphere.h"

sphere::sphere(float radius, material *matrl) : radius(radius), shape(matrl) {
	assert(radius > 0);
}

std::ostream &operator<<(std::ostream &out, const sphere &a) {
	out << "Radius: " << a.radius << ", Transformations: " << a.object_to_world;
	return out;
}

intersection sphere::intersect_full(const ray &r) {
	ray tr = this->world_to_object(r);
	direction c = -tr.o;
	float a = std::max(float(0.0), dot(tr.d, c));
	float b = std::sqrt(std::pow(length(c), 2)-std::pow(a, 2));
	intersection out = intersection();
	if (b < this->radius-1E-7) {
		float d = std::sqrt(std::pow(this->radius, 2)-std::pow(b, 2));
		point *x;
		if (d < a-1E-7)
			x = new point(tr.o+direction(tr.d*(a-d)));
		else
			x = new point(tr.o+direction(tr.d*(a+d)));
		normal *norm = new normal(*x);
		float local_len = length(direction(*x));
		vec2 *local_pos = new vec2((*x)[0]/local_len, (*x)[1]/local_len);
		*x = this->object_to_world(*x);
		*norm = normalise(this->object_to_world(*norm));
		out.object = this;
		out.norm = norm;
		out.pos = x;
		out.local_pos = local_pos;
	}
	return out;
}

bool sphere::intersect_shadow(const ray &r) {
	ray tr = this->world_to_object(r);
	direction c = -tr.o;
	float a = std::max(float(0.0), dot(tr.d, c));
	float b = std::sqrt(std::pow(length(c), 2)-std::pow(a, 2));
	return (a > 0 && b < this->radius);
}
