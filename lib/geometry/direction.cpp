//
// Created by chais on 25.08.15.
//

#include "direction.h"

direction::direction() : vec4() { }

direction::direction(const float &x, const float &y, const float &z) : vec4(x, y, z, 0) { }

direction::direction(const vec4 &in) : vec4(in[0], in[1], in[2], 0) { }

direction::direction(const direction &in) : vec4(in) { }

std::ostream &operator<<(std::ostream &out, const direction &a) {
	out << vec4::operator<<(out, dynamic_cast<vec4>(a));
	return out;
}

direction operator+(const direction &lhs, const direction &rhs) {
	return direction(dynamic_cast<vec4>(lhs)+dynamic_cast<vec4>(rhs));
}

direction &operator+=(direction &lhs, const direction &rhs) {
	dynamic_cast<vec4>(lhs) += dynamic_cast<vec4>(rhs);
	return lhs;
}

direction operator-(const direction &lhs, const direction &rhs) {
	return direction(dynamic_cast<vec4>(lhs)-dynamic_cast<vec4>(rhs));
}

direction &operator-=(direction &lhs, const direction &rhs) {
	dynamic_cast<vec4>(lhs) -= dynamic_cast<vec4>(rhs);
	return lhs;
}

direction operator*(const direction &lhs, const float &rhs) {
	return direction(dynamic_cast<vec4>(lhs)*rhs);
}

direction operator*(const float &lhs, const direction &rhs) {
	return direction(lhs*dynamic_cast<vec4>(rhs));
}

direction &operator*=(direction &lhs, const float &rhs) {
	dynamic_cast<vec4>(lhs)*=rhs;
	return lhs;
}

float dot(const direction &lhs, const direction &rhs) {
	return dot(dynamic_cast<vec4>(lhs), dynamic_cast<vec4>(rhs));
}

direction cross(const direction &lhs, const direction &rhs) {
	return direction(lhs[1]*rhs[2]-lhs[2]*rhs[1], lhs[2]*rhs[0]-lhs[0]*rhs[2], lhs[0]*rhs[1]-lhs[1]*rhs[0]);
}