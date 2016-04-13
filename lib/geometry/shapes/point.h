//
// Created by chais on 29/03/16.
//

#ifndef RAY_TRACER_POINT_H
#define RAY_TRACER_POINT_H

#include "shape.h"

class point : public shape {
public:
	point(const direction &offset, const std::shared_ptr<material> &matrl);

	virtual intersection intersect_full(const ray &r) const override;

	virtual bool intersect_shadow(const position &o, const direction &d) const override;
};
#endif //RAY_TRACER_POINT_H