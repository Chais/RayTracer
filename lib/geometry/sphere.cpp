//
// Created by chais on 02.08.15.
//

#include "sphere.h"

sphere::sphere(double radius) : radius(radius) {
	if (radius <= 0)
		throw new geometry_exception("The radius has to be greater than zero.");
}

std::ostream &operator<<(std::ostream &out, const sphere &a) {
	out << "Radius: " << a.radius << ", Transformations: " << a.transforms << ", inverse transformations: " <<
	a.inv_trans;;
	return out;
}

ray sphere::intersect(ray r) {
	mat4 m = this->getTransforms();
	mat4 im = this->getInvTransforms();
	ray tr = ray(transform(im, r.getOrigin()), transform(im, r.getDirection()));
	vec3 c = this->getPosition()-tr.getOrigin();
	double a = std::max(0.0, dot(tr.getDirection(), c));
	double b = std::sqrt(std::pow(length(c), 2)-std::pow(a, 2));
	if (b < this->radius-1E-12) {
		double d = std::sqrt(std::pow(this->radius, 2)-std::pow(b, 2));
		vec3 x;
		if (d < a-1E-12)
			x = tr.getOrigin()+tr.getDirection()*(a-d);
		else
			x = tr.getOrigin()+tr.getDirection()*(a+d);
		x = transform(m, x);
		vec3 dir = x-this->getPosition();
		dir = transform(im, dir);
		vec3 col{1, 1, 1};
		return ray(x, dir, col);
	}
	throw geometry_exception("No intersection");
}

bool sphere::getShadow(vec3 origin, vec3 direction) {
	return false;
}
