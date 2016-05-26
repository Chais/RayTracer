//
// Created by chais on 22.09.15.
//

#ifndef RAY_TRACER_SPECULAR_MATERIAL_H
#define RAY_TRACER_SPECULAR_MATERIAL_H

#include "phong_material.h"

class specular_material : public phong_material {
protected:
	const float reflectance;
public:

	virtual std::shared_ptr<ray> scatter(const direction &i, const normal &n, const position &x) const override;

	specular_material(const std::shared_ptr<color> emit_col, const std::shared_ptr<color> col, const float &ambient,
					  const float &diffuse,
					  const float &specular, const float &exponent, const float &reflectance);

	virtual const std::shared_ptr<color> shade(const color &lcol, const direction &l, const normal &n,
											   const direction &v,
											   const vec2 &pos, const bool &internal) const override;

	virtual std::shared_ptr<ray> reflect(const direction &i, const normal &n, const position &x) const;

	virtual std::shared_ptr<ray> refract(const direction &i, const normal &n, const position &x,
										 const bool &internal) const;

	virtual const float get_reflectance() const;

	virtual const float get_transmittance() const;
};

#endif //RAY_TRACER_SPECULAR_MATERIAL_H
