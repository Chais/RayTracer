//
// Created by chais on 10.07.15.
//

#include "camera_exception.h"

camera_exception::camera_exception(const std::string &msg) : runtime_error(msg) { }

camera_exception::camera_exception(const char *msg) : runtime_error(msg) { }
