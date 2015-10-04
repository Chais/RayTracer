//
// Created by chais on 06.08.15.
//

#include "parallel_light.h"

parallel_light::parallel_light(const std::shared_ptr<color> col, const std::shared_ptr<direction> dir) : light(col,
																											   dir) { }

std::ostream &operator<<(std::ostream &out, const parallel_light &a) {
	out << "Parallel light: color [r, g, b]: " << *a.col << ", direction: " << *a.dir;
	return out;
}

const std::shared_ptr<direction> parallel_light::get_direction(const point &pos) {
	return std::make_shared<direction>(*this->dir*std::numeric_limits<float>::max());
}

const std::shared_ptr<color> parallel_light::emit(const direction &dir) {
	return this->col;
}