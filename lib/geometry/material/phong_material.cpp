//
// Created by chais on 06.08.15.
//

#include "phong_material.h"

phong_material::phong_material(color col, float ambient, float diffuse, float specular,
							   float exponent) : col(col), ambient(ambient), diffuse(diffuse), specular(specular),
												 exponent(exponent) { }

std::ostream &operator<<(std::ostream &out, const phong_material &a) {
	out << "Phong material: Color: " << a.col << " Ambient intensity: " << a.ambient << ", Diffuse intensity: " <<
	a.diffuse << ", Specular intensity: " <<
	a.specular << ", Specular exponent: " << a.exponent;
	return out;
}

color phong_material::shade(const color &lcol, const direction &l, const normal &n, const direction &v, const vec2 &pos,
							const bool internal) {
	if (l != direction()) {
		// Directional light
		if (!internal) {
			float phi = std::max<float>(0.0, dot(n, l));
			if (phi > 0) {
				direction r = n*(2*phi)-l;
				return scale(this->col, lcol*(this->diffuse*phi)+
						lcol*(std::pow(std::max<float>(0.0, dot(v, r)), this->exponent)*this->specular));
			}
		}
	} else
		// Ambient light
		return scale(this->col, lcol*this->ambient);
	return color();
}