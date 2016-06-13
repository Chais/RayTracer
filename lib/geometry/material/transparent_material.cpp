//
// Created by chais on 24.09.15.
//

#include "transparent_material.h"

transparent_material::transparent_material(const std::shared_ptr<color> emit_col, const std::shared_ptr<color> col,
										   const float &ambient, const float &diffuse, const float &specular,
										   const float &exponent, const float &reflectivity, const float &transmittance,
										   const float &ior) : specular_material(emit_col, col, ambient, diffuse,
																				 specular, exponent, reflectivity),
															   transmittance(transmittance), ior(ior) {
	assert(transmittance >= 0);
	assert(ior > 0);
}

const std::shared_ptr<color> transparent_material::shade(const color &lcol, const direction &l, const normal &n,
														 const direction &v, const vec2 &pos,
														 const bool &internal) const {
	std::shared_ptr<color> out(new color());
	if (reflectance + transmittance < 1) {
		if (l != direction()) {
			// Directional light
			if (!internal) {
				float phi = std::max<float>(0.0, dot(n, l));
				if (phi > 0) {
					direction r = n * (2 * phi) - l;
					*out = (scale(*col, lcol * (diffuse * phi)) +
							lcol * (std::pow(std::max<float>(0.0, dot(v, r)), exponent) * specular)) *
						   (1 - reflectance - transmittance);
				}
			}
		} else
			// Ambient light
			*out = scale(*col, lcol * ambient) * (1 - reflectance - transmittance);
	}
	return out;
}

std::shared_ptr<ray> transparent_material::refract(const direction &i, const normal &n, const position &x,
												   const bool &internal) const {
	const float cosi = dot(n, i);
	const float eta = internal ? ior : 1 / ior;
	const float sint2 = std::pow(eta, 2) * (1 - std::pow(cosi, 2));
	if (sint2 <= 1)
		return std::shared_ptr<ray>(new ray(x, -i * eta + n * (eta * cosi - std::sqrt(1 - sint2))));
	else
		return std::shared_ptr<ray>(new ray(x, n * (2 * cosi) - i));
}

const float transparent_material::get_transmittance() const {
	return transmittance;
}
