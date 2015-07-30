#include <array>
#include "vec3.h"

vec3::vec3() {
	std::fill(a, a+3, 0);
}

vec3::vec3(const double x, const double y, const double z) {
	this->a[0] = x;
	this->a[1] = y;
	this->a[2] = z;
}

vec3::vec3(const double *in) {
	this->a[0] = in[0];
	this->a[1] = in[1];
	this->a[2] = in[2];
}

vec3::vec3(const vec3 &in) {
	this->a[0] = in.a[0];
	this->a[1] = in.a[1];
	this->a[2] = in.a[2];
}

vec3 &vec3::operator=(const vec3 &in) {
	this->a[0] = in.a[0];
	this->a[1] = in.a[1];
	this->a[2] = in.a[2];
	return *this;
}

double &vec3::operator[](const int i) {
	if (i < 0 || i > 2)
		throw std::out_of_range("Index out of range.");
	return this->a[i];
}

const double &vec3::operator[](const int i) const {
	if (i < 0 || i > 2)
		throw std::out_of_range("Index out of range.");
	return this->a[i];
}

vec3 operator+(const vec3 &a, const vec3 &b) {
	double tmp[] = {
			a[0]+b[0],
			a[1]+b[1],
			a[2]+b[2]
	};
	return vec3(tmp);
}

vec3 &operator+=(vec3 &a, const vec3 &b) {
	a[0] += b[0];
	a[1] += b[1];
	a[2] += b[2];
	return a;
}

vec3 operator-(const vec3 &a, const vec3 &b) {
	double tmp[] = {
			a[0]-b[0],
			a[1]-b[1],
			a[2]-b[2]
	};
	return vec3(tmp);
}

vec3 &operator-=(vec3 &a, const vec3 &b) {
	a[0] -= b[0];
	a[1] -= b[1];
	a[2] -= b[2];
	return a;
}

vec3 operator-(const vec3 &a) {
	double tmp[] = {
			-a[0],
			-a[1],
			-a[2]
	};
	return vec3(tmp);
}

std::ostream &operator<<(std::ostream &out, const vec3 &a) {
	out << "[" << a.a[0] << ", " << a.a[1] << ", " << a.a[2] << "]";
	return out;
}

vec3 operator*(const vec3 &lhs, const double rhs) {
	double tmp[] = {
			lhs[0]*rhs,
			lhs[1]*rhs,
			lhs[2]*rhs
	};
	return vec3(tmp);
}

vec3 operator*(const double lhs, const vec3 &rhs) {
	double tmp[] = {
			lhs*rhs[0],
			lhs*rhs[1],
			lhs*rhs[2]
	};
	return vec3(tmp);
}

vec3 &operator*=(vec3 &a, const double n) {
	a[0] *= n;
	a[1] *= n;
	a[2] *= n;
	return a;
}

double dot(const vec3 &a, const vec3 &b) {
	return a[0]*b[0]+a[1]*b[1]+a[2]*b[2];
}

vec3 cross(const vec3 &a, const vec3 &b) {
	double tmp[] = {
			a[1]*b[2]-a[2]*b[1],
			a[2]*b[0]-a[0]*b[2],
			a[0]*b[1]-a[1]*b[0]
	};
	return vec3(tmp);
}

vec3 scale(const vec3 &a, const double *f) {
	double tmp[] = {
			a[0]*f[0],
			a[1]*f[1],
			a[2]*f[2]
	};
	return vec3(tmp);
}

double length(const vec3 &a) {
	return sqrt(a[0]*a[0]+a[1]*a[1]+a[2]*a[2]);
}

vec3 normalise(const vec3 &a) {
	double l = length(a);
	double tmp[] = {
			a[0]/l,
			a[1]/l,
			a[2]/l
	};
	return vec3(tmp);
}

vec3 to_color(const vec3 &a) {
	vec3 out = normalise(a)*0.5;
	vec3 tmp{0.5, 0.5, 0.5};
	out = (out+tmp)*255;
	out[0] = round(out[0]);
	out[1] = round(out[1]);
	out[2] = round(out[2]);
	return out;
}
