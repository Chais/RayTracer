//
// Created by chais on 06.08.15.
//

#include "light.h"

light::light(const std::shared_ptr<color> col) : col(col), dir(new direction()) { }

light::light(const std::shared_ptr<color> col, const std::shared_ptr<direction> dir)
	: col(col), dir(new direction(normalise(*dir))) { }