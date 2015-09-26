//
// Created by chais on 06.08.15.
//

#ifndef RAY_TRACER_LIGHT_H
#define RAY_TRACER_LIGHT_H

#include <ostream>
#include "../geometry/color.h"
#include "../geometry/point.h"
#include "../geometry/transform.h"

class light {
 protected:
  const color *col;
  const direction *dir;

  light(const color *col);

  light(const color *col, const direction *dir);

 public:
  virtual direction *get_direction(const point &pos) = 0;

  virtual color *emit(const direction &dir) = 0;
};

#endif //RAY_TRACER_LIGHT_H
