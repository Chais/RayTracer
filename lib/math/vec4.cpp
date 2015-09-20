#include "vec4.h"

vec4::vec4() {
	a = {0, 0, 0, 0};
}

vec4::vec4(const float &x, const float &y, const float &z, const float &w) {
	a = {x, y, z, w};
}

vec4::vec4(const std::array<float, 4> &in) {
	a = {in[0], in[1], in[2], in[3]};
}

vec4::vec4(const vec4 &in) {
	a = {in.a[0], in.a[1], in.a[2], in.a[3]};
}

vec4 &vec4::operator=(const vec4 &in) {
	this->a[0] = in.a[0];
	this->a[1] = in.a[1];
	this->a[2] = in.a[2];
	this->a[3] = in.a[3];
	return *this;
}

float &vec4::operator[](const unsigned long i) {
	assert(0 <= i && i <= 3);
	return this->a[i];
}

const float &vec4::operator[](const unsigned long i) const {
	assert(0 <= i && i <= 3);
	return this->a[i];
}

vec4 operator+(const vec4 &lhs, const vec4 &rhs) {
	std::array<float, 4> tmp = {
			lhs[0]+rhs[0],
			lhs[1]+rhs[1],
			lhs[2]+rhs[2],
			lhs[3]+rhs[3]
	};
	return vec4(tmp);
}

vec4 &operator+=(vec4 &a, const vec4 &b) {
	a[0] += b[0];
	a[1] += b[1];
	a[2] += b[2];
	a[3] += b[3];
	return a;
}

vec4 operator-(const vec4 &a, const vec4 &b) {
	std::array<float, 4> tmp = {
			a[0]-b[0],
			a[1]-b[1],
			a[2]-b[2],
			a[3]-b[3]
	};
	return vec4(tmp);
}

vec4 &operator-=(vec4 &a, const vec4 &b) {
	a[0] -= b[0];
	a[1] -= b[1];
	a[2] -= b[2];
	a[3] -= b[3];
	return a;
}

vec4 operator-(const vec4 &rhs) {
	std::array<float, 4> tmp = {
			-rhs[0],
			-rhs[1],
			-rhs[2],
			-rhs[3]
	};
	return vec4(tmp);
}

std::ostream &operator<<(std::ostream &out, const vec4 &a) {
	out << "[" << a.a[0] << ", " << a.a[1] << ", " << a.a[2] << ", " << a.a[3] << "]";
	return out;
}

vec4 operator*(const vec4 &lhs, const float &rhs) {
	std::array<float, 4> tmp = {
			lhs[0]*rhs,
			lhs[1]*rhs,
			lhs[2]*rhs,
			lhs[3]*rhs
	};
	return vec4(tmp);
}

vec4 operator*(const float &lhs, const vec4 &rhs) {
	std::array<float, 4> tmp = {
			lhs*rhs[0],
			lhs*rhs[1],
			lhs*rhs[2],
			lhs*rhs[3]
	};
	return vec4(tmp);
}

bool operator==(const vec4 &lhs, const vec4 &rhs) {
	return helper::almost_equal(lhs[0], rhs[0], 1) && helper::almost_equal(lhs[1], rhs[1], 1) &&
		   helper::almost_equal(lhs[2], rhs[2], 1) && helper::almost_equal(lhs[3], rhs[3], 1);
}

bool operator!=(const vec4 &lhs, const vec4 &rhs) {
	return !(helper::almost_equal(lhs[0], rhs[0], 1) && helper::almost_equal(lhs[1], rhs[1], 1) &&
		   helper::almost_equal(lhs[2], rhs[2], 1) && helper::almost_equal(lhs[3], rhs[3], 1));
}

float dot(const vec4 &lhs, const vec4 &rhs) {
	return lhs[0]*rhs[0]+lhs[1]*rhs[1]+lhs[2]*rhs[2]+lhs[3]*rhs[3];
}

vec4 scale(const vec4 &a, const float f[4]) {
	std::array<float, 4> tmp = {
			a[0]*f[0],
			a[1]*f[1],
			a[2]*f[2],
			a[3]*f[3]
	};
	return vec4(tmp);
}

float length(const vec4 &a) {
	return std::sqrt(a[0]*a[0]+a[1]*a[1]+a[2]*a[2]+a[3]*a[3]);
}

vec4 normalise(const vec4 &a) {
	float il = 1/length(a);
	std::array<float, 4> tmp = {
			a[0]*il,
			a[1]*il,
			a[2]*il,
			a[3]*il
	};
	return vec4(tmp);
}
