//
// Created by chais on 06.08.15.
//

#include "phong_material.h"

phong_material::phong_material(const color &col, const float &ambient, const float &diffuse, const float &specular,
							   const float &exponent) : solid_material(col), ambient(ambient), diffuse(diffuse),
														specular(specular), exponent(exponent) { }

std::ostream &operator<<(std::ostream &out, const phong_material &a) {
	out << "Phong material: Color: " << a.col << " Ambient intensity: " << a.ambient << ", Diffuse intensity: " <<
		a.diffuse << ", Specular intensity: " <<
		a.specular << ", Specular exponent: " << a.exponent;
	return out;
}

std::shared_ptr<color> phong_material::shade(const color &lcol,
											 const direction &l,
											 const normal &n,
											 const direction &v,
											 const vec2 &pos,
											 const bool internal) const {
	if (l != direction()) {
		// Directional light
		if (!internal) {
			float phi = std::max<float>(0.0, dot(n, l));
			if (phi > 0) {
				direction r = n*(2*phi) - l;
				return std::make_shared<color>(scale(this->col, lcol*(this->diffuse*phi)) +
					lcol*(std::pow(std::max<float>(0.0, dot(v, r)), this->exponent)*this->specular));
			}
		}
	} else
		// Ambient light
		return std::make_shared<color>(scale(this->col, lcol*this->ambient));
	return std::make_shared<color>(color());
}

std::shared_ptr<std::vector<ray>> phong_material::reflect(const direction &i,
														  const normal &n,
														  const point &x,
														  const unsigned int &s) const {
	return std::shared_ptr<std::vector<ray>>();
}

std::shared_ptr<std::vector<ray>> phong_material::refract(const direction &i, const normal &n, const point &x,
														  const unsigned int &s, const bool internal) const {
	return std::shared_ptr<std::vector<ray>>();
}

const float phong_material::get_reflectance() const {
	return 0;
}

const float phong_material::get_transmittance() const {
	return 0;
}
