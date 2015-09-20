//
// Created by chais on 15.09.15.
//

#ifndef RAY_TRACER_POINT_LIGHT_H
#define RAY_TRACER_POINT_LIGHT_H

#include "light.h"

class point_light : public light {
protected:
	const point *position;
public:
	point_light(const color *col, const point *pos);

	virtual direction *get_direction(const point &pos);

	virtual color *emit(const direction &dir);
};

#endif //RAY_TRACER_POINT_LIGHT_H