//
// Created by chais on 06.08.15.
//

#include "ambient_light.h"

ambient_light::ambient_light(const vec3 &color) : color(color) { }

std::ostream &operator<<(std::ostream &out, const ambient_light &a) {
	out << "Ambient light: color [r, g, b]: " << to_color(a.color);
	return out;
}

const vec3 &ambient_light::getColor() const {
	return this->color;
}
