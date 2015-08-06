//
// Created by chais on 06.08.15.
//

#include "solid_material.h"

solid_material::solid_material(const vec3 color, const phong &phong_params, double reflectance, double transmittance,
							   double refraction) : material(phong_params, reflectance, transmittance, refraction),
													color(color) { }

vec3 solid_material::getColor(double u, double v) {
	return this->color;
}
