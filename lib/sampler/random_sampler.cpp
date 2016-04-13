//
// Created by chais on 08.01.16.
//

#include "random_sampler.h"

random_sampler::random_sampler() { }

std::shared_ptr<std::vector<float>> random_sampler::get_1d_samples(const float &lower, const float &upper,
																   const unsigned long &count) const {
	assert(count > 0);
	std::uniform_real_distribution<float> dis(lower, upper);
	std::shared_ptr<std::vector<float>> out(new std::vector<float>());
	for (unsigned long i = 0; i < count; i++)
		out->push_back(dis(gen));
	return out;
}

std::shared_ptr<std::vector<long>> random_sampler::get_1d_samples(const long &lower, const long &upper,
																  const unsigned long &count) const {
	assert(count > 0);
	std::uniform_int_distribution<long> dis(lower, upper);
	std::shared_ptr<std::vector<long>> out(new std::vector<long>());
	for (unsigned long i = 0; i < count; i++)
		out->push_back(dis(gen));
	return out;
}

std::shared_ptr<std::vector<unsigned long>> random_sampler::get_1d_samples(const unsigned long &lower, const unsigned long &upper,
																  const unsigned long &count) const {
	assert(count > 0);
	std::uniform_int_distribution<unsigned long> dis(lower, upper);
	std::shared_ptr<std::vector<unsigned long>> out(new std::vector<unsigned long>());
	for (unsigned long i = 0; i < count; i++)
		out->push_back(dis(gen));
	return out;
}

std::shared_ptr<std::vector<vec2>> random_sampler::get_2d_samples(const float &lowerx, const float &upperx,
																  const float &lowery,
																  const float &uppery,
																  const unsigned long &count) const {
	assert(count > 0);
	std::uniform_real_distribution<float> xdis(lowerx, upperx);
	std::uniform_real_distribution<float> ydis(lowery, uppery);
	std::shared_ptr<std::vector<vec2>> out(new std::vector<vec2>());
	for (int i = 0; i < count; i++)
		out->push_back(vec2(xdis(gen), ydis(gen)));
	return out;
}
