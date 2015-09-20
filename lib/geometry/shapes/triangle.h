//
// Created by chais on 18.09.15.
//

#ifndef RAY_TRACER_TRIANGLE_H
#define RAY_TRACER_TRIANGLE_H

#include "shape.h"

class triangle {
protected:
	std::array<point, 3> *vertices;
	std::array<normal, 3> *normals;
	std::array<vec2, 3> *texture_coords;
public:
	triangle(std::array<point, 3> *vertices, std::array<normal, 3> *normals, std::array<vec2, 3> *texture_coords);

	virtual intersection intersect_full(const ray &r);

	virtual bool intersect_shadow(const ray &r);

	virtual normal * get_avg_normal();

	virtual normal * get_barycentric_normal(const float &a, const float &b, const float &c);
};

#endif //RAY_TRACER_TRIANGLE_H
