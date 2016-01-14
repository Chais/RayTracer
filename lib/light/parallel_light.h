//
// Created by chais on 06.08.15.
//

#ifndef RAY_TRACER_PARALLEL_LIGHT_H
#define RAY_TRACER_PARALLEL_LIGHT_H

#include "light.h"
#include "../geometry/shapes/shape.h"
#include "../geometry/material/lambertian_material.h"

/**
 * Models a parallel light source
 */
class parallel_light: public light, public shape {
public:
	/**
	 * @copydoc light::light()
	 */
	parallel_light(const std::shared_ptr<color> &col, const std::shared_ptr<direction> &dir);

	friend std::ostream &operator<<(std::ostream &out, const parallel_light &a);

	/**
	 * @copybrief light::get_direction()
	 *
	 * Returns the \ref direction stored in \p light::dir
	 * @copydetails light::get_direction()
	 */
	virtual const std::shared_ptr<direction> get_direction(const point &pos) const;

	/**
	 * @copydoc ambient_light::emit()
	 */
	virtual const std::shared_ptr<color> emit(const direction &dir) const;

	virtual intersection intersect_full(const ray &r) override;

	virtual bool intersect_shadow(const point &o, const direction &d) const override;
};

#endif //RAY_TRACER_PARALLEL_LIGHT_H
