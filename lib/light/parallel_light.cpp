//
// Created by chais on 06.08.15.
//

#include "parallel_light.h"

parallel_light::parallel_light(const color *col, const direction *dir) : light(col, dir) { }

std::ostream &operator<<(std::ostream &out, const parallel_light &a) {
	out << "Parallel light: color [r, g, b]: " << *a.col << ", direction: " << *a.dir;
	return out;
}

direction *parallel_light::get_direction(const point &pos) {
	return new direction(*this->dir);
}

color *parallel_light::emit(const direction &dir) {
	return new color(*this->col);
}
