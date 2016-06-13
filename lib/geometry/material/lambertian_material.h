//
// Created by chais on 26.08.15.
//

#ifndef RAY_TRACER_LAMBERTIAN_MATERIAL_H
#define RAY_TRACER_LAMBERTIAN_MATERIAL_H

#include "solid_material.h"
#include "../../sampler/random_sampler.h"

class lambertian_material : public solid_material {
private:
	float ambient, diffuse;
public:
	virtual std::shared_ptr<ray> scatter(const direction &i, const normal &n, const position &x) const override;

	lambertian_material(const std::shared_ptr<color> emittance, const std::shared_ptr<color> col, const float &ambient,
						const float &diffuse);

	friend std::ostream &operator<<(std::ostream &out, const lambertian_material &a);

	virtual const std::shared_ptr<color> shade(const color &lcol, const direction &l, const normal &n,
											   const direction &v,
											   const vec2 &pos, const bool &internal) const override;

	virtual std::shared_ptr<ray> reflect(const direction &i, const normal &n, const position &x) const;

	virtual std::shared_ptr<ray> refract(const direction &i, const normal &n, const position &x,
										 const bool &internal) const;
};

#endif //RAY_TRACER_LAMBERTIAN_MATERIAL_H