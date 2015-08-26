//
// Created by chais on 02.08.15.
//

#include "shape.h"

shape::shape(material *matrl) : transforms(transform()), matrl(matrl) { }

color shape::shade(const direction &l, const normal &n, const direction &v, const vec2 &pos, const bool internal) {
	return this->matrl->shade(l, n, v, pos, internal);
}
