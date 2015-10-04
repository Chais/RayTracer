//
// Created by chais on 23.09.15.
//

#ifndef RAY_TRACER_TEXTURED_MATERIAL_H
#define RAY_TRACER_TEXTURED_MATERIAL_H

#include <string>
#include <png++/image.hpp>
#include "phong_material.h"

class textured_material: public phong_material {
protected:
	std::shared_ptr<std::vector<std::vector<color>>> texture;
public:
	textured_material(const float &ambient, const float &diffuse, const float &specular,
					  const float &exponent, std::shared_ptr<std::vector<std::vector<color>>> texture);

	virtual std::shared_ptr<color>
		shade(const color &lcol, const direction &l, const normal &n, const direction &v, const vec2 &pos,
			  const bool internal) const override;
};

#endif //RAY_TRACER_TEXTURED_MATERIAL_H
