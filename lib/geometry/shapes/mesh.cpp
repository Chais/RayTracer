//
// Created by chais on 18.09.15.
//

#include "mesh.h"

mesh::mesh(std::shared_ptr<direction> offset,
		   std::shared_ptr<material> matrl,
		   std::shared_ptr<std::vector<std::shared_ptr<triangle>>> faces) : shape(offset, matrl), faces(faces) {
	assert(faces->size() > 0);
	aabb[0] = point(std::numeric_limits<float>::infinity(),
					std::numeric_limits<float>::infinity(),
					std::numeric_limits<float>::infinity());
	aabb[1] = point(-std::numeric_limits<float>::infinity(),
					-std::numeric_limits<float>::infinity(),
					-std::numeric_limits<float>::infinity());
	for (std::shared_ptr<triangle> t : *faces) {
		std::array<point, 2> box = t->get_aabb();
		aabb[0][0] = std::min(aabb[0][0], box[0][0]);
		aabb[0][1] = std::min(aabb[0][1], box[0][1]);
		aabb[0][2] = std::min(aabb[0][2], box[0][2]);
		aabb[1][0] = std::max(aabb[1][0], box[1][0]);
		aabb[1][1] = std::max(aabb[1][1], box[1][1]);
		aabb[1][2] = std::max(aabb[1][2], box[1][2]);
	}
}

bool mesh::intersect_quick(const point &o, const direction &inv_d) const {
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

intersection mesh::intersect_full(const ray &r) {
	intersection out = intersection();
	ray tr = this->world_to_object(r);
	tr.o = tr.o - *this->offset;
	const direction inv_d = direction(1/tr.d[0], 1/tr.d[1], 1/tr.d[2]);
	if (!this->intersect_quick(tr.o, inv_d))
		return out;
	float dist = std::numeric_limits<float>::max();
	for (std::shared_ptr<triangle> t : *this->faces) {
		if (!t->intersect_quick(tr.o, inv_d))
			continue;
		std::shared_ptr<normal> n = t->get_avg_normal();
		if (dot(*n, tr.d) > 0)
			continue;
		intersection cur = t->intersect_full(tr);
		if (!cur.pos)
			continue;
		float new_dist = length(tr.o - *cur.pos);
		if (new_dist < dist) {
			dist = new_dist;
			out = cur;
			out.object = shared_from_this();
			*out.pos = this->object_to_world(*out.pos + *this->offset);
			*out.norm = normalise(this->object_to_world(*out.norm));
		}
	}
	return out;
}

bool mesh::intersect_shadow(const point &o, const direction &d) const {
	if (d == direction())
		return false;
	point to = this->world_to_object(o);
	direction td = this->world_to_object(d);
	to -= *this->offset;
	const direction inv_d = direction(1/td[0], 1/td[1], 1/td[2]);
	if (!this->intersect_quick(to, inv_d))
		return false;
	for (std::shared_ptr<triangle> t : *this->faces)
		if (t->intersect_shadow(to, td))
			return true;
	return false;
}
