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
 *
 * Defines the interface every material has to implement. If methods aren't applicable for vertain materials they are implemented in a way that allows the program to continue.
 */
class material {
protected:
	material() { };
public:
	/**
	 * @brief Shades the material
	 *
	 * Determines the intensity of the material's color at the specified texture coordinates, based on light-
	 * and viewing direction as well as the normal and whether the material is viewed from the inside or the outside.
	 * @param lcol     The color of the light
	 * @param l        The direction the light is in. Expected to be a 0 vector for ambient light.
	 * @param n        The normal at the point that is being shaded
	 * @param v        The direction the ray is coming from
	 * @param pos      The texture coordinates as calculated by shape::intersect_full
	 * @param internal A flag denoting whether the ray originated from inside (true) or outside (false) the shape this material belongs to.
	 * @return         The base color multiplied by a factor according to the viewing situation
	 */
	virtual std::shared_ptr<color> shade
		(const color &lcol, const direction &l, const normal &n, const direction &v, const vec2 &pos,
		 const bool internal) const = 0;

	/**
	 * @brief Reflects a ray
	 * @param i The direction the incident ray is coming from
	 * @param n The normal on the surface
	 * @param x The position (in world coordinates) of the reflection
	 * @param s The number of samples
	 * @return The reflected ray(s)
	 */
	virtual std::shared_ptr<std::vector<ray>> reflect(const direction &i, const normal &n, const point &x,
													  const unsigned int &s) const = 0;

	/**
  	 * @brief Refracts a ray according to Snell's law
  	 * @details Calculates the origin and direction of refracted rays. Rays entering the material will be refracted towards the inverted normal. \f$\frac{\sin \sigma_i}{\sin \sigma_o}=\frac{1}{\mathtt{ior}}\f$. Conversely, rays leaving the material are refracted away from the normal. \f$\frac{\sin \sigma_i}{\sin \sigma_o}=\frac{\mathtt{ior}}{1}\f$. This results in total internal reflection angles greater than a critical angle that depends on \p ior.
  	 * @param i        The direction the incident ray is coming from
	 * @param n        The normal on the surface
	 * @param x        The position (in world coordinates) of the reflection
	 * @param s        The number of samples
	 * @param internal A flag denoting whether the ray originated from inside (true) or outside (false) the shape this material belongs
	 * @return The refracted ray(s)
  	 */
	virtual std::shared_ptr<std::vector<ray>> refract(const direction &i, const normal &n, const point &x,
													  const unsigned int &s, const bool internal) const = 0;

  	/**
  	 * @brief Returns the reflectance
  	 * @return The reflectance
  	 */
	virtual const float get_reflectance() const = 0;

	/**
	 * @brief Returns the transmittance
	 * @return The transmittance
	 */
	virtual const float get_transmittance() const = 0;
};

#endif //RAY_TRACER_MATERIAL_H
