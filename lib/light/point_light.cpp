//
// Created by chais on 15.09.15.
//

#include "point_light.h"

point_light::point_light(const std::shared_ptr<color> &col, const std::shared_ptr<direction> &offset) : light(col),
																										shape(offset,
																											  std::shared_ptr<material>()) { }

const std::shared_ptr<direction> point_light::get_direction(const point &pos) const {
	return std::shared_ptr<direction>(new direction(pos - object_to_world(*offset)));
}

const std::shared_ptr<color> point_light::emit(const direction &dir) const {
	return emit_color;
}

intersection point_light::intersect_full(const ray &r) {
	return intersection();
}

bool point_light::intersect_shadow(const point &o, const direction &d) const {
	return false;
}
