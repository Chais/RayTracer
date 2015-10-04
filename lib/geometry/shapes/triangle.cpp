//
// Created by chais on 18.09.15.
//

#include "triangle.h"

triangle::triangle(std::shared_ptr<std::array<point, 3>> vertices,
				   std::shared_ptr<std::array<normal, 3>> normals,
				   std::shared_ptr<std::array<vec2, 3>> texture_coords)
	: vertices(vertices), normals(normals), texture_coords(texture_coords) {
	aabb[0] = point(std::min((*vertices)[0][0], std::min((*vertices)[1][0], (*vertices)[2][0])),
					std::min((*vertices)[0][1], std::min((*vertices)[1][1], (*vertices)[2][1])),
					std::min((*vertices)[0][2], std::min((*vertices)[1][2], (*vertices)[2][2])));
	aabb[1] = point(std::max((*vertices)[0][0], std::max((*vertices)[1][0], (*vertices)[2][0])),
					std::max((*vertices)[0][1], std::max((*vertices)[1][1], (*vertices)[2][1])),
					std::max((*vertices)[0][2], std::max((*vertices)[1][2], (*vertices)[2][2])));
}

intersection triangle::intersect_full(const ray &r) const {
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
	if (t < 2E-4 || x < 0 || y < 0 || x + y > 1)
		return out;
	out.pos = std::shared_ptr<point>(new point(r.o + r.d*(t - 1E-4)));
	out.local_pos = std::shared_ptr<vec2>(new vec2(
		(1 - x - y)*(*this->texture_coords)[0][0] + x*(*this->texture_coords)[1][0] + y*(*this->texture_coords)[2][0],
		(1 - x - y)*(*this->texture_coords)[0][1] + x*(*this->texture_coords)[1][1] + y*(*this->texture_coords)[2][1]));
	out.norm = this->get_barycentric_normal(1 - x - y, x, y);
	return out;
}

bool triangle::intersect_shadow(const point &o, const direction &d) const {
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

bool triangle::intersect_quick(const point &o, const direction &inv_d) const {
	float tmin = -std::numeric_limits<float>::infinity(), tmax = std::numeric_limits<float>::infinity();
	if (inv_d[0] != 0) {
		float tx1 = (this->aabb[0][0] - o[0])*inv_d[0];
		float tx2 = (this->aabb[1][0] - o[0])*inv_d[0];
		tmin = std::max(tmin, std::min(tx1, tx2));
		tmax = std::min(tmax, std::max(tx1, tx2));
	}
	if (inv_d[1] != 0) {
		float tx1 = (this->aabb[0][1] - o[1])*inv_d[1];
		float tx2 = (this->aabb[1][1] - o[1])*inv_d[1];
		tmin = std::max(tmin, std::min(tx1, tx2));
		tmax = std::min(tmax, std::max(tx1, tx2));
	}
	if (inv_d[2] != 0) {
		float tx1 = (this->aabb[0][2] - o[2])*inv_d[2];
		float tx2 = (this->aabb[1][2] - o[2])*inv_d[2];
		tmin = std::max(tmin, std::min(tx1, tx2));
		tmax = std::min(tmax, std::max(tx1, tx2));
	}
	return tmax >= tmin;
}

std::shared_ptr<normal> triangle::get_avg_normal() const {
	return std::shared_ptr<normal>(new normal(normalise(
		(*this->normals)[0] + (*this->normals)[1] + (*this->normals)[2])));
}

std::shared_ptr<normal> triangle::get_barycentric_normal(const float &a, const float &b, const float &c) const {
	return std::shared_ptr<normal>(new normal(normalise(
		(*this->normals)[0]*a + (*this->normals)[1]*b + (*this->normals)[2]*c)));
}
const std::array<point, 2> &triangle::get_aabb() const {
	return this->aabb;
}
