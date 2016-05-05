//
// Created by chais on 06.08.15.
//

#ifndef RAY_TRACER_PARALLEL_LIGHT_H
#define RAY_TRACER_PARALLEL_LIGHT_H

#include "light.h"
#include "../geometry/shapes/point.h"
#include "../geometry/material/solid_material.h"

/**
 * Models a parallel light source
 */
class parallel_light : public light, public point {
public:
	/**
	 * @copydoc light::light()
	 */
	parallel_light(const std::shared_ptr<color> emit_col, const direction &emit_dir);

	friend std::ostream &operator<<(std::ostream &out, const parallel_light &a);

	/**
	 * @copybrief light::get_direction()
	 *
	 * Returns the \ref direction stored in \p light::dir
	 * @copydetails light::get_directions()
	 */
	virtual const std::shared_ptr<std::vector<direction>> get_directions(const position &pos,
																		 const unsigned long &samples) const;

	/**
	 * @copydoc ambient_light::emit()
	 */
	virtual const std::shared_ptr<color> emit(const direction &dir) const;

	virtual intersection intersect_full(const ray &r) const override;

	virtual bool intersect_shadow(const position &o, const direction &d) const override;

	virtual const std::shared_ptr<std::vector<ray>> shed(unsigned long samples) const override;
};

#endif //RAY_TRACER_PARALLEL_LIGHT_H
