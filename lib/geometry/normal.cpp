//
// Created by chais on 25.08.15.
//

#include "normal.h"

normal::normal() : vec4() { }

normal::normal(const float &x, const float &y, const float &z) : vec4(x, y, z, 0) { }

normal::normal(const vec4 &in) : vec4(in[0], in[1], in[2], 0) { }

normal::normal(const normal &in) : vec4(in) { }