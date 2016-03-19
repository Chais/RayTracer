//
// Created by chais on 08.01.16.
//

#ifndef RAY_TRACER_RANDOM_SAMPLER_H
#define RAY_TRACER_RANDOM_SAMPLER_H

#include "sampler.h"

class random_sampler : public sampler {
public:
	random_sampler();

	virtual std::shared_ptr<std::vector<vec2>> get_samples(const float &width, const float &height,
														   const unsigned long &count) const override;
};


#endif //RAY_TRACER_RANDOM_SAMPLER_H
