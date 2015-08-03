//
// Created by chais on 23.07.15.
//

#ifndef RAY_TRACER_RAY_H
#define RAY_TRACER_RAY_H

#include "../math/vec3.h"

class ray {
private:
	vec3 origin, direction;
	vec3 *color;

public:
	/**
	 * @brief Minimal constructor
	 * Minimal constructor with origin and direction
	 */
	ray(const vec3 &origin, const vec3 &direction);

	/**
	 * @brief Explicit constructor
	 * Constructor with origin, direciton and color. Useful for reflected rays.
	 */
	ray(const vec3 &origin, const vec3 &direction, const vec3 &color);

	/**
	 * @brief Destructor
	 * Deallocates the memory for the color vector
	 */
	virtual ~ray();

/**
	 * @brief output operator
	 * Puts the ray's origin and direction on the out stream
	 */
	friend std::ostream &operator<<(std::ostream &out, const ray &a);

	/**
	 * @brief returns a copy of the origin vector
	 */
	vec3 getOrigin() const;

	/**
	 * @brief returns a copy of the direction vector
	 */
	vec3 getDirection() const;

	/**
	 * @brief returns a copy of the color vector
	 */
	vec3 *getColor() const;

	/**
	 * @brief sets the color
	 */
	void setColor(const vec3 &color);
};

#endif //RAY_TRACER_RAY_H
