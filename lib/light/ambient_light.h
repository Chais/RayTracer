//
// Created by chais on 06.08.15.
//

#ifndef RAY_TRACER_AMBIENT_LIGHT_H
#define RAY_TRACER_AMBIENT_LIGHT_H

#include <ostream>
#include "../math/vec3.h"

class ambient_light {
protected:
	vec3 color;
public:
	ambient_light(const vec3 &color);

	virtual ~ambient_light() { }

	friend std::ostream &operator<<(std::ostream &out, const ambient_light &a);

	const vec3 &getColor() const;
};

#endif //RAY_TRACER_AMBIENT_LIGHT_H
