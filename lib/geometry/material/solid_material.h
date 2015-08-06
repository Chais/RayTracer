//
// Created by chais on 06.08.15.
//

#ifndef RAY_TRACER_SOLID_MATERIAL_H
#define RAY_TRACER_SOLID_MATERIAL_H

#include "material.h"

class solid_material : public material {
protected:
	vec3 color;
public:
	solid_material(const vec3 color, const phong &phong_params, double reflectance, double transmittance,
				   double refraction);

	virtual vec3 getColor(double u, double v);
};

#endif //RAY_TRACER_SOLID_MATERIAL_H
