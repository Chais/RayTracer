//
// Created by chais on 06.08.15.
//

#ifndef RAY_TRACER_PARALLEL_LIGHT_H
#define RAY_TRACER_PARALLEL_LIGHT_H

#include "light.h"

class parallel_light : public light {
protected:
	direction dir;
public:
	parallel_light(const color &col, const direction &dir);

	friend std::ostream &operator<<(std::ostream &out, const parallel_light &a);

	const direction &get_direction() const;

	virtual color &emit(const direction &dir) const;
};

#endif //RAY_TRACER_PARALLEL_LIGHT_H
