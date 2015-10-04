//
// Created by chais on 06.08.15.
//

#ifndef RAY_TRACER_PARALLEL_LIGHT_H
#define RAY_TRACER_PARALLEL_LIGHT_H

#include "light.h"

/**
 * Models a parallel light source
 */
class parallel_light: public light {
public:
	/**
	 * @copydoc light::light()
	 */
	parallel_light(const std::shared_ptr<color> col, const std::shared_ptr<direction> dir);

	friend std::ostream &operator<<(std::ostream &out, const parallel_light &a);

	/**
	 * @copybrief light::get_direction()
	 *
	 * Returns the \ref direction stored in \p light::dir
	 * @copydetails light::get_direction()
	 */
	virtual const std::shared_ptr<direction> get_direction(const point &pos);

	/**
	 * @copydoc ambient_light::emit()
	 */
	virtual const std::shared_ptr<color> emit(const direction &dir);
};

#endif //RAY_TRACER_PARALLEL_LIGHT_H
