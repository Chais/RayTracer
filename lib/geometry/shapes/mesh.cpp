//
// Created by chais on 18.09.15.
//

#include "mesh.h"

mesh::mesh(const direction *offset, const material *matrl, std::vector<triangle *> *faces) : shape(offset, matrl),
																							 faces(faces) { }

intersection mesh::intersect_full(const ray &r) {
	intersection out = intersection();
	ray tr = this->world_to_object(r);
	tr.o = tr.o - *this->offset;
	float dist = std::numeric_limits<float>::max();
	for (triangle *t : *this->faces) {
		if (dot(*t->get_avg_normal(), tr.d) > 0)
			continue;
		intersection cur = t->intersect_full(tr);
		if (cur.pos == nullptr)
			continue;
		float new_dist = length(tr.o - *cur.pos);
		if (new_dist < dist) {
			dist = new_dist;
			out = cur;
			out.object = this;
			*out.pos = this->object_to_world(*out.pos + *this->offset);
			*out.norm = normalise(this->object_to_world(*out.norm));
		}
	}
	return out;
}

bool mesh::intersect_shadow(const point &o, const direction &d) {
	if (d == direction())
		return false;
	point to = this->world_to_object(o);
	direction td = this->world_to_object(d);
	to -= *this->offset;
	for (triangle *t : *this->faces)
		if (t->intersect_shadow(to, td))
			return true;
	return false;
}
