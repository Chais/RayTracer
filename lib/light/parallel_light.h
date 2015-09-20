//
// Created by chais on 06.08.15.
//

#ifndef RAY_TRACER_PARALLEL_LIGHT_H
#define RAY_TRACER_PARALLEL_LIGHT_H

#include "light.h"

class parallel_light : public light {
public:
	parallel_light(const color *col, const direction *dir);

	friend std::ostream &operator<<(std::ostream &out, const parallel_light &a);

	virtual direction *get_direction(const point &pos);

	virtual color *emit(const direction &dir);
};

#endif //RAY_TRACER_PARALLEL_LIGHT_H
