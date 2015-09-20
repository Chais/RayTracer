#include "mat4.h"

mat4::mat4() {
	m = {{{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}};
}

mat4::mat4(const std::array<std::array<float, 4>, 4> &in) {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			m[i][j] = in[i][j];
}

mat4::mat4(const mat4 &in) {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			m[i][j] = in[i][j];
}

mat4 &mat4::operator=(const mat4 &in) {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			this->m[i][j] = in[i][j];
	return *this;
}

std::array<float, 4> mat4::operator[](const unsigned long i) {
	assert(0 <= i && i <= 3);
	return this->m[i];
}

const std::array<float, 4> mat4::operator[](const unsigned long i) const {
	assert(0 <= i && i <= 3);
	return this->m[i];
}

std::ostream &operator<<(std::ostream &out, const mat4 &a) {
	out << "[";
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			out << a.m[i][j];
			if (j != 3)
				out << ", ";
		}
		if (i != 3)
			out << ";";
	}
	out << "]";
	return out;
}

mat4 operator+(const mat4 &lhs, const mat4 &rhs) {
	std::array<std::array<float, 4>, 4> tmp;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			tmp[i][j] = lhs[i][j]+rhs[i][j];
	return mat4(tmp);
}

mat4 &operator+=(mat4 &lhs, const mat4 &rhs) {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			lhs[i][j] += rhs[i][j];
	return lhs;
}

mat4 operator-(const mat4 &lhs, const mat4 &rhs) {
	std::array<std::array<float, 4>, 4> tmp;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			tmp[i][j] = lhs[i][j]-rhs[i][j];
	return mat4(tmp);
}

mat4 &operator-=(mat4 &lhs, const mat4 &rhs) {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			lhs[i][j] -= rhs[i][j];
	return lhs;
}

mat4 operator-(const mat4 &rhs) {
	std::array<std::array<float, 4>, 4> tmp;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			tmp[i][j] = -rhs[i][j];
	return mat4(tmp);
}

mat4 operator*(const mat4 &lhs, const float &rhs) {
	std::array<std::array<float, 4>, 4> tmp;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			tmp[i][j] = lhs[i][j]*rhs;
	return mat4(tmp);
}

mat4 operator*(const float &lhs, const mat4 &rhs) {
	std::array<std::array<float, 4>, 4> tmp;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			tmp[i][j] = rhs[i][j]*lhs;
	return mat4(tmp);
}

vec4 operator*(const mat4 &lhs, const vec4 &rhs) {
	std::array<float, 4> tmp;
	for (int i = 0; i < 4; i++)
		tmp[i] = lhs[i][0]*rhs[0]+lhs[i][1]*rhs[1]+lhs[i][2]*rhs[2]+lhs[i][3]*rhs[3];
	return vec4(tmp);
}

vec4 operator*(const vec4 &a, const mat4 &b) {
	std::array<float, 4> tmp;
	for (int i = 0; i < 4; i++)
		tmp[i] = a[0]*b[0][i]+a[1]*b[1][i]+a[2]*b[2][i]+a[3]*b[3][i];
	return vec4(tmp);
}

mat4 operator*(const mat4 &a, const mat4 &b) {
	std::array<std::array<float, 4>, 4> tmp;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			tmp[i][j] = a[i][0]*b[0][j]+a[i][1]*b[1][j]+a[i][2]*b[2][j]+a[i][3]*b[3][j];
	return mat4(tmp);
}

mat4 &operator*=(mat4 &a, const float &n) {
	for (int i = 0; i < 16; i += 4) {
		a[i][0] *= n;
		a[i][1] *= n;
		a[i][2] *= n;
		a[i][3] *= n;
	}
	return a;
}

