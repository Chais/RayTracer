//
// Created by chais on 26.08.15.
//

#include "ambient_light.h"

ambient_light::ambient_light(color col) : light(col) {}

std::ostream &operator<<(std::ostream &out, const ambient_light &a) {
	out << "Ambient light: color [r, g, b]: " << rgb(a.col) << ", direction: " << a.dir;
	return out;
}
color &ambient_light::emit(const direction &dir) const {
	return this->col;
}
