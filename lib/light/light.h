//
// Created by chais on 06.08.15.
//

#ifndef RAY_TRACER_LIGHT_H
#define RAY_TRACER_LIGHT_H

#include "../geometry/color.h"
#include "../geometry/point.h"
#include "../geometry/transform.h"
#include <memory>
#include <ostream>

/**
 * @brief Models generic lights
 *
 * Every light has a color. If omnidirectional lights are considered to have a 0 vector for direction every light also has a direction.
 */
class light {
protected:
	const std::shared_ptr<color> emit_color;
	const std::shared_ptr<direction> emit_dir;

	/**
	 * @brief Minimal constructor
	 *
	 * \p dir is set to [0, 0, 0, 0] for omnidirectional lights
	 * @param col The light's \ref color
	 */
	light(const std::shared_ptr<color> col);

	/**
	 * Explicit constructor
	 * @param col The light's \ref color
	 * @param dir The light's \ref direction
	 */
	light(const std::shared_ptr<color> col, const std::shared_ptr<direction> dir);

public:
	/**
	 * @brief Returns the direction the light shines on the position \p pos in.
	 * @param pos The \ref point (in world coordinates) to shine light on
	 * @return    The \ref direction the light is going to reach \p pos
	 */
	virtual const std::shared_ptr<direction> get_direction(const point &pos) const = 0;

	/**
	 * @brief Returns the color the light is emitting in the direction \p dir.
	 * @param dir The \ref direction to emit to
	 * @return    The \ref color of the emitted light
	 */
	virtual const std::shared_ptr<color> emit(const direction &dir) const = 0;
};

#endif //RAY_TRACER_LIGHT_H
