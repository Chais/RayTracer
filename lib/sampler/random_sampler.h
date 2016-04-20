//
// Created by chais on 08.01.16.
//

#ifndef RAY_TRACER_RANDOM_SAMPLER_H
#define RAY_TRACER_RANDOM_SAMPLER_H

#include "sampler.h"
#include "../math/mat4.h"

class random_sampler : public sampler {
public:
	random_sampler();

	virtual std::shared_ptr<std::vector<float>> get_1d_samples(const float &lower, const float &upper,
														   const unsigned long &count) const override;

	virtual std::shared_ptr<std::vector<long>> get_1d_samples(const long &lower, const long &upper,
															   const unsigned long &count) const override;

	virtual std::shared_ptr<std::vector<unsigned long>> get_1d_samples(const unsigned long &lower, const unsigned long &upper,
															  const unsigned long &count) const override;

	virtual std::shared_ptr<std::vector<vec2>> get_2d_samples(const float &lowerx, const float &upperx,
															  const float &lowery, const float &uppery,
															  const unsigned long &count) const override;

	virtual std::shared_ptr<std::vector<direction>> get_solid_angle_samples(const direction &centre, const float &phi,
																			const unsigned long &count) const override;
};
#endif //RAY_TRACER_RANDOM_SAMPLER_H