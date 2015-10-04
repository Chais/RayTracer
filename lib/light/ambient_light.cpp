//
// Created by chais on 26.08.15.
//

#include "ambient_light.h"

ambient_light::ambient_light(const std::shared_ptr<color> col) : light(col) { }

std::ostream &operator<<(std::ostream &out, const ambient_light &a) {
	out << "Ambient light: color [r, g, b]: " << *a.col;
	return out;
}

const std::shared_ptr<direction> ambient_light::get_direction(const point &pos) {
	return this->dir;
}

const std::shared_ptr<color> ambient_light::emit(const direction &dir) {
	return this->col;
}