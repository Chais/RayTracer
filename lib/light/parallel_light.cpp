//
// Created by chais on 06.08.15.
//

#include "parallel_light.h"

parallel_light::parallel_light(const std::shared_ptr<color> &col, const std::shared_ptr<direction> &dir)
		: light(col, dir), shape(std::shared_ptr<direction>(new direction()),
				std::shared_ptr<material>()) { }

std::ostream &operator<<(std::ostream &out, const parallel_light &a) {
	out << "Parallel light: color [r, g, b]: " << *a.emit_color << ", direction: " << *a.emit_dir;
	return out;
}

const std::shared_ptr<direction> parallel_light::get_direction(const point &pos) const {
	return std::make_shared<direction>(object_to_world(*emit_dir) * std::numeric_limits<float>::max());
}

const std::shared_ptr<color> parallel_light::emit(const direction &dir) const {
	return emit_color;
}

intersection parallel_light::intersect_full(const ray &r) {
	return intersection();
}

bool parallel_light::intersect_shadow(const point &o, const direction &d) const {
	return false;
}
