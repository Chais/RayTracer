//
// Created by chais on 21/03/16.
//

#include <iostream>
#include "mesh_light.h"

mesh_light::mesh_light(const direction &offset, const std::shared_ptr<material> &matrl,
					   const std::shared_ptr<std::vector<std::shared_ptr<triangle>>> &faces)
		: light(direction()), mesh(offset, matrl, faces) {
	for (std::shared_ptr<triangle> t : *faces) {
		const std::array<position, 3> v = *t->get_vertices();
		total_area += 0.5f * length(cross(object_to_world(v[1] - v[0]), object_to_world(v[2] - v[0])));
		cr_areas.push_back(total_area);
	}
	for (unsigned long i = 0; i < cr_areas.size(); i++)
		cr_areas[i] /= total_area;
}

mesh_light::mesh_light(const std::shared_ptr<mesh> &m) : light(direction()), mesh(*m) {
	for (std::shared_ptr<triangle> t : *faces) {
		const std::array<position, 3> v = *t->get_vertices();
		total_area += 0.5f * length(cross(object_to_world(v[1] - v[0]), object_to_world(v[2] - v[0])));
		cr_areas.push_back(total_area);
	}
	for (unsigned long i = 0; i < cr_areas.size(); i++)
		cr_areas[i] /= total_area;
}

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

const std::shared_ptr<std::vector<intersection>> mesh_light::get_directions(const position &pos,
																			const unsigned long &samples) const {
	std::shared_ptr<std::vector<intersection>> out(new std::vector<intersection>());
	random_sampler s;
	std::vector<float> face_selector = *s.get_1d_samples(0.0f, 1.0f, samples);
	std::vector<vec2> c = *s.get_2d_samples(0, 1, 0, 1, samples);
	for (unsigned long i = 0; i < c.size(); i++) {
		for (unsigned long f = 0; f < cr_areas.size(); f++) {
			if (face_selector.at(i) < cr_areas[f]) {
				std::shared_ptr<triangle> face = faces->at(f);
				std::shared_ptr<vec2> lcoord(new vec2(c[i][0] + c[i][1] > 1 ? 1 - c[i][1] : c[i][0],
													  c[i][0] + c[i][1] > 1 ? 1 - c[i][0] : c[i][1]));
				std::shared_ptr<position> lpos = std::make_shared<position>(object_to_world(
						*face->get_barycentric_position(1 - (*lcoord)[0] - (*lcoord)[1], (*lcoord)[0], (*lcoord)[1]) +
						offset));
				intersection closest = intersect_self(ray(*lpos, pos - *lpos));
				if (!closest.object) {
					closest.pos = lpos;
					closest.object = face;
					closest.local_pos = lcoord;
					closest.norm = std::make_shared<normal>(object_to_world(
							*face->get_barycentric_normal(1 - (*lcoord)[0] - (*lcoord)[1], (*lcoord)[0], (*lcoord)[1])
					));
				}
				if (dot(*closest.norm, pos - *closest.pos) >= 0)
					out->push_back(closest);
				break;
			}
		}
	}
	return out;
}

const std::shared_ptr<color> mesh_light::emit(const direction &dir, const intersection &is) const {
	return std::make_shared<color>(*matrl->get_emittance() * dot(normalise(dir), *is.norm) *
								   (1.0f / length(dir)));
}

const std::shared_ptr<std::vector<ray>> mesh_light::shed(unsigned long samples) const {
	random_sampler s;
	std::vector<float> face_selector = *s.get_1d_samples(0.0f, 1.0f, samples);
	std::vector<vec2> c = *s.get_2d_samples(0, 1, 0, 1, samples);
	std::shared_ptr<std::vector<ray>> out(new std::vector<ray>());
	for (unsigned long i = 0; i < c.size(); i++) {
		for (unsigned long f = 0; f < cr_areas.size(); f++) {
			if (face_selector.at(i) < cr_areas[f]) {
				std::shared_ptr<triangle> face = faces->at(f);
				std::shared_ptr<vec2> lcoord(new vec2(c[i][0] + c[i][1] > 1 ? 1 - c[i][1] : c[i][0],
													  c[i][0] + c[i][1] > 1 ? 1 - c[i][0] : c[i][1]));
				std::shared_ptr<position> lpos = std::make_shared<position>(object_to_world(
						*face->get_barycentric_position(1 - (*lcoord)[0] - (*lcoord)[1], (*lcoord)[0], (*lcoord)[1]) +
						offset));
				std::array<position, 3> & v = *face->get_vertices();
				normal n = normalise(cross(object_to_world(v[1]-v[0]), object_to_world(v[2]-v[0])));
				if (dot(n, object_to_world(*face->get_avg_normal())) < 0)
					n = -n;
				out->push_back(ray(*lpos, s.get_solid_angle_samples(n, static_cast<float>(M_PI / 2), 1)->at(0)));
			}
		}
	}
	return out;
}

const float mesh_light::get_total_area() const {
	return total_area;
}