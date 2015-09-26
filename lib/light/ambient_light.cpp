//
// Created by chais on 26.08.15.
//

#include "ambient_light.h"

ambient_light::ambient_light(const color *col) : light(col) { }

std::ostream &operator<<(std::ostream &out, const ambient_light &a) {
	out << "Ambient light: color [r, g, b]: " << *a.col;
	return out;
}

direction *ambient_light::get_direction(const point &pos) {
	return new direction(*this->dir);
}

color *ambient_light::emit(const direction &dir) {
	return new color(*this->col);
}