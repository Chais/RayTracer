#include "vec2.h"

vec2::vec2() {
	a = {0, 0};
}

vec2::vec2(const float &u, const float &v) {
	a = {u, v};
}

vec2::vec2(const std::array<const float, 2> &in) {
	a = {in[0], in[1]};
}

vec2::vec2(const vec2 &in) {
	a = {in[0], in[1]};
}

vec2 &vec2::operator=(const vec2 &in) {
	this->a[0] = in.a[0];
	this->a[1] = in.a[1];
	return *this;
}

float &vec2::operator[](const unsigned long i) {
	assert(0 <= i <= 1);
	return this->a[i];
}

const float &vec2::operator[](const unsigned long i) const {
	assert(0 <= i <= 1);
	return this->a[i];
}

vec2 operator+(const vec2 &lhs, const vec2 &rhs) {
	std::array<float, 2> tmp = {
			lhs[0]+rhs[0],
			lhs[1]+rhs[1]
	};
	return vec2(tmp);
}

vec2 &operator+=(vec2 &lhs, const vec2 &rhs) {
	lhs[0] += rhs[0];
	lhs[1] += rhs[1];
	return lhs;
}

vec2 operator-(const vec2 &lhs, const vec2 &rhs) {
	std::array<const float, 2> tmp = {
			lhs[0]-rhs[0],
			lhs[1]-rhs[1]
	};
	return vec2(tmp);
}

vec2 &operator-=(vec2 &lhs, const vec2 &rhs) {
	lhs[0] -= rhs[0];
	lhs[1] -= rhs[1];
	return lhs;
}

vec2 operator-(const vec2 &rhs) {
	std::array<const float, 2> tmp = {
			-rhs[0],
			-rhs[1]
	};
	return vec2(tmp);
}

std::ostream &operator<<(std::ostream &out, const vec2 &a) {
	out << "[" << a.a[0] << ", " << a.a[1] << "]";
	return out;
}

vec2 operator*(const vec2 &lhs, const float &rhs) {
	std::array<const float, 2> tmp = {
			lhs[0]*rhs,
			lhs[1]*rhs
	};
	return vec2(tmp);
}

vec2 operator*(const float &lhs, const vec2 &rhs) {
	std::array<const float, 2> tmp = {
			lhs*rhs[0],
			lhs*rhs[1]
	};
	return vec2(tmp);
}

float dot(const vec2 &lhs, const vec2 &rhs) {
	return lhs[0]*rhs[0]+lhs[1]*rhs[1];
}

vec2 scale(const vec2 &a, const float f[2]) {
	std::array<const float, 2> tmp = {
			a[0]*f[0],
			a[1]*f[1]
	};
	return vec2(tmp);
}

float length(const vec2 &a) {
	return std::sqrt(a[0]*a[0]+a[1]*a[1]);
}

vec2 normalise(const vec2 &a) {
	float il = 1/length(a);
	std::array<const float, 2> tmp = {
			a[0]*il,
			a[1]*il
	};
	return vec2(tmp);
}