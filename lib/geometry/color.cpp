//
// Created by chais on 25.08.15.
//

#include "color.h"

color::color() {
	v = {0, 0, 0};
}

color::color(const float r, const float g, const float b) {
	v = {r, g, b};
}

color::color(const color &in) {
	v = {in[0], in[1], in[2]};
}

float &color::operator[](const unsigned long i) {
	assert(0 <= i && i <= 2);
	return this->v[i];
}

const float &color::operator[](const unsigned long i) const {
	assert(0 <= i && i <= 2);
	return this->v[i];
}

std::ostream &operator<<(std::ostream &out, const color &a) {
	out << "RGB: [" << a.v[0] << ", " << a.v[1] << ", " << a.v[2] << "]";
	return out;
}

color operator+(const color &lhs, const color &rhs) {
	return color(lhs[0] + rhs[0], lhs[1] + rhs[1], lhs[2] + rhs[2]);
}

color &operator+=(color &lhs, const color &rhs) {
	lhs[0] += rhs[0];
	lhs[1] += rhs[1];
	lhs[2] += rhs[2];
	return lhs;
}

color operator*(const color &lhs, const float &rhs) {
	return color(lhs[0]*rhs, lhs[1]*rhs, lhs[2]*rhs);
}

color operator*(const float &lhs, const color &rhs) {
	return color(lhs*rhs[0], lhs*rhs[1], lhs*rhs[2]);
}

color scale(const color &col, const std::array<float, 3> &sf) {
	return color(col[0]*sf[0], col[1]*sf[1], col[2]*sf[2]);
}

color scale(const color &col, const color &sf) {
	return color(col[0]*sf[0], col[1]*sf[1], col[2]*sf[2]);
}

std::array<unsigned char, 3> rgb(const color &col) {
	std::array<unsigned char, 3> out = {{
												static_cast<unsigned char>(col[0] > 1 ? 255 : std::round(col[0]*255)),
												static_cast<unsigned char>(col[1] > 1 ? 255 : std::round(col[1]*255)),
												static_cast<unsigned char>(col[2] > 1 ? 255 : std::round(col[2]*255))
							  }};
	return out;
}
