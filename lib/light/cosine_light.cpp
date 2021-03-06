//
// Created by chais on 21/03/16.
//

#include "cosine_light.h"

cosine_light::cosine_light(const std::shared_ptr<color> emit_col, const direction &emit_dir,
								   const direction &offset) :
		light(emit_dir), point(offset, std::shared_ptr<material>(
		new solid_material(emit_col, std::shared_ptr<color>(new color())))) { }

const std::shared_ptr<std::vector<intersection>> cosine_light::get_directions(const position &pos,
																			   const unsigned long &samples) const {
	std::shared_ptr<std::vector<intersection>> out(new std::vector<intersection>());
	intersection i;
	i.pos = std::shared_ptr<position>(new position(object_to_world(position() + offset)));
	out->push_back(i);
	return out;
}

const std::shared_ptr<color> cosine_light::emit(const direction &dir, const intersection &is) const {
	return std::make_shared<color>(
			*matrl->get_emittance() * std::max(dot(emit_dir, dir), 0.0f) * (1.0f / std::pow(length(dir), 2)));
}

intersection cosine_light::intersect_full(const ray &r) const {
	return intersection();
	/*ray tr = world_to_object(r);
	direction c = position(-tr.o) + offset;
	float a = std::max(float(0.0), dot(tr.d, c));
	float b = std::sqrt(std::pow(length(c), 2) - std::pow(a, 2));
	intersection out = intersection();
	if (b < 0.05f) {
		float d = std::sqrt(std::pow(0.05f, 2) - std::pow(b, 2));
		std::shared_ptr<position> x;
		if (d < a - 1E-4)
			x = std::make_shared<position>(position(tr.o + direction(tr.d * (a - d))));
		else
			x = std::make_shared<position>(position(tr.o + direction(tr.d * (a + d))));
		std::shared_ptr<normal> norm = std::make_shared<normal>(normal(*x - offset));
		float local_len = length(*norm);
		std::shared_ptr<vec2> local_pos = std::make_shared<vec2>(vec2((*norm)[0] / local_len, (*norm)[1] / local_len));
		*x = object_to_world(*x);
		*norm = normalise(object_to_world(*norm));
		out.object = shared_from_this();
		out.norm = norm;
		out.pos = x;
		out.local_pos = local_pos;
	}
	return out;*/
}

bool cosine_light::intersect_shadow(const position &o, const direction &d) const {
	return false;
}

const std::shared_ptr<std::vector<ray>> cosine_light::shed(unsigned long samples) const {
	random_sampler s;
	std::shared_ptr<std::vector<ray>> out(new std::vector<ray>());
	std::shared_ptr<std::vector<direction>> dirs = s.get_solid_angle_samples(emit_dir, static_cast<float>(M_PI / 2),
																			 samples);
	for (direction d : *dirs)
		out->push_back(object_to_world(ray(offset, d)));
	return out;
}

const float cosine_light::get_total_area() const {
	return 1;
}