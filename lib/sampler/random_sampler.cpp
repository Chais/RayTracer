//
// Created by chais on 08.01.16.
//

#include "random_sampler.h"

std::shared_ptr<std::vector<vec2>> random_sampler::get_samples() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> wdis(-width/2, std::nextafter(width/2, std::numeric_limits<float>::max()));
	std::uniform_real_distribution<float> hdis(-height/2, std::nextafter(height/2, std::numeric_limits<float>::max()));
	std::shared_ptr<std::vector<vec2>> out = std::make_shared<std::vector<vec2>>();
	for (int i = 0; i < count; i++) {
		out->push_back(vec2(wdis(gen), hdis(gen)));
	}
	return out;
}
