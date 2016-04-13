//
// Created by chais on 09.09.15.
//

#include "ray.h"

ray::ray(const position &o, const direction &d) : o(o), d(normalise(d)) { }
