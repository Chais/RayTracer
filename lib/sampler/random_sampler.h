//
// Created by chais on 08.01.16.
//

#ifndef RAY_TRACER_RANDOM_SAMPLER_H
#define RAY_TRACER_RANDOM_SAMPLER_H

#include "sampler.h"

class random_sampler: public sampler {
public:
	random_sampler() : sampler(width, height, count) { }

	random_sampler(const float &width, const float &height, const unsigned long &count) : sampler(width, height,
																								  count) { }

	virtual std::shared_ptr<std::vector<vec2>> get_samples() override;
};


#endif //RAY_TRACER_RANDOM_SAMPLER_H
