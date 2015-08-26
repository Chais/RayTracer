//
// Created by chais on 06.08.15.
//

#ifndef RAY_TRACER_AMBIENT_LIGHT_H
#define RAY_TRACER_AMBIENT_LIGHT_H

#include <ostream>
#include "../geometry/direction.h"
#include "../geometry/color.h"

class light {
protected:
	color col;

	light(const color &col);

public:
	friend std::ostream &operator<<(std::ostream &out, const light &a);

	virtual color &emit(const direction &dir) const = 0;
};

#endif //RAY_TRACER_AMBIENT_LIGHT_H
