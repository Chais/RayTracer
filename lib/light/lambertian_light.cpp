//
// Created by chais on 21/03/16.
//

#include "lambertian_light.h"

lambertian_light::lambertian_light(const std::shared_ptr<color> emit_col, const direction &emit_dir,
								   const direction &offset) :
		light(emit_dir), point(direction(), std::shared_ptr<material>(
		new solid_material(emit_col, std::shared_ptr<color>(new color())))) { }

const std::shared_ptr<std::vector<direction>> lambertian_light::get_directions(const position &pos,
																			   const unsigned long &samples) const {
	std::shared_ptr<std::vector<direction>> out(new std::vector<direction>());
	out->push_back(pos - object_to_world(offset));
	return out;
}

const std::shared_ptr<color> lambertian_light::emit(const direction &dir) const {
	return std::make_shared<color>(*matrl->get_emit_col() * std::max(dot(emit_dir, dir), 0.0f));
}

intersection lambertian_light::intersect_full(const ray &r) const {
	return intersection();
}

bool lambertian_light::intersect_shadow(const position &o, const direction &d) const {
	return false;
}