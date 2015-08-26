//
// Created by chais on 06.08.15.
//

#include "parallel_light.h"

parallel_light::parallel_light(const color &col, const direction &dir) : light(col), dir(dir) { }

std::ostream &operator<<(std::ostream &out, const parallel_light &a) {
	out << "Parallel light: color [r, g, b]: " << rgb(a.col) << ", direction: " << a.dir;
	return out;
}

const direction &parallel_light::get_direction() const {
	return this->dir;
}

color &parallel_light::emit(const direction &dir) const {
	return this->col;
}
