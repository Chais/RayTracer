//
// Created by chais on 02.08.15.
//

#ifndef RAY_TRACER_GEOMETRY_H
#define RAY_TRACER_GEOMETRY_H

#include "../math/mat4.h"
#include "ray.h"
#include "material/material.h"

class shape {
protected:
	mat4 transforms;
	mat4 inv_trans;
	material *matrl;

public:
	shape(material *matrl);

	material *getMaterial() const;

	vec3 getPosition();

	const mat4 &getTransforms() const;

	const mat4 &getInvTransforms() const;

	void translate(vec3 translation);

	void scale(vec3 sf);

	void rotateX(double angle);

	void rotateY(double angle);

	void rotateZ(double angle);

	virtual ray intersect(ray r) = 0;

	virtual bool getShadow(vec3 origin, vec3 direction) = 0;

	virtual vec3 getColor(double u, double v)=0;
};

#endif //RAY_TRACER_GEOMETRY_H
