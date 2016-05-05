//
// Created by chais on 21/03/16.
//

#include "mesh_light.h"

mesh_light::mesh_light(const direction &offset, const std::shared_ptr<material> &matrl,
					   const std::shared_ptr<std::vector<std::shared_ptr<triangle>>> &faces)
		: light(direction()), mesh(offset, matrl, faces) { }

mesh_light::mesh_light(const std::shared_ptr<mesh> &m) : light(direction()), mesh(*m) { }

intersection mesh_light::intersect_self(const ray &r) const {
	intersection out = intersection();
	ray tr = world_to_object(r);
	tr.o = tr.o - offset;
	const direction inv_d = direction(1 / tr.d[0], 1 / tr.d[1], 1 / tr.d[2]);
	if (!intersect_quick(tr.o, inv_d))
		return out;
	float dist = std::numeric_limits<float>::max();
	for (std::shared_ptr<triangle> t : *faces) {
		if (!t->intersect_quick(tr.o, inv_d))
			continue;
		std::shared_ptr<normal> n = t->get_avg_normal();
		intersection cur = t->intersect_full(tr);
		if (!cur.pos)
			continue;
		float new_dist = length(tr.o - *cur.pos);
		if (new_dist < dist) {
			dist = new_dist;
			out = cur;
			*out.pos = object_to_world(*out.pos + offset);
			*out.norm = normalise(object_to_world(*out.norm));
		}
	}
	return out;
}

const std::shared_ptr<std::vector<direction>> mesh_light::get_directions(const position &pos,
																		 const unsigned long &samples) const {
	std::vector<float> area = std::vector<float>(faces->size(), 0);
	for (unsigned long i = 0; i < faces->size(); i++) {
		const std::array<position, 3> v = *faces->at(i)->get_vertices();
		float e1 = length(object_to_world(v[0] - v[1]));
		float e2 = length(object_to_world(v[0] - v[2]));
		float e3 = length(object_to_world(v[1] - v[2]));
		float s = (e1 + e2 + e3) / 2;
		area[i] = std::sqrt(s * (s - e1) * (s - e2) * (s - e3));
	}
	float m = area[std::distance(area.begin(), std::min_element(area.begin(), area.end()))];
	for (unsigned long i = 0; i < area.size(); i++)
		area[i] = std::ceil(area[i] / m);
	std::vector<float> wheighted = std::vector<float>(
			static_cast<unsigned long>(std::accumulate(area.begin(), area.end(), 0)), 0);
	std::vector<float>::iterator it = wheighted.begin();
	for (unsigned long i = 0; i < area.size(); i++)
		for (unsigned long j = 0; j < area[i]; j++)
			*it++ = i;
	random_sampler s;
	std::vector<unsigned long> f = *s.get_1d_samples(0, wheighted.size() - 1, samples);
	std::vector<vec2> c = *s.get_2d_samples(0, 1, 0, 1, samples);
	std::shared_ptr<std::vector<direction>> out(new std::vector<direction>());
	for (unsigned long i = 0; i < samples; i++) {
		std::shared_ptr<triangle> face = faces->at(static_cast<unsigned long>(wheighted[f[i]]));
		std::shared_ptr<vec2> lcoord(new vec2(c[i][0] + c[i][1] > 1 ? 1 - c[i][1] : c[i][0],
											  c[i][0] + c[i][1] > 1 ? 1 - c[i][0] : c[i][1]));
		std::shared_ptr<position> lpos = std::make_shared<position>(object_to_world(
				*face->get_barycentric_position(1 - (*lcoord)[0] - (*lcoord)[1], (*lcoord)[0], (*lcoord)[1]) + offset));
		intersection closest = intersect_self(ray(*lpos, pos - *lpos));
		if (!closest.object) {
			closest.pos = lpos;
			closest.object = face;
			closest.local_pos = lcoord;
			closest.norm = std::make_shared<normal>(object_to_world(
					*face->get_barycentric_normal(1 - (*lcoord)[0] - (*lcoord)[1], (*lcoord)[0], (*lcoord)[1])));
		}
		direction dir = (pos - *closest.pos) * 0.9999;
		if (dot(*closest.norm, normalise(dir)) >= 0)
			out->push_back(dir);
	}
	return out;
}

const std::shared_ptr<color> mesh_light::emit(const direction &dir) const {
	return std::make_shared<color>(*matrl->get_emit_col() * (1.0f / std::pow(length(dir), 2)));
}

const std::shared_ptr<std::vector<ray>> mesh_light::shed(unsigned long samples) const {
	std::vector<float> area = std::vector<float>(faces->size(), 0);
	std::vector<direction> n = std::vector<direction>();
	for (unsigned long i = 0; i < faces->size(); i++) {
		const std::array<position, 3> v = *faces->at(i)->get_vertices();
		direction e1 = object_to_world(v[0] - v[1]);
		direction e2 = object_to_world(v[0] - v[2]);
		float l1 = length(e1);
		float l2 = length(e2);
		float l3 = length(object_to_world(v[1] - v[2]));
		float s = (l1 + l2 + l3) / 2;
		area[i] = std::sqrt(s * (s - l1) * (s - l2) * (s - l3));
		n.push_back(normalise(cross(e1, e2)));
	}
	float m = area[std::distance(area.begin(), std::min_element(area.begin(), area.end()))];
	for (unsigned long i = 0; i < area.size(); i++)
		area[i] = std::ceil(area[i] / m);
	std::vector<float> wheighted = std::vector<float>(
			static_cast<unsigned long>(std::accumulate(area.begin(), area.end(), 0)), 0);
	std::vector<float>::iterator it = wheighted.begin();
	for (unsigned long i = 0; i < area.size(); i++)
		for (unsigned long j = 0; j < area[i]; j++)
			*it++ = i;
	std::shared_ptr<std::vector<ray>> out(new std::vector<ray>());
	random_sampler s;
	std::vector<unsigned long> f = *s.get_1d_samples(0, wheighted.size() - 1, samples);
	std::vector<vec2> c = *s.get_2d_samples(0, 1, 0, 1, samples);
	for (unsigned long i = 0; i < samples; i++) {
		std::shared_ptr<triangle> face = faces->at(static_cast<unsigned long>(wheighted[f[i]]));
		std::shared_ptr<vec2> lcoord(new vec2(c[i][0] + c[i][1] > 1 ? 1 - c[i][1] : c[i][0],
											  c[i][0] + c[i][1] > 1 ? 1 - c[i][0] : c[i][1]));
		std::shared_ptr<position> lpos = std::make_shared<position>(object_to_world(
				*face->get_barycentric_position(1 - (*lcoord)[0] - (*lcoord)[1], (*lcoord)[0], (*lcoord)[1]) + offset));
		if (dot(n[static_cast<unsigned long>(wheighted[f[i]])], object_to_world(*face->get_avg_normal())) < 0)
			n[static_cast<unsigned long>(wheighted[f[i]])] = -n[static_cast<unsigned long>(wheighted[f[i]])];
		out->push_back(ray(*lpos, s.get_solid_angle_samples(n[static_cast<unsigned long>(wheighted[f[i]])],
															static_cast<float>(M_PI / 2), 1)->at(0)));
	}
	return out;
}