#include "mat4.h"

mat4::mat4() {
	for (int i = 0; i < 15; i += 5) {
		this->a[i] = 1;
		std::fill(a+i+1, a+i+4, 0);
	}
	this->a[15] = 1;
}

mat4::mat4(const double *in) {
	for (int i = 0; i < 16; i += 4) {
		this->a[i] = in[i];
		this->a[i+1] = in[i+1];
		this->a[i+2] = in[i+2];
		this->a[i+3] = in[i+3];
	}
}

mat4::mat4(const mat4 &in) {
	for (int i = 0; i < 16; i += 4) {
		this->a[i] = in[i];
		this->a[i+1] = in[i+1];
		this->a[i+2] = in[i+2];
		this->a[i+3] = in[i+3];
	}
}

mat4 &mat4::operator=(const mat4 &in) {
	for (int i = 0; i < 16; i += 4) {
		this->a[i] = in[i];
		this->a[i+1] = in[i+1];
		this->a[i+2] = in[i+2];
		this->a[i+3] = in[i+3];
	}
	return *this;
}

double &mat4::operator[](const int i) {
	if (i < 0 || i > 15)
		throw std::out_of_range("Index out of range.");
	return this->a[i];
}

const double &mat4::operator[](const int i) const {
	if (i < 0 || i > 15)
		throw std::out_of_range("Index out of range.");
	return this->a[i];
}

std::ostream &operator<<(std::ostream &out, const mat4 &a) {
	out << "[";
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			out << a.a[i*4+j];
			if (j != 3)
				out << ", ";
		}
		if (i != 3)
			out << ";";
	}
	out << "]";
	return out;
}

mat4 operator+(const mat4 &a, const mat4 &b) {
	double *tmp = new double[16];
	for (int i = 0; i < 16; i += 4) {
		tmp[i] = a[i]+b[i];
		tmp[i+1] = a[i+1]+b[i+1];
		tmp[i+2] = a[i+2]+b[i+2];
		tmp[i+3] = a[i+3]+b[i+3];
	}
	return mat4(tmp);
}

mat4 &operator+=(mat4 &a, const mat4 &b) {
	for (int i = 0; i < 16; i += 4) {
		a[i] += b[i];
		a[i+1] += b[i+1];
		a[i+2] += b[i+2];
		a[i+3] += b[i+3];
	}
	return a;
}

mat4 operator-(const mat4 &a, const mat4 &b) {
	double *tmp = new double[16];
	for (int i = 0; i < 16; i += 4) {
		tmp[i] = a[i]-b[i];
		tmp[i+1] = a[i+1]-b[i+1];
		tmp[i+2] = a[i+2]-b[i+2];
		tmp[i+3] = a[i+3]-b[i+3];
	}
	return mat4(tmp);
}

mat4 &operator-=(mat4 &a, const mat4 &b) {
	for (int i = 0; i < 16; i += 4) {
		a[i] -= b[i];
		a[i+1] -= b[i+1];
		a[i+2] -= b[i+2];
		a[i+3] -= b[i+3];
	}
	return a;
}

mat4 operator-(const mat4 &a) {
	double *tmp = new double[16];
	for (int i = 0; i < 16; i += 4) {
		tmp[i] = -a[i];
		tmp[i+1] = -a[i+1];
		tmp[i+2] = -a[i+2];
		tmp[i+3] = -a[i+3];
	}
	return mat4(tmp);
}

mat4 operator*(const mat4 &a, const double n) {
	double *tmp = new double[16];
	for (int i = 0; i < 16; i += 4) {
		tmp[i] = a[i]*n;
		tmp[i+1] = a[i+1]*n;
		tmp[i+2] = a[i+2]*n;
		tmp[i+3] = a[i+3]*n;
	}
	return mat4(tmp);
}

