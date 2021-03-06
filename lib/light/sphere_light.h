//
// Created by chais on 12/04/16.
//

#ifndef RAY_TRACER_SPHERE_LIGHT_H
#define RAY_TRACER_SPHERE_LIGHT_H

#include "light.h"
#include "../geometry/shapes/sphere.h"
#include "../sampler/random_sampler.h"

class sphere_light : public light, public sphere {
protected:
public:
	virtual const float get_total_area() const override;

	virtual intersection intersect_self(const ray &r) const;
public:
	sphere_light(const direction &emit_dir, const direction &offset, const std::shared_ptr<material> &matrl,
				 const float &radius);
	sphere_light(const std::shared_ptr<sphere> s);

	virtual const std::shared_ptr<std::vector<intersection>> get_directions(const position &pos,
																		 const unsigned long &samples) const override;

	virtual const std::shared_ptr<color> emit(const direction &dir, const intersection &is) const override;

	virtual const std::shared_ptr<std::vector<ray>> shed(unsigned long samples) const override;
};

#endif //RAY_TRACER_SPHERE_LIGHT_H