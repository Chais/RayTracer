#include "vec2.h"

vec2::vec2() {
	std::fill(a, a+2, 0);
}

vec2::vec2(const double *in) {
	this->a[0] = in[0];
	this->a[1] = in[1];
}

vec2::vec2(const vec2 &in) {
	this->a[0] = in.a[0];
	this->a[1] = in.a[1];
}

vec2 &vec2::operator=(const vec2 &in) {
	this->a[0] = in.a[0];
	this->a[1] = in.a[1];
	return *this;
}

double &vec2::operator[](const int i) {
	if (i < 0 || i > 1)
		throw std::out_of_range("Index out of range.");
	return this->a[i];
}

const double &vec2::operator[](const int i) const {
	if (i < 0 || i > 1)
		throw std::out_of_range("Index out of range.");
	return this->a[i];
}

vec2 operator+(const vec2 &a, const vec2 &b) {
	double tmp[] = {
			a[0]+b[0],
			a[1]+b[1]
	};
	return vec2(tmp);
}

vec2 &operator+=(vec2 &a, const vec2 &b) {
	a[0] += b[0];
	a[1] += b[1];
	return a;
}

vec2 operator-(const vec2 &a, const vec2 &b) {
	double tmp[] = {
			a[0]-b[0],
			a[1]-b[1]
	};
	return vec2(tmp);
}

vec2 &operator-=(vec2 &a, const vec2 &b) {
	a[0] -= b[0];
	a[1] -= b[1];
	return a;
}

vec2 operator-(const vec2 &a) {
	double tmp[] = {
			-a[0],
			-a[1]
	};
	return vec2(tmp);
}

std::ostream &operator<<(std::ostream &out, const vec2 &a) {
	out << "[" << a.a[0] << ", " << a.a[1] << "]";
	return out;
}

vec2 operator*(const vec2 &lhs, const double rhs) {
	double tmp[] = {
			lhs[0]*rhs,
			lhs[1]*rhs
	};
	return vec2(tmp);
}

vec2 operator*(const double lhs, const vec2 &rhs) {
	double tmp[] = {
			lhs*rhs[0],
			lhs*rhs[1]
	};
	return vec2(tmp);
}

double dot(const vec2 &a, const vec2 &b) {
	return a[0]*b[0]+a[1]*b[1];
}

vec2 scale(const vec2 &a, const double *f) {
	double tmp[] = {
			a[0]*f[0],
			a[1]*f[1]
	};
	return vec2(tmp);
}

double length(const vec2 &a) {
	return sqrt(a[0]*a[0]+a[1]*a[1]);
}

vec2 normalise(const vec2 &a) {
	double l = length(a);
	double tmp[] = {
			a[0]/l,
			a[1]/l
	};
	return vec2(tmp);
}