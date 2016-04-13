//
// Created by chais on 10.09.15.
//

#include "solid_material.h"

solid_material::solid_material(const std::shared_ptr<color> emit_col, const std::shared_ptr<color> col) :
		material(emit_col, col) { }

const std::shared_ptr<color> solid_material::shade(const color &lcol, const direction &l, const normal &n,
												   const direction &v,
												   const vec2 &pos, const bool &internal) const {
	std::shared_ptr<color> out = std::make_shared<color>(*col);
	*out += *emit_col;
	return out;
}

std::shared_ptr<ray> solid_material::reflect(const direction &i, const normal &n, const position &x) const {
	return std::shared_ptr<ray>();
}

std::shared_ptr<ray> solid_material::refract(const direction &i, const normal &n, const position &x,
											 const bool &internal) const {
	return std::shared_ptr<ray>();
}

const float solid_material::get_reflectance() const {
	return 0;
}

const float solid_material::get_transmittance() const {
	return 0;
}