//
// Created by chais on 25.08.15.
//

#include "position.h"

position::position() : vec4(0, 0, 0, 1) { }

position::position(const float &x, const float &y, const float &z) : vec4(x, y, z, 1) { }

position::position(const vec4 &in) : vec4(in[0], in[1], in[2], 1) { }

position::position(const position &in) : vec4(in) { }

position operator+(const position &lhs, const direction &rhs) {
	return position(dynamic_cast<const vec4 &>(lhs) + dynamic_cast<const vec4 &>(rhs));
}

position &operator+=(position &lhs, const direction &rhs) {
	dynamic_cast<vec4 &>(lhs) += dynamic_cast<const vec4 &>(rhs);
	return lhs;
}

direction operator-(const position &lhs, const position &rhs) {
	return direction(dynamic_cast<const vec4 &>(lhs) - dynamic_cast<const vec4 &>(rhs));
}

position operator-(const position &lhs, const direction &rhs) {
	return position(dynamic_cast<const vec4 &>(lhs) - dynamic_cast<const vec4 &>(rhs));
}
