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
protected:
	color col;
	solid_material(const color &col);
};

#endif //RAY_TRACER_SOLID_MATERIAL_H
