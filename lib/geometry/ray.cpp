//
// Created by chais on 23.07.15.
//

#include "ray.h"

ray::ray(const vec3 &origin, const vec3 &direction) : origin(origin), direction(normalise(direction)),
													  color(nullptr) { }

ray::ray(const vec3 &origin, const vec3 &direction, const vec3 &color) : origin(origin),
																		 direction(normalise(direction)),
																		 color(new vec3(color)) { }

/*ray::~ray() {
	if (this->color != nullptr)
		delete(this->color);
}*/

std::ostream &operator<<(std::ostream &out, const ray &a) {
	out << "origin: " << a.origin << " direction: " << a.direction;
	return out;
}

vec3 ray::getOrigin() const {
	return vec3(this->origin);
}

vec3 ray::getDirection() const {
	return vec3(this->direction);
}

vec3 *ray::getColor() const {
	return this->color;
}

void ray::setColor(const vec3 &color) {
	if (this->color == nullptr)
		this->color = new vec3(color);
	else
		*this->color = color;
}