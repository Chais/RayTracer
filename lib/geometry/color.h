//
// Created by chais on 25.08.15.
//

#ifndef RAY_TRACER_COLOR_H
#define RAY_TRACER_COLOR_H

#define _USE_MATH_DEFINES
#include <cmath>
#include <array>
#include <cassert>
#include <ostream>

/**
 * Models RGB color as an array of three float values. Values are considered to range from 0.0 to 1.0. Although higher values can be stored they will be capped when converted to the 0 to 255 scale.
 */
class color {
private:
	std::array<float, 3> v;
public:
	/**
	 * @brief Default constructor
	 *
	 * Creates black
	 */
	color();

	/**
	 * @brief Explicit constructor
	 *
	 * Creates the given color
	 * @param r The red component
	 * @param g The green component
	 * @param b The blue component
	 */
	color(const float r, const float g, const float b);

	/**
	 * @brief Copy constructor
	 *
	 * Copies the values from the given color
	 * @param in The original color
	 */
	color(const color &in);

	/**
	 * Array subscribt
	 * @param  i The component to access. 0 = r, 1 = g, 2 = b
	 * @return   The component
	 */
	float &operator[](const unsigned long i);

	/**
	 * Array subscribt
	 * @param  i The component to access. 0 = r, 1 = g, 2 = b
	 * @return   The component
	 */
	const float &operator[](const unsigned long i) const;

	friend std::ostream &operator<<(std::ostream &out, const color &a);
};

/**
 * @brief Addition
 *
 * Adds two colors.
 * @param lhs The left operand
 * @param rhs The right operand
 * @return    The resulting color
 */
color operator+(const color &lhs, const color &rhs);

color operator-(const color &lhs, const color &rhs);

/**
 * @brief Addition assignment
 *
 * Adds the right operand to the left. The result is stored in the left operand.
 * @param lhs The left operand
 * @param rhs The right operand
 * @return    The updated left operand
 */
color &operator+=(color &lhs, const color &rhs);

/**
 * @brief Scalar multiplication
 *
 * Multiplies every component of the color with a scaling factor.
 * @param lhs The color
 * @param rhs The scaling factor
 * @return    The resulting color
 */
color operator*(const color &lhs, const float &rhs);

/**
 * @brief Scalar multiplication
 *
 * Multiplies every component of the color with a scaling factor.
 * @param lhs The scaling factor
 * @param rhs The color
 * @return    The resulting color
 */
color operator*(const float &lhs, const color &rhs);

/**
 * @brief Non-uniform scaling
 *
 * Multiplies each color component with its own scaling factor.
 * @param  col The color
 * @param  sf  The array of scaling factors
 * @return     The resulting color
 */
color scale(const color &col, const std::array<float, 3> &sf);

/**
 * @brief Non-uniform scaling
 *
 * Multiplies each color component with its own scaling factor. Uses another color as container for the scaling factors.
 * @param  col The color
 * @param  sf  The array of scaling factors
 * @return     The resulting color
 */
color scale(const color &col, const color &sf);

/**
 * Converts the color components to a 0 - 255 scale. Component values greater than 1.0 are capped to 255.
 * @param col The color to convert
 * @return    An array of three integers ranging from 0 to 255
 */
std::array<unsigned char, 3> rgb(const color &col);
#endif //RAY_TRACER_COLOR_H
