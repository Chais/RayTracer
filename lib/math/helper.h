//
// Created by chais on 03.08.15.
//

#ifndef RAY_TRACER_HELPER_H
#define RAY_TRACER_HELPER_H

#include <limits>
#include <cmath>

class helper {
 public:
  static float to_radians(float angle);

  static bool almost_equal(const float &x, const float &y, const int ulp);
};

#endif //RAY_TRACER_HELPER_H
