//
// Created by chais on 25.08.15.
//

#include "point.h"

point::point() : vec4(0, 0, 0, 1) { }

point::point(const float &x, const float &y, const float &z) : vec4(x, y, z, 1) { }

point::point(const vec4 &in) : vec4(in[0], in[1], in[2], 1) { }

point::point(const point &in) : vec4(in) { }

point operator+(const point &lhs, const direction &rhs) {
	return point(dynamic_cast<const vec4 &>(lhs)+dynamic_cast<const vec4 &>(rhs));
}

point &operator+=(point &lhs, const direction &rhs) {
	dynamic_cast<vec4 &>(lhs) += dynamic_cast<const vec4 &>(rhs);
	return lhs;
}

direction operator-(const point &lhs, const point &rhs) {
	return direction(dynamic_cast<const vec4 &>(lhs)-dynamic_cast<const vec4 &>(rhs));
}

point operator-(const point &lhs, const direction &rhs) {
	return point(dynamic_cast<const vec4 &>(lhs)-dynamic_cast<const vec4 &>(rhs));
}