vec4 operator*(const mat4 &a, const vec4 &b) {
	double tmp[4];
	for (int i = 0; i < 4; i++)
		tmp[i] = a[i*4]*b[0]+a[i*4+1]*b[1]+a[i*4+2]*b[2]+a[i*4+3]*b[3];
	return vec4(tmp);
}

vec3 operator*(const mat4 &a, const vec3 &b) {
	double tmp[3];
	for (int i = 0; i < 3; i++)
		tmp[i] = a[i*4]*b[0]+a[i*4+1]*b[1]+a[i*4+2]*b[2]+a[i*4+3];
	return vec3(tmp);
}

vec4 operator*(const vec4 &a, const mat4 &b) {
	double tmp[4];
	for (int i = 0; i < 4; i++)
		tmp[i] = a[0]*b[i]+a[1]*b[i+4]+a[2]*b[i+8]+a[3]*b[i+12];
	return vec4(tmp);
}

mat4 operator*(const mat4 &a, const mat4 &b) {
	double tmp[16];
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			tmp[i*4+j] = a[i*4]*b[j*4]+a[i*4+1]*b[j*4+1]+a[i*4+2]*b[j*4+2]+a[i*4+3]*b[j*4+3];
	return mat4(tmp);
}

mat4 &operator*=(mat4 &a, const mat4 &b) {
	a = a*b;
	return a;
}

mat4 &operator*=(mat4 &a, const double n) {
	for (int i = 0; i < 16; i += 4) {
		a[i] *= n;
		a[i+1] *= n;
		a[i+2] *= n;
		a[i+3] *= n;
	}
	return a;
}

