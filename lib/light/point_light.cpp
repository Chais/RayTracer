//
// Created by chais on 15.09.15.
//

#include "point_light.h"

point_light::point_light(const color *col, const point *pos) : light(col), position(pos) { }

direction *point_light::get_direction(const point &pos) {
	return new direction(pos - *this->position);
}

color *point_light::emit(const direction &dir) {
	return new color(*this->col);
}