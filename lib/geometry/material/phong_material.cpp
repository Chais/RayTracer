//
// Created by chais on 06.08.15.
//

#include "phong_material.h"

phong_material::phong_material(const std::shared_ptr<color> emit_col, const std::shared_ptr<color> col,
							   const float &ambient, const float &diffuse, const float &specular, const float &exponent)
		: solid_material(emit_col, col), ambient(ambient), diffuse(diffuse), specular(specular), exponent(exponent) { }

std::ostream &operator<<(std::ostream &out, const phong_material &a) {
	out << "Phong material: Color: " << a.col << " Ambient intensity: " << a.ambient << ", Diffuse intensity: " <<
	a.diffuse << ", Specular intensity: " <<
	a.specular << ", Specular exponent: " << a.exponent;
	return out;
}

const std::shared_ptr<color> phong_material::shade(const color &lcol, const direction &l, const normal &n,
												   const direction &v,
												   const vec2 &pos, const bool &internal) const {
	std::shared_ptr<color> out(new color());
	if (l != direction()) {
		// Directional light
		if (!internal) {
			float cos_theta = std::max<float>(0.0, dot(n, l));
			if (cos_theta > 0) {
				direction r = n * (2 * cos_theta) - l;
				*out = scale(*col, lcol * (diffuse * static_cast<float>(1 / M_PI) * cos_theta)) +
					   lcol * (std::pow(std::max<float>(0.0, dot(v, r)), exponent) * specular * ((exponent + 2)/(2*M_PI)));
			}
		}
	} else
		// Ambient light
		*out = scale(*col, lcol * ambient);
	return out;
}

std::shared_ptr<ray> phong_material::reflect(const direction &i, const normal &n, const position &x) const {
	if (diffuse > 0) {
		random_sampler s;
		return std::shared_ptr<ray>(new ray(x, s.get_solid_angle_samples(n, static_cast<float>(M_PI / 2), 1)->at(0)));
	} else
		return std::shared_ptr<ray>();
}

std::shared_ptr<ray> phong_material::refract(const direction &i, const normal &n, const position &x,
											 const bool &internal) const {
	return std::shared_ptr<ray>();
}