//
// Created by chais on 22.09.15.
//

#ifndef RAY_TRACER_SPECULAR_MATERIAL_H
#define RAY_TRACER_SPECULAR_MATERIAL_H

#include "phong_material.h"

class specular_material: public phong_material {
protected:
	const float reflectance;
public:

	specular_material(const color &col, const float &ambient, const float &diffuse, const float &specular,
					  const float &exponent, const float reflectance);

	virtual std::shared_ptr<color>
		shade(const color &lcol, const direction &l, const normal &n, const direction &v, const vec2 &pos,
			  const bool internal) const;

	virtual std::shared_ptr<std::vector<ray>>
		reflect(const direction &i, const normal &n, const point &x, const unsigned int &s) const;

	virtual std::shared_ptr<std::vector<ray>>
		refract(const direction &i, const normal &n, const point &x, const unsigned int &s, const bool internal) const;

	virtual const float get_reflectance() const;

	virtual const float get_transmittance() const;
};

#endif //RAY_TRACER_SPECULAR_MATERIAL_H
