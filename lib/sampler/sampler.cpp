//
// Created by chais on 08.01.16.
//

#include "sampler.h"

sampler::sampler() : gen(rd()) {
}

std::shared_ptr<std::vector<float>> sampler::get_1d_samples(const float &lower, const float &upper,
															const unsigned long &count) const {
	assert(count > 0);
	std::shared_ptr<std::vector<float>> out = std::shared_ptr<std::vector<float>>(new std::vector<float>());
	out->push_back(0);
	return out;
}

std::shared_ptr<std::vector<long>> sampler::get_1d_samples(const long &lower, const long &upper,
														   const unsigned long &count) const {
	assert(count > 0);
	std::shared_ptr<std::vector<long>> out = std::shared_ptr<std::vector<long>>(new std::vector<long>());
	out->push_back(0);
	return out;
}

std::shared_ptr<std::vector<unsigned long>> sampler::get_1d_samples(const unsigned long &lower,
																	const unsigned long &upper,
																	const unsigned long &count) const {
	assert(count > 0);
	std::shared_ptr<std::vector<unsigned long>> out = std::shared_ptr<std::vector<unsigned long>>(
			new std::vector<unsigned long>());
	out->push_back(0);
	return out;
}

std::shared_ptr<std::vector<vec2>> sampler::get_2d_samples(const float &lowerx, const float &upperx,
														   const float &lowery, const float &uppery,
														   const unsigned long &count) const {
	assert(count > 0);
	std::shared_ptr<std::vector<vec2>> out = std::shared_ptr<std::vector<vec2>>(new std::vector<vec2>());
	out->push_back(vec2());
	return out;
}

std::shared_ptr<std::vector<direction>> sampler::get_solid_angle_samples(const direction &centre, const float &phi,
																		 const unsigned long &count) const {
	assert(phi <= static_cast<float>(M_PI));
	assert(count > 0);
	std::shared_ptr<std::vector<direction>> out = std::shared_ptr<std::vector<direction>>(new std::vector<direction>());
	out->push_back(direction(centre));
	return out;
}