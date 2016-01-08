//
// Created by chais on 08.01.16.
//

#include "sampler.h"

sampler::sampler() { }

sampler::sampler(const float &width, const float &height, const unsigned long &count) : width(width), height(height),
																						count(count) {
	assert(width > 0);
	assert(height > 0);
	assert(count > 0);
}

std::shared_ptr<std::vector<vec2>> sampler::get_samples() {
	std::shared_ptr<std::vector<vec2>> out = std::make_shared<std::vector<vec2>>();
	out->push_back(vec2());
	return out;
}