#include "vec4.h"

vec4::vec4() {
	std::fill(a, a+4, 0);
}

vec4::vec4(const double *in) {
	this->a[0] = in[0];
	this->a[1] = in[1];
	this->a[2] = in[2];
	this->a[3] = in[3];
}

vec4::vec4(const vec4 &in) {
	this->a[0] = in.a[0];
	this->a[1] = in.a[1];
	this->a[2] = in.a[2];
	this->a[3] = in.a[3];
}

vec4 &vec4::operator=(const vec4 &in) {
	this->a[0] = in.a[0];
	this->a[1] = in.a[1];
	this->a[2] = in.a[2];
	this->a[3] = in.a[3];
	return *this;
}

double &vec4::operator[](const int i) {
	if (i < 0 || i > 3)
		throw std::out_of_range("Index out of range.");
	return this->a[i];
}

const double &vec4::operator[](const int i) const {
	if (i < 0 || i > 3)
		throw std::out_of_range("Index out of range.");
	return this->a[i];
}

vec4 operator+(const vec4 &a, const vec4 &b) {
	double tmp[] = {
			a[0]+b[0],
			a[1]+b[1],
			a[2]+b[2],
			a[3]+b[3]
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
	double tmp[] = {
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

vec4 operator-(const vec4 &a) {
	double tmp[] = {
			-a[0],
			-a[1],
			-a[2],
			-a[3]
	};
	return vec4(tmp);
}

std::ostream &operator<<(std::ostream &out, const vec4 &a) {
	out << "[" << a.a[0] << ", " << a.a[1] << ", " << a.a[2] << ", " << a.a[3] << "]";
	return out;
}

vec4 operator*(const vec4 &lhs, const double rhs) {
	double tmp[] = {
			lhs[0]*rhs,
			lhs[1]*rhs,
			lhs[2]*rhs,
			lhs[3]*rhs
	};
	return vec4(tmp);
}

vec4 operator*(const double lhs, const vec4 &rhs) {
	double tmp[] = {
			lhs*rhs[0],
			lhs*rhs[1],
			lhs*rhs[2],
			lhs*rhs[3]
	};
	return vec4(tmp);
}

double dot(const vec4 &a, const vec4 &b) {
	return a[0]*b[0]+a[1]*b[1]+a[2]*b[2]+a[3]*b[3];
}

vec4 scale(const vec4 &a, const double *f) {
	double tmp[] = {
			a[0]*f[0],
			a[1]*f[1],
			a[2]*f[2],
			a[3]*f[3]
	};
	return vec4(tmp);
}

double length(const vec4 &a) {
	return sqrt(a[0]*a[0]+a[1]*a[1]+a[2]*a[2]+a[3]*a[3]);
}

vec4 normalise(const vec4 &a) {
	double l = length(a);
	double tmp[] = {
			a[0]/l,
			a[1]/l,
			a[2]/l,
			a[3]/l
	};
	return vec4(tmp);
}