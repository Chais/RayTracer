//
// Created by chais on 08.01.16.
//

#ifndef RAY_TRACER_SAMPLER_H
#define RAY_TRACER_SAMPLER_H

#include <cassert>
#include "../math/vec2.h"
#include "../geometry/direction.h"
#include <random>
#include <memory>

class sampler {
protected:
	std::random_device rd;
	mutable std::mt19937 gen;
public:
	sampler();

	virtual std::shared_ptr<std::vector<float>> get_1d_samples(const float &lower, const float &upper,
													   const unsigned long &count) const;

	virtual std::shared_ptr<std::vector<long>> get_1d_samples(const long &lower, const long &upper,
															   const unsigned long &count) const;

	virtual std::shared_ptr<std::vector<unsigned long>> get_1d_samples(const unsigned long &lower, const unsigned long &upper,
															  const unsigned long &count) const;

	virtual std::shared_ptr<std::vector<vec2>> get_2d_samples(const float &lowerx, const float &upperx,
															 const float &lowery,
															 const float &uppery, const unsigned long &count) const;
};
#endif //RAY_TRACER_SAMPLER_H