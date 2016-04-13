//
// Created by chais on 21/03/16.
//

#ifndef RAY_TRACER_LAMBERTIAN_LIGHT_H
#define RAY_TRACER_LAMBERTIAN_LIGHT_H

#include "light.h"
#include "../geometry/shapes/point.h"
#include "../geometry/material/solid_material.h"

class lambertian_light: public light, public point {
public:
	lambertian_light(const std::shared_ptr<color> emit_col, const direction &emit_dir, const direction &offset);

	virtual const std::shared_ptr<std::vector<direction>> get_directions(const position &pos,
																		 const unsigned long &samples) const override;

	virtual const std::shared_ptr<color> emit(const direction &dir) const override;

	virtual intersection intersect_full(const ray &r) const override;

	virtual bool intersect_shadow(const position &o, const direction &d) const override;
};
#endif //RAY_TRACER_LAMBERTIAN_LIGHT_H
