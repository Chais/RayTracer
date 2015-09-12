//
// Created by chais on 02.08.15.
//

#include "shape.h"

shape::shape(material *matrl) : object_to_world(transform()), world_to_object(object_to_world.inv_trans, object_to_world.trans), matrl(matrl) { }

color shape::shade(const color &lcol, const direction &l, const normal &n, const direction &v, const vec2 &pos,
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
