//
// Created by chais on 06.08.15.
//

#ifndef RAY_TRACER_SOLID_MATERIAL_H
#define RAY_TRACER_SOLID_MATERIAL_H

#include "material.h"

/**
 * @name solid_material
 *
 * @brief Models solid materials
 *
 * All solid materials should have a color
 */
class solid_material : public material {
public:
	solid_material(const std::shared_ptr<color> emit_col, const std::shared_ptr<color> col);

	virtual const std::shared_ptr<color> shade(const color &lcol, const direction &l, const normal &n,
											   const direction &v, const vec2 &pos,
											   const bool &internal) const override;

	virtual std::shared_ptr<ray> reflect(const direction &i, const normal &n, const position &x) const override;

	virtual std::shared_ptr<ray> refract(const direction &i, const normal &n, const position &x,
										 const bool &internal) const override;

	virtual const float get_reflectance() const override;

	virtual const float get_transmittance() const override;
};

#endif //RAY_TRACER_SOLID_MATERIAL_H
