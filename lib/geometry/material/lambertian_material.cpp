//
// Created by chais on 26.08.15.
//

#include "lambertian_material.h"

lambertian_material::lambertian_material(color col, float ambient, float diffuse) : solid_material(col),
																					ambient(ambient),
																					diffuse(diffuse) { }

std::ostream &operator<<(std::ostream &out, const lambertian_material &a) {
	out << "Phong material: Color: " << a.col << " Ambient intensity: " << a.ambient << ", Diffuse intensity: " <<
		a.diffuse;
	return out;
}

color lambertian_material::shade(const color &lcol, const direction &l, const normal &n, const direction &v,
								 const vec2 &pos,
								 const bool internal) const {
	if (l != direction()) {
		// Directional light
		if (!internal) {
			float phi = std::max<float>(0.0, dot(n, l));
			if (phi > 0) {
				return scale(this->col, lcol*(this->diffuse*phi));
			}
		}
	} else
		// Ambient light
		return scale(this->col, lcol*this->ambient);
	return color();
}

std::vector<ray> *lambertian_material::reflect(const direction &i, const normal &n, const point &x,
											   const unsigned int &s) const {
	return nullptr;
}

std::vector<ray> *lambertian_material::refract(const direction &i, const normal &n, const point &x,
											   const unsigned int &s, const bool internal) const {
	return nullptr;
}

const float lambertian_material::get_reflectance() const {
	return 0;
}

const float lambertian_material::get_transmittance() const {
	return 0;
}
