//
// Created by chais on 22.09.15.
//

#include "specular_material.h"

specular_material::specular_material(const color &col, const float &ambient, const float &diffuse,
									 const float &specular, const float &exponent, const float reflectivity)
	: phong_material(col, ambient, diffuse, specular,
					 exponent),
	  reflectance(reflectivity) {
	assert(reflectivity >= 0 && reflectivity <= 1);
}

std::shared_ptr<color> specular_material::shade(const color &lcol,
												const direction &l,
												const normal &n,
												const direction &v,
												const vec2 &pos,
												const bool internal) const {
	if (this->reflectance < 1) {
		if (l != direction()) {
			// Directional light
			if (!internal) {
				float phi = std::max<float>(0.0, dot(n, l));
				if (phi > 0) {
					direction r = n*(2*phi) - l;
					return std::make_shared<color>((scale(this->col, lcol*(this->diffuse*phi)) +
						lcol*(std::pow(std::max<float>(0.0, dot(v, r)), this->exponent)*this->specular))*
						(1 - this->reflectance));
				}
			}
		} else
			// Ambient light
			return std::make_shared<color>(scale(this->col, lcol*this->ambient)*(1 - this->reflectance));
	}
	return std::shared_ptr<color>(new color());
}

std::shared_ptr<std::vector<ray>> specular_material::reflect(const direction &i, const normal &n, const point &x,
															 const unsigned int &s) const {
	std::shared_ptr<std::vector<ray>> out(new std::vector<ray>());
	// TODO adapt for multisampling
	out->push_back(ray(x, (2*dot(n, i))*n - i));
	return out;
}

std::shared_ptr<std::vector<ray>> specular_material::refract(const direction &i, const normal &n, const point &x,
															 const unsigned int &s, const bool internal) const {
	return std::shared_ptr<std::vector<ray>>();
}

const float specular_material::get_reflectance() const {
	return this->reflectance;
}

const float specular_material::get_transmittance() const {
	return 0;
}
