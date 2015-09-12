//
// Created by chais on 06.08.15.
//

#include "light.h"
#include "../geometry/direction.h"

light::light(const color &col) : col(col), dir(direction()) { }

light::light(const color &col, const direction &dir) : col(col), dir(normalise(dir)) { }
