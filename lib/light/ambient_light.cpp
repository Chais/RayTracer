//
// Created by chais on 26.08.15.
//

#include "ambient_light.h"

ambient_light::ambient_light(const std::shared_ptr<color> emit_col) : light(direction()), point(direction(),
																								std::shared_ptr<material>(
																										new solid_material(
																												emit_col,
																												std::shared_ptr<color>(
																														new color())))) { }

std::ostream &operator<<(std::ostream &out, const ambient_light &a) {
	out << "Ambient light: color [r, g, b]: " << a.matrl->get_emit_col();
	return out;
}

const std::shared_ptr<std::vector<intersection>> ambient_light::get_directions(const position &pos,
																			const unsigned long &samples) const {
	std::shared_ptr<std::vector<intersection>> out(new std::vector<intersection>());
	intersection i;
	i.pos = std::shared_ptr<position>(new position(pos));
	out->push_back(i);
	return out;
}

const std::shared_ptr<color> ambient_light::emit(const direction &dir, const intersection &is) const {
	return matrl->get_emit_col();
}

const std::shared_ptr<std::vector<ray>> ambient_light::shed(unsigned long samples) const {
	return std::shared_ptr<std::vector<ray>>(new std::vector<ray>());
}