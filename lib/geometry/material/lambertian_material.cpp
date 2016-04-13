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
			float phi = std::max<float>(0.0, dot(n, l));
			*out = phi > 0 ? scale(*col, lcol * (diffuse * phi)) : *out;
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

std::shared_ptr<ray> lambertian_material::refract(const direction &i, const normal &n, const position &x,
												  const bool &internal) const {
	return std::shared_ptr<ray>();
}