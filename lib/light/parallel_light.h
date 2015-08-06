//
// Created by chais on 06.08.15.
//

#ifndef RAY_TRACER_PARALLEL_LIGHT_H
#define RAY_TRACER_PARALLEL_LIGHT_H

#include "ambient_light.h"

class parallel_light : public ambient_light {
protected:
	vec3 direction;
public:
	parallel_light(const vec3 &color, const vec3 &direction);

	friend std::ostream &operator<<(std::ostream &out, const parallel_light &a);

	const vec3 &getDirection() const;
};

#endif //RAY_TRACER_PARALLEL_LIGHT_H
