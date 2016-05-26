//
// Created by chais on 06.08.15.
//

#ifndef RAY_TRACER_LIGHT_H
#define RAY_TRACER_LIGHT_H

#include "../geometry/direction.h"
#include "../geometry/position.h"
#include "../geometry/color.h"
#include "../geometry/ray.h"
#include "../geometry/intersection.h"
#include <memory>
#include <ostream>
#include <vector>

/**
 * @brief Models generic lights
 *
 * Every light has a color. If omnidirectional lights are considered to have a 0 vector for direction every light also has a direction.
 */
class light {
protected:
	const direction emit_dir;
	light() {}
	/**
	 * Explicit constructor
	 * @param emit_dir The light's \ref direction
	 */
	light(const direction &emit_dir);

public:
	/**
	 * @brief Returns the direction the light shines on the position \p pos in.
	 * @param pos The \ref position (in world coordinates) to shine light on
	 * @return    The \ref direction the light is going to reach \p pos
	 */
	virtual const std::shared_ptr<std::vector<intersection>> get_directions(const position &pos,
																		 const unsigned long &samples) const = 0;

	/**
	 * @brief Returns the color the light is emitting in the direction \p dir.
	 * @param dir The \ref direction to emit to
	 * @return    The \ref color of the emitted light
	 */
	virtual const std::shared_ptr<color> emit(const direction &dir, const intersection &is) const = 0;

	virtual const std::shared_ptr<std::vector<ray>> shed(unsigned long samples) const = 0;
};
#endif //RAY_TRACER_LIGHT_H