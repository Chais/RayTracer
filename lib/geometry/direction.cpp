//
// Created by chais on 25.08.15.
//

#include "direction.h"

direction::direction() : vec4() { }

direction::direction(const float &x, const float &y, const float &z) : vec4(x, y, z, 0) { }

direction::direction(const vec4 &in) : vec4(in[0], in[1], in[2], 0) { }

direction::direction(const direction &in) : vec4(in) { }

direction cross(const direction &lhs, const direction &rhs) {
	return direction(lhs[1]*rhs[2]-lhs[2]*rhs[1], lhs[2]*rhs[0]-lhs[0]*rhs[2], lhs[0]*rhs[1]-lhs[1]*rhs[0]);
}