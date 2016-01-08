//
// Created by chais on 08.01.16.
//

#ifndef RAY_TRACER_SAMPLER_H
#define RAY_TRACER_SAMPLER_H

#include <assert.h>
#include "../math/vec2.h"
#include <random>
#include <memory>

class sampler {
public:
	const float width = 0.001953125, height = 0.001953125;
	const unsigned long count = 1;

	sampler();

	sampler(const float &width, const float &height, const unsigned long &count);

	virtual std::shared_ptr<std::vector<vec2>> get_samples();
};

#endif //RAY_TRACER_SAMPLER_H