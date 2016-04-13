//
// Created by chais on 29/03/16.
//

#include "point.h"

point::point(const direction &offset, const std::shared_ptr<material> &matrl) : shape(offset, matrl) { }

intersection point::intersect_full(const ray &r) const {
	return intersection();
}

bool point::intersect_shadow(const position &o, const direction &d) const {
	return false;
}