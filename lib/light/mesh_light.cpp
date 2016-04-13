//
// Created by chais on 21/03/16.
//

#include "mesh_light.h"

mesh_light::mesh_light(const direction &offset, const std::shared_ptr<material> &matrl,
					   const std::shared_ptr<std::vector<std::shared_ptr<triangle>>> &faces)
		: light(direction()), mesh(offset, matrl, faces) { }

mesh_light::mesh_light(const std::shared_ptr<mesh> &m) : light(direction()), mesh(*m) { }

intersection mesh_light::find_farthest(const ray &r) const {
	intersection out = intersection();
	ray tr = world_to_object(r);
	tr.o = tr.o - offset;
	const direction inv_d = direction(1 / tr.d[0], 1 / tr.d[1], 1 / tr.d[2]);
	if (!intersect_quick(tr.o, inv_d))
		return out;
	float dist = 0;
	for (std::shared_ptr<triangle> t : *faces) {
		if (!t->intersect_quick(tr.o, inv_d))
			continue;
		std::shared_ptr<normal> n = t->get_avg_normal();
		if (dot(*n, tr.d) > 0)
			continue;
		intersection cur = t->intersect_full(tr);
		if (!cur.pos)
			continue;
		float new_dist = length(tr.o - *cur.pos);
		if (new_dist > dist) {
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
	std::vector<unsigned long> valid_faces = std::vector<unsigned long>(faces->size(), 0);
	for (unsigned long i = 0; i < faces->size(); i++)
		valid_faces[i] = i;
	position tpos = world_to_object(pos);
	std::shared_ptr<std::vector<direction>> out(new std::vector<direction>());
	random_sampler s;
	std::vector<unsigned long> f = *s.get_1d_samples(static_cast<unsigned long>(0), faces->size() - 1, samples);
	std::vector<vec2> c = *s.get_2d_samples(0, 1, 0, 1, samples);
	for (unsigned long i = 0; i < samples; i++) {
		while (true) {
			if (valid_faces.size() == 0)
				return out;
			std::vector<unsigned long>::iterator result = std::find(valid_faces.begin(), valid_faces.end(), f[i]);
			if (result == valid_faces.end()) {
				f[i] = s.get_1d_samples(static_cast<unsigned long>(0), faces->size() - 1, 1)->at(0);
				continue;
			}
			const std::shared_ptr<std::array<normal, 3>> n = faces->at(f[i])->get_normals();
			const std::shared_ptr<std::array<position, 3>> d = faces->at(f[i])->get_vertices();
			bool valid = dot(*faces->at(f[i])->get_avg_normal(),
							 tpos - *faces->at(f[i])->get_barycentric_position(1.0f / 3, 1.0f / 3, 1.0f / 3)) > 1e-3;
			if (!valid) {
				valid_faces.erase(result);
				continue;
			}
			vec2 lcoord = vec2(c[i][0] + c[i][1] > 1 ? 1 - c[i][1] : c[i][0],
							   c[i][0] + c[i][1] > 1 ? 1 - c[i][0] : c[i][1]);
			position lpos = object_to_world(
					*faces->at(f[i])->get_barycentric_position(1 - lcoord[0] - lcoord[1], lcoord[0], lcoord[1]));
			intersection closest = find_farthest(ray(lpos, pos - lpos));
			if (closest.object && dot(*closest.norm, normalise(pos - *closest.pos)) <= 0) {
				std::vector<std::shared_ptr<triangle>>::iterator cf = std::find(faces->begin(), faces->end(),
																				closest.object);
				result = std::find(valid_faces.begin(), valid_faces.end(), std::distance(faces->begin(), cf));
				valid_faces.erase(result);
				c[i] = s.get_2d_samples(0, 1, 0, 1, 1)->at(0);
				continue;
			} else if (dot(*faces->at(f[i])->get_barycentric_normal(1 - lcoord[0] - lcoord[1], lcoord[0], lcoord[1]),
						   normalise(pos - lpos)) <= 0) {
				c[i] = s.get_2d_samples(0, 1, 0, 1, 1)->at(0);
				continue;
			}
			out->push_back((pos - lpos) * 0.999);
			break;
		}
	}
	return out;
}

const std::shared_ptr<color> mesh_light::emit(const direction &dir) const {
	return matrl->get_emit_col();
}