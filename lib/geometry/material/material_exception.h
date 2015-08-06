//
// Created by chais on 06.08.15.
//

#ifndef RAY_TRACER_MATERIAL_EXCEPTION_H
#define RAY_TRACER_MATERIAL_EXCEPTION_H

#include <stdexcept>

class material_exception : std::runtime_error {
public:
	material_exception(const std::string &msg);

	material_exception(const char *msg);
};

#endif //RAY_TRACER_MATERIAL_EXCEPTION_H