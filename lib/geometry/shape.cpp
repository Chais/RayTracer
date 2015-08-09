//
// Created by chais on 02.08.15.
//

#include "shape.h"
#include "../math/helper.h"

shape::shape(material *matrl) : transforms(mat4()), inv_trans(mat4()), matrl(matrl) { }

vec3 shape::getPosition() {
	return vec3(this->transforms[3], this->transforms[7], this->transforms[11]);
}

material *shape::getMaterial() const {
	return this->matrl;
}

const mat4 &shape::getTransforms() const {
	return this->transforms;
}

const mat4 &shape::getInvTransforms() const {
	return this->inv_trans;
}

void shape::translate(vec3 t) {
	double tmp[] = {
			1, 0, 0, t[0],
			0, 1, 0, t[1],
			0, 0, 1, t[2],
			0, 0, 0, 1
	};
	double itmp[] = {
			1, 0, 0, -t[0],
			0, 1, 0, -t[1],
			0, 0, 1, -t[2],
			0, 0, 0, 1
	};
	this->transforms *= mat4(tmp);
	this->inv_trans = mat4(itmp)*this->inv_trans;
}

void shape::scale(vec3 sf) {
	double tmp[] = {
			sf[0], 0, 0, 0,
			0, sf[1], 0, 0,
			0, 0, sf[2], 0,
			0, 0, 0, 1
	};
	double itmp[] = {
			1/sf[0], 0, 0, 0,
			0, 1/sf[1], 0, 0,
			0, 0, 1/sf[2], 0,
			0, 0, 0, 1
	};
	this->transforms *= mat4(tmp);
	this->inv_trans = mat4(itmp)*this->inv_trans;
}

void shape::rotateX(double angle) {
	angle = helper::toRadians(angle);
	double tmp[] = {
			1, 0, 0, 0,
			0, cos(angle), -sin(angle), 0,
			0, sin(angle), cos(angle), 0,
			0, 0, 0, 1
	};
	double itmp[] = {
			1, 0, 0, 0,
			0, cos(-angle), -sin(-angle), 0,
			0, sin(-angle), cos(-angle), 0,
			0, 0, 0, 1
	};
	this->transforms *= mat4(tmp);
	this->inv_trans = mat4(itmp)*this->inv_trans;
}

void shape::rotateY(double angle) {
	angle = helper::toRadians(angle);
	double tmp[] = {
			cos(angle), 0, sin(angle), 0,
			0, 1, 0, 0,
			-sin(angle), 0, cos(angle), 0,
			0, 0, 0, 1
	};
	double itmp[] = {
			cos(-angle), 0, sin(-angle), 0,
			0, 1, 0, 0,
			-sin(-angle), 0, cos(-angle), 0,
			0, 0, 0, 1
	};
	this->transforms *= mat4(tmp);
	this->inv_trans = mat4(itmp)*this->inv_trans;
}

void shape::rotateZ(double angle) {
	angle = helper::toRadians(angle);
	double tmp[] = {
			cos(angle), -sin(angle), 0, 0,
			sin(angle), cos(angle), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
	};
	double itmp[] = {
			cos(-angle), -sin(-angle), 0, 0,
			sin(-angle), cos(-angle), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
	};
	this->transforms *= mat4(tmp);
	this->inv_trans = mat4(itmp)*this->inv_trans;
}