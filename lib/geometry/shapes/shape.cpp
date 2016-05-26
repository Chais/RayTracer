//
// Created by chais on 02.08.15.
//

#include "shape.h"

shape::shape(const direction &offset, const std::shared_ptr<material> &matrl) : object_to_world(transform()),
																				world_to_object(
																					   object_to_world.inv_trans,
																					   object_to_world.trans),
																				offset(offset), matrl(matrl) { }

const std::shared_ptr<color> shape::shade(const color &lcol, const direction &l, const normal &n, const direction &v,
										  const vec2 &pos,
										  const bool &internal) const {
	return matrl->shade(lcol, l, n, v, pos, internal);
}

void shape::translate(const direction &t) {
	object_to_world.translate(t);
}

void shape::scale(const std::array<float, 3> &sf) {
	object_to_world.scale(sf);
}

void shape::rotateX(const float &angle) {
	object_to_world.rotateX(angle);
}

void shape::rotateY(const float &angle) {
	object_to_world.rotateY(angle);
}

void shape::rotateZ(const float &angle) {
	object_to_world.rotateZ(angle);
}

std::shared_ptr<ray> shape::reflect(const direction &i, const normal &n, const position &x) const {
	return matrl->reflect(i, n, x);
}

std::shared_ptr<ray> shape::scatter(const direction &i, const normal &n, const position &x) const {
	return matrl->scatter(i, n, x);
}

std::shared_ptr<ray> shape::refract(const direction &i, const normal &n, const position &x, const bool internal) const {
	return matrl->refract(i, n, x, internal);
}

const float shape::get_reflectance() const {
	return matrl->get_reflectance();
}

const float shape::get_transmittance() const {
	return matrl->get_transmittance();
}
