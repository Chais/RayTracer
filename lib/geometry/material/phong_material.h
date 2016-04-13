//
// Created by chais on 06.08.15.
//

#ifndef RAY_TRACER_PHONG_H
#define RAY_TRACER_PHONG_H

#include <ostream>
#include "solid_material.h"

struct phong_material : public solid_material {
protected:
	float ambient, diffuse, specular, exponent;
public:
	phong_material(const std::shared_ptr<color> emit_col, const std::shared_ptr<color> col, const float &ambient,
				   const float &diffuse,
				   const float &specular, const float &exponent);

	friend std::ostream &operator<<(std::ostream &out, const phong_material &a);

	virtual const std::shared_ptr<color> shade(const color &lcol, const direction &l, const normal &n,
											   const direction &v,
											   const vec2 &pos, const bool &internal) const override;

	virtual std::shared_ptr<ray> reflect(const direction &i, const normal &n, const position &x) const;

	virtual std::shared_ptr<ray> refract(const direction &i, const normal &n, const position &x,
										 const bool &internal) const;
};

#endif //RAY_TRACER_PHONG_H
