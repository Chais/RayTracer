//
// Created by chais on 06.08.15.
//

#include "light.h"

light::light(const std::shared_ptr<color> col) : emit_color(col), emit_dir(new direction()) { }

light::light(const std::shared_ptr<color> col, const std::shared_ptr<direction> dir)
	: emit_color(col), emit_dir(new direction(normalise(*dir))) { }