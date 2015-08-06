//
// Created by chais on 06.08.15.
//

#include "material.h"

material::material(const phong &phong_params, double reflectance, double transmittance, double refraction) : phong_params(
		phong_params), reflectance(reflectance), transmittance(transmittance), refraction(refraction) {
	if (reflectance<0)
		throw material_exception("Reflectance needs to be non-negative");
	if (transmittance<0)
		throw material_exception("Transmittance needs to be non-negative");
	if (refraction<0)
		throw material_exception("Index of refraction needs to be non-negative");
}

const phong &material::getPhong_params() const {
	return this->phong_params;
}

double material::getReflectance() const {
	return this->reflectance;
}

double material::getTransmittance() const {
	return this->transmittance;
}

double material::getRefraction() const {
	return this->refraction;
}
