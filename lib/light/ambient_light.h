//
// Created by chais on 26.08.15.
//

#ifndef RAY_TRACER_AMBIENT_LIGHT_H
#define RAY_TRACER_AMBIENT_LIGHT_H

#include "../geometry/color.h"
#include "light.h"
#include "../geometry/direction.h"

class ambient_light : public light {
public:
	ambient_light(color col);
	friend std::ostream &operator<<(std::ostream &out, const ambient_light &a);

	virtual direction &get_direction(const point &pos);

	virtual color &emit(const direction &dir);
};

#endif //RAY_TRACER_AMBIENT_LIGHT_H
