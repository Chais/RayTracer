//
// Created by chais on 06.08.15.
//

#include "light.h"
#include "../geometry/direction.h"

light::light(const color &col) : col(col) { }

std::ostream &operator<<(std::ostream &out, const light &a) {
	out << "Ambient light: color [r, g, b]: " << rgb(a.col);
	return out;
}