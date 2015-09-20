//
// Created by chais on 03.08.15.
//

#include "helper.h"

float helper::to_radians(float angle) {
	return angle*float(M_PI)/180;
}

bool helper::almost_equal(const float &x, const float &y, const int ulp) {
	return std::abs(x-y) < std::numeric_limits<float>::epsilon()*std::abs(x-y)*ulp ||
		   std::abs(x-y) < std::numeric_limits<float>::min();
}