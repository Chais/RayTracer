//
// Created by chais on 15.09.15.
//

#ifndef RAY_TRACER_POINT_LIGHT_H
#define RAY_TRACER_POINT_LIGHT_H

#include "light.h"

/**
 * Models a point light source
 */
class point_light: public light {
protected:
	/**
	 * The \ref point "position" (in world coordinates) of the light
	 */
	const std::shared_ptr<point> position;
public:
	/**
	 * @brief Explicit constructor
	 * @param col The \ref color of the light
	 * @param pos The \ref point "position" stored in \p position
	 */
	point_light(const std::shared_ptr<color> col, const std::shared_ptr<point> pos);

	/**
	 * @copybrief light::get_direction()
	 *
	 * Returns \p pos - \p position.
	 * \copydetails light::get_direction()
	 */
	virtual const std::shared_ptr<direction> get_direction(const point &pos);

	/**
	 * @copydoc ambient_light::emit()
	 */
	virtual const std::shared_ptr<color> emit(const direction &dir);
};

#endif //RAY_TRACER_POINT_LIGHT_H
