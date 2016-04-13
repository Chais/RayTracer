//
// Created by chais on 15.09.15.
//

#include "point_light.h"

point_light::point_light(const std::shared_ptr<color> emit_col, const direction &offset) : light(direction()),
																						   point(direction(),
																								 std::shared_ptr<material>(
																										 new solid_material(
																												 emit_col,
																												 std::shared_ptr<color>(
																														 new color())))) { }

const std::shared_ptr<std::vector<direction>> point_light::get_directions(const position &pos,
																		  const unsigned long &samples) const {
	std::shared_ptr<std::vector<direction>> out(new std::vector<direction>());
	out->push_back(pos - object_to_world(offset));
	return out;
}

const std::shared_ptr<color> point_light::emit(const direction &dir) const {
	return matrl->get_emit_col();
}

intersection point_light::intersect_full(const ray &r) const {
	return intersection();
}

bool point_light::intersect_shadow(const position &o, const direction &d) const {
	return false;
}