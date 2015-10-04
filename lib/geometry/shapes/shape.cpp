//
// Created by chais on 02.08.15.
//

#include "shape.h"

shape::shape(const std::shared_ptr<direction> offset, std::shared_ptr<material> matrl) : object_to_world(transform()),
																						 world_to_object(object_to_world.inv_trans,
																										 object_to_world.trans),
																						 offset(offset),
																						 matrl(matrl) { }

std::shared_ptr<color> shape::shade(const color &lcol,
									const direction &l,
									const normal &n,
									const direction &v,
									const vec2 &pos,
									const bool internal) {
	return this->matrl->shade(lcol, l, n, v, pos, internal);
}

void shape::translate(const direction &t) {
	this->object_to_world.translate(t);
}

void shape::scale(const std::array<float, 3> sf) {
	this->object_to_world.scale(sf);
}

void shape::rotateX(const float &angle) {
	this->object_to_world.rotateX(angle);
}

void shape::rotateY(const float &angle) {
	this->object_to_world.rotateY(angle);
}

void shape::rotateZ(const float &angle) {
	this->object_to_world.rotateZ(angle);
}

std::shared_ptr<std::vector<ray>> shape::reflect(const direction &i,
												 const normal &n,
												 const point &x,
												 const unsigned int &s) const {
	return this->matrl->reflect(i, n, x, s);
}

std::shared_ptr<std::vector<ray>> shape::refract(const direction &i,
												 const normal &n,
												 const point &x,
												 const unsigned int &s,
												 const bool internal) const {
	return this->matrl->refract(i, n, x, s, internal);
}

const float shape::get_reflectance() const {
	return this->matrl->get_reflectance();
}

const float shape::get_transmittance() const {
	return this->matrl->get_transmittance();
}
