//
// Created by chais on 06.08.15.
//

#ifndef RAY_TRACER_MATERIAL_H
#define RAY_TRACER_MATERIAL_H

#include "phong.h"
#include "../../math/vec3.h"

class material {
protected:
	phong phong_params;
	double reflectance, transmittance, refraction;
public:
	material(const phong &phong_params, double reflectance, double transmittance, double refraction);

	const phong &getPhong_params() const;

	double getReflectance() const;

	double getTransmittance() const;

	double getRefraction() const;

	virtual vec3 getColor(double u, double v) = 0;
};

#endif //RAY_TRACER_MATERIAL_H
