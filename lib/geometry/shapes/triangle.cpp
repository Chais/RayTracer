//
// Created by chais on 18.09.15.
//

#include "triangle.h"

triangle::triangle(std::array<point, 3> *vertices, std::array<normal, 3> *normals, std::array<vec2, 3> *texture_coords)
	: vertices(vertices), normals(normals), texture_coords(texture_coords) { }

intersection triangle::intersect_full(const ray &r) {
	direction E1 = (*this->vertices)[1] - (*this->vertices)[0];
	direction E2 = (*this->vertices)[2] - (*this->vertices)[0];
	direction T = r.o - (*this->vertices)[0];
	direction P = cross(r.d, E2);
	direction Q = cross(T, E1);
	float s = 1/(dot(P, E1));
	float t = dot(Q, E2)*s;
	float x = dot(P, T)*s;
	float y = dot(Q, r.d)*s;
	intersection out = intersection();
	if (t < 0 || x < 0 || y < 0 || x + y > 1)
		return out;
	out.pos = new point(r.o + r.d*(t - 1E-4));
	out.local_pos = new vec2(
		(1 - x - y)*(*this->texture_coords)[0][0] + x*(*this->texture_coords)[1][0] + y*(*this->texture_coords)[2][0],
		(1 - x - y)*(*this->texture_coords)[0][1] + x*(*this->texture_coords)[1][1] + y*(*this->texture_coords)[2][1]);
	out.norm = this->get_barycentric_normal(x, y, 1 - x - y);
	return out;
}

bool triangle::intersect_shadow(const point &o, const direction &d) {
	direction E1 = (*this->vertices)[1] - (*this->vertices)[0];
	direction E2 = (*this->vertices)[2] - (*this->vertices)[0];
	direction T = o - (*this->vertices)[0];
	direction nd = normalise(d);
	direction P = cross(nd, E2);
	direction Q = cross(T, E1);
	float s = 1/(dot(P, E1));
	float t = dot(Q, E2)*s;
	float x = dot(P, T)*s;
	float y = dot(Q, nd)*s;
	return !(length(d) < t || t < 0 || x < 0 || y < 0 || x + y > 1);
}

normal *triangle::get_avg_normal() {
	return new normal(normalise((*this->normals)[0] + (*this->normals)[1] + (*this->normals)[2]));
}

normal *triangle::get_barycentric_normal(const float &a, const float &b, const float &c) {
	return new normal(normalise((*this->normals)[0]*a + (*this->normals)[1]*b + (*this->normals)[2]*c));
}