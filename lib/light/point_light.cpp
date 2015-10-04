//
// Created by chais on 15.09.15.
//

#include "point_light.h"

point_light::point_light(const std::shared_ptr<color> col, const std::shared_ptr<point> pos)
	: light(col), position(pos) { }

const std::shared_ptr<direction> point_light::get_direction(const point &pos) {
	return std::shared_ptr<direction>(new direction(pos - *this->position));
}

const std::shared_ptr<color> point_light::emit(const direction &dir) {
	return this->col;
}