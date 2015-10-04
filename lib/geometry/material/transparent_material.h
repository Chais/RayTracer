//
// Created by chais on 24.09.15.
//

#ifndef RAY_TRACER_TRANSMISSIVE_MATERIAL_H
#define RAY_TRACER_TRANSMISSIVE_MATERIAL_H

#include "specular_material.h"

class transparent_material: public specular_material {
protected:
	const float transmittance;
	const float ior;
public:

	transparent_material(const color &col, const float &ambient, const float &diffuse, const float &specular,
						 const float &exponent, const float reflectance, const float transmittance, const float ior);

	virtual std::shared_ptr<color>
		shade(const color &lcol, const direction &l, const normal &n, const direction &v, const vec2 &pos,
			  const bool internal) const override;

	virtual std::shared_ptr<std::vector<ray>> refract(const direction &i, const normal &n, const point &x,
													  const unsigned int &s, const bool internal) const override;

	virtual const float get_transmittance() const override;
};

#endif //RAY_TRACER_TRANSMISSIVE_MATERIAL_H
