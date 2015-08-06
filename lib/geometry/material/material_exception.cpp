//
// Created by chais on 06.08.15.
//

#include "material_exception.h"

material_exception::material_exception(const std::string &msg) : runtime_error(msg) { }

material_exception::material_exception(const char *msg) : runtime_error(msg) { }
