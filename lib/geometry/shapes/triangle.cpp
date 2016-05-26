//
// Created by chais on 18.09.15.
//

#include "triangle.h"

triangle::triangle(const direction &offset, const std::shared_ptr<material> &matrl,
				   std::shared_ptr<std::array<position, 3>> vertices, std::shared_ptr<std::array<normal, 3>> normals,
				   std::shared_ptr<std::array<vec2, 3>> texture_coords) : shape(offset, matrl), vertices(vertices),
																		  normals(normals),
																		  texture_coords(texture_coords) {
	aabb[0] = position(std::min((*vertices)[0][0], std::min((*vertices)[1][0], (*vertices)[2][0])),
					   std::min((*vertices)[0][1], std::min((*vertices)[1][1], (*vertices)[2][1])),
					   std::min((*vertices)[0][2], std::min((*vertices)[1][2], (*vertices)[2][2])));
	aabb[1] = position(std::max((*vertices)[0][0], std::max((*vertices)[1][0], (*vertices)[2][0])),
					   std::max((*vertices)[0][1], std::max((*vertices)[1][1], (*vertices)[2][1])),
					   std::max((*vertices)[0][2], std::max((*vertices)[1][2], (*vertices)[2][2])));
}

intersection triangle::intersect_full(const ray &r) const {
	direction E1 = (*vertices)[1] - (*vertices)[0];
	direction E2 = (*vertices)[2] - (*vertices)[0];
	direction T = r.o - (*vertices)[0];
	direction P = cross(r.d, E2);
	direction Q = cross(T, E1);
	float s = 1 / (dot(P, E1));
	float t = dot(Q, E2) * s;
	float x = dot(P, T) * s;
	float y = dot(Q, r.d) * s;
	intersection out = intersection();
	if (t < 2E-4 || x < 0 || y < 0 || x + y > 1)
		return out;
	out.object = shared_from_this();
	out.pos = std::shared_ptr<position>(new position(r.o + r.d * (t - 1E-3)));
	out.local_pos = std::shared_ptr<vec2>(new vec2(
			(1 - x - y) * (*texture_coords)[0][0] + x * (*texture_coords)[1][0] + y * (*texture_coords)[2][0],
			(1 - x - y) * (*texture_coords)[0][1] + x * (*texture_coords)[1][1] + y * (*texture_coords)[2][1]));
	out.norm = get_barycentric_normal(1 - x - y, x, y);
	return out;
}

bool triangle::intersect_shadow(const position &o, const direction &d) const {
	direction E1 = (*vertices)[1] - (*vertices)[0];
	direction E2 = (*vertices)[2] - (*vertices)[0];
	direction T = o - (*vertices)[0];
	direction nd = normalise(d);
	direction P = cross(nd, E2);
	direction Q = cross(T, E1);
	float s = 1 / (dot(P, E1));
	float t = dot(Q, E2) * s;
	float x = dot(P, T) * s;
	float y = dot(Q, nd) * s;
	return !(length(d) < t + 1e-3 || t < 0 || x < 0 || y < 0 || x + y > 1);
}

bool triangle::intersect_quick(const position &o, const direction &inv_d) const {
	float tmin = -std::numeric_limits<float>::infinity(), tmax = std::numeric_limits<float>::infinity();
	if (inv_d[0] != 0) {
		float tx1 = (aabb[0][0] - o[0]) * inv_d[0];
		float tx2 = (aabb[1][0] - o[0]) * inv_d[0];
		tmin = std::max(tmin, std::min(tx1, tx2));
		tmax = std::min(tmax, std::max(tx1, tx2));
	}
	if (inv_d[1] != 0) {
		float tx1 = (aabb[0][1] - o[1]) * inv_d[1];
		float tx2 = (aabb[1][1] - o[1]) * inv_d[1];
		tmin = std::max(tmin, std::min(tx1, tx2));
		tmax = std::min(tmax, std::max(tx1, tx2));
	}
	if (inv_d[2] != 0) {
		float tx1 = (aabb[0][2] - o[2]) * inv_d[2];
		float tx2 = (aabb[1][2] - o[2]) * inv_d[2];
		tmin = std::max(tmin, std::min(tx1, tx2));
		tmax = std::min(tmax, std::max(tx1, tx2));
	}
	return tmax >= tmin;
}

std::shared_ptr<normal> triangle::get_avg_normal() const {
	return std::shared_ptr<normal>(new normal(normalise((*normals)[0] + (*normals)[1] + (*normals)[2])));
}

std::shared_ptr<normal> triangle::get_barycentric_normal(const float &a, const float &b, const float &c) const {
	return std::shared_ptr<normal>(new normal(normalise((*normals)[0] * a + (*normals)[1] * b + (*normals)[2] * c)));
}

std::shared_ptr<position> triangle::get_barycentric_position(const float &a, const float &b, const float &c) const {
	return std::shared_ptr<position>(new position((*vertices)[0] * a + (*vertices)[1] * b + (*vertices)[2] * c));
}

const std::array<position, 2> &triangle::get_aabb() const {
	return aabb;
}

const std::shared_ptr<std::array<normal, 3>> triangle::get_normals() const {
	return normals;
}

const std::shared_ptr<std::array<position, 3>> triangle::get_vertices() const {
	return vertices;
}
