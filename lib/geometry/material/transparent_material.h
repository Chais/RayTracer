//
// Created by chais on 24.09.15.
//

#ifndef RAY_TRACER_TRANSMISSIVE_MATERIAL_H
#define RAY_TRACER_TRANSMISSIVE_MATERIAL_H

#include "specular_material.h"

/**
 * Models a transparent material with a smooth surface. It reflects light and refracts it according to its index of refraction. It is assumed that outside the geometry there is vacuum, with an index of refraction of 1. Inclusion of geometry (e.g. a sphere inside a sphere) is not currently supported and will give incorrect results. Beer's law is not currently implemented.
 */
class transparent_material: public specular_material {
protected:
	/**
	 * The factor by which the colour resulting from transmitted (refracted) rays is scaled. \p transmittance + \p reflectance must be <= 1
	 */
	const float transmittance;
	/**
	 * The index of refraction of the material
	 */
	const float ior;
public:
	/**
	 * @brief Explicit constructor
	 * @param col           The colour
	 * @param ambient       The scaling factor for ambient lighting
	 * @param diffuse       The scaling factor for diffuse lighting
	 * @param specular      The scaling factor for specular lighting
	 * @param exponent      The specular exponent
	 * @param reflectance   The scaling factor for reflected rays
	 * @param transmittance The scaling factor for refracted rays
	 * @param ior           The index of refraction
	 */
	transparent_material(const color &col, const float &ambient, const float &diffuse, const float &specular,
						 const float &exponent, const float reflectance, const float transmittance, const float ior);

	virtual std::shared_ptr<color>
		shade(const color &lcol, const direction &l, const normal &n, const direction &v, const vec2 &pos,
			  const bool internal) const override;

	virtual std::shared_ptr<std::vector<ray>> refract(const direction &i, const normal &n, const point &x,
														  const bool internal) const override;

	virtual const float get_transmittance() const override;
};

#endif //RAY_TRACER_TRANSMISSIVE_MATERIAL_H