mat4 invert(const mat4 &a) {
	double det = a[0]*a[5]*a[10]*a[15]+a[0]*a[6]*a[11]*a[13]+
				 a[0]*a[7]*a[9]*a[14]+a[1]*a[4]*a[11]*a[14]+
				 a[1]*a[6]*a[8]*a[15]+a[1]*a[7]*a[10]*a[12]+
				 a[2]*a[4]*a[9]*a[15]+a[2]*a[5]*a[11]*a[12]+
				 a[2]*a[7]*a[8]*a[13]+a[3]*a[4]*a[10]*a[13]+
				 a[3]*a[5]*a[8]*a[14]+a[3]*a[6]*a[9]*a[12]-
				 a[0]*a[5]*a[11]*a[14]-a[0]*a[6]*a[9]*a[15]-
				 a[0]*a[7]*a[10]*a[13]-a[1]*a[4]*a[10]*a[15]-
				 a[1]*a[6]*a[11]*a[12]-a[1]*a[7]*a[8]*a[14]-
				 a[2]*a[4]*a[11]*a[13]-a[2]*a[5]*a[8]*a[15]-
				 a[2]*a[7]*a[9]*a[12]-a[3]*a[4]*a[9]*a[14]-
				 a[3]*a[5]*a[10]*a[12]-a[3]*a[6]*a[8]*a[13];
	double tmp[] = {
			(a[5]*a[10]*a[15]+a[6]*a[11]*a[13]+a[7]*a[9]*a[14]-
			 a[5]*a[11]*a[14]-a[6]*a[9]*a[15]-a[7]*a[10]*a[13])/
			det,
			(a[1]*a[11]*a[14]+a[2]*a[9]*a[15]+a[3]*a[10]*a[13]-
			 a[1]*a[10]*a[15]-a[2]*a[11]*a[13]-a[3]*a[9]*a[14])/
			det,
			(a[1]*a[6]*a[15]+a[2]*a[7]*a[13]+a[3]*a[5]*a[14]-
			 a[1]*a[7]*a[14]-a[2]*a[5]*a[15]-a[3]*a[6]*a[13])/det,
			(a[1]*a[7]*a[10]+a[2]*a[5]*a[11]+a[3]*a[6]*a[9]-
			 a[1]*a[6]*a[11]-a[2]*a[7]*a[9]-a[3]*a[5]*a[10])/det,
			(a[4]*a[11]*a[14]+a[6]*a[8]*a[15]+a[7]*a[10]*a[12]-
			 a[4]*a[10]*a[15]-a[6]*a[11]*a[12]-a[7]*a[8]*a[14])/
			det,
			(a[0]*a[10]*a[15]+a[2]*a[11]*a[12]+a[3]*a[8]*a[14]-
			 a[0]*a[11]*a[14]-a[2]*a[8]*a[15]-a[3]*a[10]*a[12])/
			det,
			(a[0]*a[7]*a[14]+a[2]*a[4]*a[15]+a[3]*a[6]*a[12]-
			 a[0]*a[6]*a[15]-a[2]*a[7]*a[12]-a[3]*a[4]*a[14])/det,
			(a[0]*a[6]*a[11]+a[2]*a[7]*a[8]+a[3]*a[4]*a[10]-
			 a[0]*a[7]*a[10]-a[2]*a[4]*a[11]-a[3]*a[6]*a[8])/det,
			(a[4]*a[9]*a[15]+a[5]*a[11]*a[12]+a[7]*a[8]*a[13]-
			 a[4]*a[11]*a[13]-a[5]*a[8]*a[15]-a[7]*a[9]*a[12])/
			det,
			(a[0]*a[11]*a[13]+a[1]*a[8]*a[15]+a[3]*a[9]*a[12]-
			 a[0]*a[9]*a[15]-a[1]*a[11]*a[12]-a[3]*a[8]*a[13])/
			det,
			(a[0]*a[5]*a[15]+a[1]*a[7]*a[12]+a[3]*a[4]*a[13]-
			 a[0]*a[7]*a[13]-a[1]*a[4]*a[15]-a[3]*a[5]*a[12])/det,
			(a[0]*a[7]*a[9]+a[1]*a[4]*a[11]+a[3]*a[5]*a[8]-
			 a[0]*a[5]*a[11]-a[1]*a[7]*a[8]-a[3]*a[4]*a[9])/det,
			(a[4]*a[10]*a[13]+a[5]*a[8]*a[14]+a[6]*a[9]*a[12]-
			 a[4]*a[9]*a[14]-a[5]*a[10]*a[12]-a[6]*a[8]*a[13])/
			det,
			(a[0]*a[9]*a[14]+a[1]*a[10]*a[12]+a[2]*a[8]*a[13]-
			 a[0]*a[10]*a[13]-a[1]*a[8]*a[14]-a[2]*a[9]*a[12])/
			det,
			(a[0]*a[6]*a[13]+a[1]*a[4]*a[14]+a[2]*a[5]*a[12]-
			 a[0]*a[5]*a[14]-a[1]*a[6]*a[12]-a[2]*a[4]*a[13])/det,
			(a[0]*a[5]*a[10]+a[1]*a[6]*a[8]+a[2]*a[4]*a[9]-
			 a[0]*a[6]*a[9]-a[1]*a[4]*a[10]-a[2]*a[5]*a[8])/det
	};
	return mat4(tmp);
}

vec3 transform(const mat4 &a, const vec3 &b) {
	double tmp[3];
	for (int i = 0; i < 3; i++)
		tmp[i] = a[i*4]*b[0]+a[i*4+1]*b[1]+a[i*4+2]*b[2];
	return vec3(tmp);
}

mat4 transpose(const mat4 &a) {
	double tmp[16];
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			tmp[j*4+i] = a[i*4+j];
	return mat4(tmp);
}

mat4 translate(const mat4 &a, const vec3 &b) {
	double tmp[16];
	for (int i = 0; i < 16; i += 4) {
		tmp[i] = a[i];
		tmp[i+1] = a[i+1];
		tmp[i+2] = a[i+2];
		tmp[i+3] = a[i+3];
	}
	tmp[3] += b[0];
	tmp[7] += b[1];
	tmp[11] += b[2];
	return mat4(tmp);
}