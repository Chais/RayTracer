//
// Created by chais on 26.08.15.
//

#include "ambient_light.h"

ambient_light::ambient_light(const std::shared_ptr<color> col) : light(col) { }

std::ostream &operator<<(std::ostream &out, const ambient_light &a) {
	out << "Ambient light: color [r, g, b]: " << *a.emit_color;
	return out;
}

const std::shared_ptr<direction> ambient_light::get_direction(const point &pos) const {
	return emit_dir;
}

const std::shared_ptr<color> ambient_light::emit(const direction &dir) const {
	return emit_color;
}