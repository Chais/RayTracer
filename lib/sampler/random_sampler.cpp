//
// Created by chais on 08.01.16.
//

#include "random_sampler.h"
#include "../geometry/transform.h"

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

std::shared_ptr<std::vector<unsigned long>> random_sampler::get_1d_samples(const unsigned long &lower,
																		   const unsigned long &upper,
																		   const unsigned long &count) const {
	assert(count > 0);
	std::uniform_int_distribution<unsigned long> dis(lower, upper);
	std::shared_ptr<std::vector<unsigned long>> out(new std::vector<unsigned long>());
	for (unsigned long i = 0; i < count; i++)
		out->push_back(dis(gen));
	return out;
}

std::shared_ptr<std::vector<vec2>> random_sampler::get_2d_samples(const float &lowerx, const float &upperx,
																  const float &lowery, const float &uppery,
																  const unsigned long &count) const {
	assert(count > 0);
	std::uniform_real_distribution<float> xdis(lowerx, upperx);
	std::uniform_real_distribution<float> ydis(lowery, uppery);
	std::shared_ptr<std::vector<vec2>> out(new std::vector<vec2>());
	for (int i = 0; i < count; i++)
		out->push_back(vec2(xdis(gen), ydis(gen)));
	return out;
}

std::shared_ptr<std::vector<direction>> random_sampler::get_solid_angle_samples(const direction &centre,
																				const float &phi,
																				const unsigned long &count) const {
	assert(phi <= static_cast<float>(M_PI));
	assert(count > 0);
	direction c = normalise(centre);
	float x = std::abs(c[0]), y = std::abs(c[1]), z = std::abs(c[2]);
	float min = std::min(x, std::min(y, z));
	direction ax = direction();
	if (min == x)
		ax[0] = 1;
	else if (min == y)
		ax[1] = 1;
	else
		ax[2] = 1;
	direction u = normalise(cross(c, ax)), v = cross(u, c);
	std::vector<vec2> samples = *get_2d_samples(0, static_cast<float>(2 * M_PI), (1 - phi / static_cast<float>(M_PI)),
												1, count);
	std::shared_ptr<std::vector<direction>> out = std::shared_ptr<std::vector<direction>>(new std::vector<direction>());
	for (vec2 s : samples) {
		s[1] = std::acos(2 * s[1] - 1);
		out->push_back(std::sin(s[1]) * (std::cos(s[0]) * u + std::sin(s[0]) * v) + std::cos(s[1]) * c);
	}
	return out;
}