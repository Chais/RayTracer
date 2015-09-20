//
// Created by chais on 06.08.15.
//

#include "light.h"

light::light(const color *col) : col(col), dir(new direction()) { }

light::light(const color *col, const direction *dir) : col(col), dir(new direction(normalise(*dir))) {

}
