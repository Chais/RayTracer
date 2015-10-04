//
// Created by chais on 26.08.15.
//

#ifndef RAY_TRACER_AMBIENT_LIGHT_H
#define RAY_TRACER_AMBIENT_LIGHT_H

#include "../geometry/color.h"
#include "light.h"
#include "../geometry/direction.h"

/**
 * Models an ambient light source
 */
class ambient_light: public light {
public:
	/**
	 * @brief Constructor
	 *
	 * \p light::dir is set to [0, 0, 0, 0] as ambient light is omnidirectional.
	 * @param col The \ref color of the ambient light
	 */
	ambient_light(const std::shared_ptr<color> col);

	friend std::ostream &operator<<(std::ostream &out, const ambient_light &a);

	/**
	 * @copybrief light::get_direction()
	 *
	 * Returns the 0 vector stored in \p light::dir
	 * @copydetails light::get_direction()
	 */
	virtual const std::shared_ptr<direction> get_direction(const point &pos);

	/**
	 * @copybrief light::emit()
	 *
	 * Returns the color stored in \p light::col
	 * @copydetails light::emit()
	 */
	virtual const std::shared_ptr<color> emit(const direction &dir);
};

#endif //RAY_TRACER_AMBIENT_LIGHT_H
