//
// Created by chais on 10.07.15.
//

#include <stdexcept>

#ifndef RAY_TRACER_CAMERAEXCEPTION_H
#define RAY_TRACER_CAMERAEXCEPTION_H

class camera_exception : std::runtime_error {
public:
	camera_exception(const std::string &msg);

	camera_exception(const char *msg);
};

#endif //RAY_TRACER_CAMERAEXCEPTION_H