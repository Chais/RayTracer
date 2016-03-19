//
// Created by chais on 08.01.16.
//

#include "sampler.h"

sampler::sampler() { }

std::shared_ptr<std::vector<vec2>> sampler::get_samples(const float &width, const float &height,
														const unsigned long &count) const {
	assert(width >= 0);
	assert(height >= 0);
	assert(count > 0);
	std::shared_ptr<std::vector<vec2>> out = std::make_shared<std::vector<vec2>>();
	for (int i = 0; i < count; i++) {
		out->push_back(vec2());
	}
	return out;
}