//
// Created by chais on 23.09.15.
//

#ifndef RAY_TRACER_TEXTURED_MATERIAL_H
#define RAY_TRACER_TEXTURED_MATERIAL_H

#include "phong_material.h"

class textured_material: public phong_material {
protected:
	/**
	 * The texture data
	 */
	std::shared_ptr<std::vector<std::vector<color>>> texture;
public:
	/**
	 * @brief Explicit constructor
	 * @param ambient  The scaling factor for ambient lighting
	 * @param diffuse  The scaling factor for diffuse lighting
	 * @param specular The scaling factor for specular lighting
	 * @param exponent The specular exponent
	 * @param texture  The texture data
	 */
	textured_material(const float &ambient, const float &diffuse, const float &specular,
					  const float &exponent, std::shared_ptr<std::vector<std::vector<color>>> texture);

	virtual std::shared_ptr<color>
		shade(const color &lcol, const direction &l, const normal &n, const direction &v, const vec2 &pos,
			  const bool internal) const override;
};

#endif //RAY_TRACER_TEXTURED_MATERIAL_H
