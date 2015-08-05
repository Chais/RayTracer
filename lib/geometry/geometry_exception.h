//
// Created by chais on 03.08.15.
//

#include <stdexcept>

#ifndef RAY_TRACER_GEOMETRY_EXCEPTION_H
#define RAY_TRACER_GEOMETRY_EXCEPTION_H

class geometry_exception : std::runtime_error{
public:
	geometry_exception(const std::string &__arg) : runtime_error(__arg) { }
	geometry_exception(const char *msg) : runtime_error(msg){ }
};

#endif //RAY_TRACER_GEOMETRY_EXCEPTION_H