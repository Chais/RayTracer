//
// Created by chais on 12/04/16.
//

#include "sphere_light.h"

sphere_light::sphere_light(const direction &emit_dir, const direction &offset, const std::shared_ptr<material> &matrl,
						   const float &radius) : light(emit_dir), sphere(offset, matrl, radius) { }

sphere_light::sphere_light(const std::shared_ptr<sphere> s) : light(direction()), sphere(*s) { }

intersection sphere_light::intersect_self(const ray &r) const {
	ray tr = sphere::world_to_object(r);
	direction c = position(-tr.o) + offset;
	float a = std::max(float(0.0), dot(tr.d, c));
	float b = std::sqrt(std::pow(length(c), 2) - std::pow(a, 2));
	intersection out = intersection();
	if (b < radius - 1E-4) {
		float d = std::sqrt(std::pow(radius, 2) - std::pow(b, 2));
		std::shared_ptr<position> x = std::shared_ptr<position>(new position(tr.o + direction(tr.d * (a + d))));
		std::shared_ptr<normal> norm = std::shared_ptr<normal>(new normal(*x - offset));
		float local_len = length(*norm);
		std::shared_ptr<vec2> local_pos = std::shared_ptr<vec2>(
				new vec2((*norm)[0] / local_len, (*norm)[1] / local_len));
		*x = object_to_world(*x);
		*norm = normalise(object_to_world(*norm));
		out.object = shared_from_this();
		out.norm = norm;
		out.pos = x;
		out.local_pos = local_pos;
	}
	return out;
}

const std::shared_ptr<std::vector<direction>> sphere_light::get_directions(const position &pos,
																		   const unsigned long &samples) const {
	std::shared_ptr<std::vector<direction>> out(new std::vector<direction>());
	random_sampler s;
	std::vector<vec2> c = *s.get_2d_samples(0, static_cast<float>(2 * M_PI), 0, 1, samples);
	for (unsigned long i = 0; i < samples; i++) {
		c[i][1] = std::acos(2 * c[i][1] - 1);
		position lpos = object_to_world(
				position(radius * std::cos(c[i][0]) * std::sin(c[i][1]), radius * std::sin(c[i][0]) * std::sin(c[i][1]),
						 radius * std::cos(c[i][1])));
		intersection closest = intersect_self(ray(lpos, pos - lpos));
		if (closest.object)
			out->push_back(pos - *closest.pos);
		else
			out->push_back(pos - lpos);
	}
	return out;
}

const std::shared_ptr<color> sphere_light::emit(const direction &dir) const {
	return matrl->get_emit_col();
}