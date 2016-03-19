//
// Created by chais on 26.08.15.
//

#ifndef RAY_TRACER_LAMBERTIAN_MATERIAL_H
#define RAY_TRACER_LAMBERTIAN_MATERIAL_H

#include "solid_material.h"

class lambertian_material: public solid_material {
private:
	float ambient, diffuse;
public:
	lambertian_material(color col, float ambient, float diffuse);

	friend std::ostream &operator<<(std::ostream &out, const lambertian_material &a);

	virtual std::shared_ptr<color>
		shade(const color &lcol, const direction &l, const normal &n, const direction &v, const vec2 &pos,
			  const bool internal) const;

	virtual std::shared_ptr<std::vector<ray>>
		reflect(const direction &i, const normal &n, const point &x, const unsigned int &s) const;

	virtual std::shared_ptr<std::vector<ray>>
		refract(const direction &i, const normal &n, const point &x, const bool internal) const;

	virtual const float get_reflectance() const;

	virtual const float get_transmittance() const;
};

#endif //RAY_TRACER_LAMBERTIAN_MATERIAL_H