mat4 invert(const mat4 &a) {
	float idet = 1/(a[0][0]*a[1][1]*a[2][2]*a[3][3]+a[0][0]*a[1][2]*a[2][3]*a[3][1]+
					a[0][0]*a[1][3]*a[2][1]*a[3][2]+a[0][1]*a[1][0]*a[2][3]*a[3][2]+
					a[0][1]*a[1][2]*a[2][0]*a[3][3]+a[0][1]*a[1][3]*a[2][2]*a[3][0]+
					a[0][2]*a[1][0]*a[2][1]*a[3][3]+a[0][2]*a[1][1]*a[2][3]*a[3][0]+
					a[0][2]*a[1][3]*a[2][0]*a[3][1]+a[0][3]*a[1][0]*a[2][2]*a[3][1]+
					a[0][3]*a[1][1]*a[2][0]*a[3][2]+a[0][3]*a[1][2]*a[2][1]*a[3][0]-
					a[0][0]*a[1][1]*a[2][3]*a[3][2]-a[0][0]*a[1][2]*a[2][1]*a[3][3]-
					a[0][0]*a[1][3]*a[2][2]*a[3][1]-a[0][1]*a[1][0]*a[2][2]*a[3][3]-
					a[0][1]*a[1][2]*a[2][3]*a[3][0]-a[0][1]*a[1][3]*a[2][0]*a[3][2]-
					a[0][2]*a[1][0]*a[2][3]*a[3][1]-a[0][2]*a[1][1]*a[2][0]*a[3][3]-
					a[0][2]*a[1][3]*a[2][1]*a[3][0]-a[0][3]*a[1][0]*a[2][1]*a[3][2]-
					a[0][3]*a[1][1]*a[2][2]*a[3][0]-a[0][3]*a[1][2]*a[2][0]*a[3][1]);
	std::array<std::array<float, 4>, 4> tmp = {{
			{(a[1][1]*a[2][2]*a[3][3]+a[1][2]*a[2][3]*a[3][1]+a[1][3]*a[2][1]*a[3][2]-
			  a[1][1]*a[2][3]*a[3][2]-a[1][2]*a[2][1]*a[3][3]-a[1][3]*a[2][2]*a[3][1])*idet,
			 (a[0][1]*a[2][3]*a[3][2]+a[0][2]*a[2][1]*a[3][3]+a[0][3]*a[2][2]*a[3][1]-
			  a[0][1]*a[2][2]*a[3][3]-a[0][2]*a[2][3]*a[3][1]-a[0][3]*a[2][1]*a[3][2])*idet,
			 (a[0][1]*a[1][2]*a[3][3]+a[0][2]*a[1][3]*a[3][1]+a[0][3]*a[1][1]*a[3][2]-
			  a[0][1]*a[1][3]*a[3][2]-a[0][2]*a[1][1]*a[3][3]-a[0][3]*a[1][2]*a[3][1])*idet,
			 (a[0][1]*a[1][3]*a[2][2]+a[0][2]*a[1][1]*a[2][3]+a[0][3]*a[1][2]*a[2][1]-
			  a[0][1]*a[1][2]*a[2][3]-a[0][2]*a[1][3]*a[2][1]-a[0][3]*a[1][1]*a[2][2])*idet},
			{(a[1][0]*a[2][3]*a[3][2]+a[1][2]*a[2][0]*a[3][3]+a[1][3]*a[2][2]*a[3][0]-
			  a[1][0]*a[2][2]*a[3][3]-a[1][2]*a[2][3]*a[3][0]-a[1][3]*a[2][0]*a[3][2])*idet,
			 (a[0][0]*a[2][2]*a[3][3]+a[0][2]*a[2][3]*a[3][0]+a[0][3]*a[2][0]*a[3][2]-
			  a[0][0]*a[2][3]*a[3][2]-a[0][2]*a[2][0]*a[3][3]-a[0][3]*a[2][2]*a[3][0])*idet,
			 (a[0][0]*a[1][3]*a[3][2]+a[0][2]*a[1][0]*a[3][3]+a[0][3]*a[1][2]*a[3][0]-
			  a[0][0]*a[1][2]*a[3][3]-a[0][2]*a[1][3]*a[3][0]-a[0][3]*a[1][0]*a[3][2])*idet,
			 (a[0][0]*a[1][2]*a[2][3]+a[0][2]*a[1][3]*a[2][0]+a[0][3]*a[1][0]*a[2][2]-
			  a[0][0]*a[1][3]*a[2][2]-a[0][2]*a[1][0]*a[2][3]-a[0][3]*a[1][2]*a[2][0])*idet},
			{(a[1][0]*a[2][1]*a[3][3]+a[1][1]*a[2][3]*a[3][0]+a[1][3]*a[2][0]*a[3][1]-
			  a[1][0]*a[2][3]*a[3][1]-a[1][1]*a[2][0]*a[3][3]-a[1][3]*a[2][1]*a[3][0])*idet,
			 (a[0][0]*a[2][3]*a[3][1]+a[0][1]*a[2][0]*a[3][3]+a[0][3]*a[2][1]*a[3][0]-
			  a[0][0]*a[2][1]*a[3][3]-a[0][1]*a[2][3]*a[3][0]-a[0][3]*a[2][0]*a[3][1])*idet,
			 (a[0][0]*a[1][1]*a[3][3]+a[0][1]*a[1][3]*a[3][0]+a[0][3]*a[1][0]*a[3][1]-
			  a[0][0]*a[1][3]*a[3][1]-a[0][1]*a[1][0]*a[3][3]-a[0][3]*a[1][1]*a[3][0])*idet,
			 (a[0][0]*a[1][3]*a[2][1]+a[0][1]*a[1][0]*a[2][3]+a[0][3]*a[1][1]*a[2][0]-
			  a[0][0]*a[1][1]*a[2][3]-a[0][1]*a[1][3]*a[2][0]-a[0][3]*a[1][0]*a[2][1])*idet},
			{(a[1][0]*a[2][2]*a[3][1]+a[1][1]*a[2][0]*a[3][2]+a[1][2]*a[2][1]*a[3][0]-
			  a[1][0]*a[2][1]*a[3][2]-a[1][1]*a[2][2]*a[3][0]-a[1][2]*a[2][0]*a[3][1])*idet,
			 (a[0][0]*a[2][1]*a[3][2]+a[0][1]*a[2][2]*a[3][0]+a[0][2]*a[2][0]*a[3][1]-
			  a[0][0]*a[2][2]*a[3][1]-a[0][1]*a[2][0]*a[3][2]-a[0][2]*a[2][1]*a[3][0])*idet,
			 (a[0][0]*a[1][2]*a[3][1]+a[0][1]*a[1][0]*a[3][2]+a[0][2]*a[1][1]*a[3][0]-
			  a[0][0]*a[1][1]*a[3][2]-a[0][1]*a[1][2]*a[3][0]-a[0][2]*a[1][0]*a[3][1])*idet,
			 (a[0][0]*a[1][1]*a[2][2]+a[0][1]*a[1][2]*a[2][0]+a[0][2]*a[1][0]*a[2][1]-
			  a[0][0]*a[1][2]*a[2][1]-a[0][1]*a[1][0]*a[2][2]-a[0][2]*a[1][1]*a[2][0])*idet}
	}};
	return mat4(tmp);
}

mat4 transpose(const mat4 &a) {
	std::array<std::array<float, 4>, 4> tmp;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			tmp[j][i] = a[i][j];
	return mat4(tmp);
}