//
// Created by chais on 03.08.15.
//

#ifndef RAY_TRACER_HELPER_H
#define RAY_TRACER_HELPER_H

#include <limits>
#include <cmath>

class helper {
public:
	/**
	 * Converts \p angle, given in degrees, to radians
	 * @param  angle The angle in degrees
	 * @return       The angle in radians
	 */
	static float to_radians(float angle);

	/**
	 * Checks whether to values are within a certain epsilon of each other. If so they are considered equal.
	 * @param  x   The first value
	 * @param  y   The second value
	 * @param  ulp Unit of Least Precision
	 * @return     true if \p x and \p y are sufficiently close to each other, false otherwise
	 */
	static bool almost_equal(const float &x, const float &y, const int ulp);
};

#endif //RAY_TRACER_HELPER_H
