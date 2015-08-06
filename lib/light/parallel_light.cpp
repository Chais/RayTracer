//
// Created by chais on 06.08.15.
//

#include "parallel_light.h"

parallel_light::parallel_light(const vec3 &color, const vec3 &direction) : ambient_light(color),
																		   direction(direction) { }

std::ostream &operator<<(std::ostream &out, const parallel_light &a) {
	out << "Parallel light: color [r, g, b]: " << to_color(a.color) << ", direction: " << a.direction;
	return out;
}

const vec3 &parallel_light::getDirection() const {
	return this->direction;
}
