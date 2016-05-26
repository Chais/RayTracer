//
// Created by chais on 26.08.15.
//

#include "lambertian_material.h"

lambertian_material::lambertian_material(const std::shared_ptr<color> emit_col, const std::shared_ptr<color> col,
										 const float &ambient, const float &diffuse) : solid_material(emit_col, col),
																					   ambient(ambient),
																					   diffuse(diffuse) { }

std::ostream &operator<<(std::ostream &out, const lambertian_material &a) {
	out << "Phong material: Color: " << a.col << " Ambient intensity: " << a.ambient << ", Diffuse intensity: " <<
	a.diffuse;
	return out;
}

const std::shared_ptr<color> lambertian_material::shade(const color &lcol, const direction &l, const normal &n,
														const direction &v, const vec2 &pos,
														const bool &internal) const {
	std::shared_ptr<color> out(new color());
	if (l != direction()) {
		// Directional light
		if (!internal) {
			float cos_theta = std::max<float>(0.0, dot(n, l));
			*out = cos_theta > 0 ? scale(*col, lcol * (diffuse * static_cast<float>(1 / M_PI) * cos_theta)) : *out;
		}
	} else
		// Ambient light
		*out = scale(*col, lcol * ambient);
	*out += *emit_col;
	return out;
}

std::shared_ptr<ray> lambertian_material::reflect(const direction &i, const normal &n, const position &x) const {
	return std::shared_ptr<ray>();
}

std::shared_ptr<ray> lambertian_material::scatter(const direction &i, const normal &n, const position &x) const {
	if (diffuse > 0) {
		random_sampler s;
		return std::shared_ptr<ray>(new ray(x, s.get_solid_angle_samples(n, static_cast<float>(M_PI / 2), 1)->at(0)));
	} else
		return std::shared_ptr<ray>();
}

std::shared_ptr<ray> lambertian_material::refract(const direction &i, const normal &n, const position &x,
												  const bool &internal) const {
	return std::shared_ptr<ray>();
}