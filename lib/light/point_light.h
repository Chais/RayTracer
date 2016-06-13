//
// Created by chais on 15.09.15.
//

#ifndef RAY_TRACER_POINT_LIGHT_H
#define RAY_TRACER_POINT_LIGHT_H

#include "light.h"
#include "../geometry/shapes/point.h"
#include "../geometry/material/solid_material.h"
#include "../sampler/random_sampler.h"

/**
 * Models a position light source
 */
class point_light : public light, public point {
public:
	virtual const float get_total_area() const override;

/**
	 * @brief Explicit constructor
	 * @param col The \ref color of the light
	 * @param pos The \ref position "position" stored in \p position
	 */
	point_light(const std::shared_ptr<color> emit_col, const direction &offset);

	/**
	 * @copybrief light::get_direction()
	 *
	 * Returns \p pos - \p position.
	 * \copydetails light::get_directions()
	 */
	virtual const std::shared_ptr<std::vector<intersection>> get_directions(const position &pos,
																		 const unsigned long &samples) const;

	/**
	 * @copydoc ambient_light::emit()
	 */
	virtual const std::shared_ptr<color> emit(const direction &dir, const intersection &is) const;

	virtual intersection intersect_full(const ray &r) const override;

	virtual bool intersect_shadow(const position &o, const direction &d) const override;

	virtual const std::shared_ptr<std::vector<ray>> shed(unsigned long samples) const override;
};

#endif //RAY_TRACER_POINT_LIGHT_H
