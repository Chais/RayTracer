//
// Created by chais on 25.08.15.
//

#ifndef RAY_TRACER_COLOR_H
#define RAY_TRACER_COLOR_H

#include <cmath>
#include <array>
#include <cassert>

/**
 * @name color
 *
 * @brief Models color
 */
class color {
private:
	std::array<float, 3> v;
public:
	color();

	color(const float r, const float g, const float b);

	color(const color &in);

	float &operator[](const unsigned long i);

	const float &operator[](const unsigned long i) const;

	friend std::ostream &operator<<(std::ostream &out, const color &a);
};

color operator+(const color &lhs, const color &rhs);

color operator*(const color &lhs, const float &rhs);

color operator*(const float &lhs, const color &rhs);

color scale(const color &col, const std::array<float, 3> &sf);

color scale(const color &col, const color &sf);

std::array<int, 3> rgb(const color &col);

#endif //RAY_TRACER_COLOR_H
