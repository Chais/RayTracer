//
// Created by chais on 22.09.15.
//

#include "specular_material.h"

specular_material::specular_material(const std::shared_ptr<color> emit_col, const std::shared_ptr<color> col,
									 const float &ambient, const float &diffuse, const float &specular,
									 const float &exponent, const float &reflectivity) : phong_material(emit_col, col,
																										ambient,
																										diffuse,
																										specular,
																										exponent),
																						 reflectance(reflectivity) {
	assert(reflectivity >= 0 && reflectivity <= 1);
}

const std::shared_ptr<color> specular_material::shade(const color &lcol, const direction &l, const normal &n,
													  const direction &v,
													  const vec2 &pos, const bool &internal) const {
	std::shared_ptr<color> out(new color());
	if (reflectance < 1) {
		if (l != direction()) {
			// Directional light
			if (!internal) {
				float phi = std::max<float>(0.0, dot(n, l));
				if (phi > 0) {
					direction r = n * (2 * phi) - l;
					*out = (scale(*col, lcol * (diffuse * phi)) +
							lcol * (std::pow(std::max<float>(0.0, dot(v, r)), exponent) * specular)) *
						   (1 - reflectance);
				}
			}
		} else
			// Ambient light
			*out = scale(*col, lcol * ambient) * (1 - reflectance);
	}
	return out;
}

std::shared_ptr<ray> specular_material::reflect(const direction &i, const normal &n, const position &x) const {
	if (reflectance > 0)
		return std::shared_ptr<ray>(new ray(x, (2 * dot(n, i)) * n - i));
	else
		return std::shared_ptr<ray>();
}

std::shared_ptr<ray> specular_material::scatter(const direction &i, const normal &n, const position &x) const {
	return std::shared_ptr<ray>();
}

std::shared_ptr<ray> specular_material::refract(const direction &i, const normal &n, const position &x,
												const bool &internal) const {
	return std::shared_ptr<ray>();
}

const float specular_material::get_reflectance() const {
	return reflectance;
}

const float specular_material::get_transmittance() const {
	return 0;
}