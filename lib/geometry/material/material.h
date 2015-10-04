//
// Created by chais on 06.08.15.
//

#ifndef RAY_TRACER_MATERIAL_H
#define RAY_TRACER_MATERIAL_H

#include "../../math/vec2.h"
#include "../direction.h"
#include "../normal.h"
#include "../color.h"
#include "../ray.h"
#include <memory>

/**
 * @name material
 * @brief Abstract material class
 * @details Defines the interface every material has to implement.
 */
class material {
protected:
	material() { };
public:
	/**
	 * @brief Shading
	 * Determines the intensity of the material's color at the specified texture coordinates, based on light-
	 * and viewing direction as well as the normal and whether the material is viewed from the inside or the outside.
	 * @param &lcol the color of the light
	 * @param &l the direction the light is in. Expected to be a 0 vector for ambient light.
	 * @param &n the normal at the point that is being shaded
	 * @param &v the direction the ray is coming from
	 * @param &pos the texture coordinates as calculated by shape::intersect_full
	 * @param internal a flag denoting whether the ray originated from inside or outside the shape this material belongs
	 * to.
	 * @return the base color multiplied by a factor according to the viewing situation
	 */
	virtual std::shared_ptr<color> shade
		(const color &lcol, const direction &l, const normal &n, const direction &v, const vec2 &pos,
		 const bool internal) const = 0;

	virtual std::shared_ptr<std::vector<ray>> reflect(const direction &i, const normal &n, const point &x,
													  const unsigned int &s) const = 0;

	virtual std::shared_ptr<std::vector<ray>> refract(const direction &i, const normal &n, const point &x,
													  const unsigned int &s, const bool internal) const = 0;

	virtual const float get_reflectance() const = 0;

	virtual const float get_transmittance() const = 0;
};

#endif //RAY_TRACER_MATERIAL_H
