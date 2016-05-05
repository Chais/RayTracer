//
// Created by chais on 06.08.15.
//

#include "parallel_light.h"

parallel_light::parallel_light(const std::shared_ptr<color> emit_col, const direction &emit_dir) : light(
		emit_dir), point(direction(), std::shared_ptr<material>(
		new solid_material(emit_col, std::shared_ptr<color>(new color())))) { }

std::ostream &operator<<(std::ostream &out, const parallel_light &a) {
	out << "Parallel light: color [r, g, b]: " << a.matrl->get_emit_col() << ", direction: " << a.emit_dir;
	return out;
}

const std::shared_ptr<std::vector<direction>> parallel_light::get_directions(const position &pos,
																			 const unsigned long &samples) const {
	std::shared_ptr<std::vector<direction>> out(new std::vector<direction>());
	out->push_back(object_to_world(emit_dir) * std::numeric_limits<float>::max());
	return out;
}

const std::shared_ptr<color> parallel_light::emit(const direction &dir) const {
	return matrl->get_emit_col();
}

intersection parallel_light::intersect_full(const ray &r) const {
	return intersection();
}

bool parallel_light::intersect_shadow(const position &o, const direction &d) const {
	return false;
}

const std::shared_ptr<std::vector<ray>> parallel_light::shed(unsigned long samples) const {
	return std::shared_ptr<std::vector<ray>>(new std::vector<ray>());
}