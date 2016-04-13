/**
 * @file whittedrt.h
 * @author Philip Abernethy
 */

#ifndef RAY_TRACER_WHITTEDRT_H
#define RAY_TRACER_WHITTEDRT_H

#include "renderer.h"

/**
 * @brief A whitted ray tracer.
 */
class whitted_rt : public renderer {
protected:
	virtual color cast_ray(ray r, int step, bool internal) override;

public:
	whitted_rt(const std::shared_ptr<color> background_color, std::shared_ptr<camera> cam,
			   std::shared_ptr<std::vector<std::shared_ptr<light>>> lights,
			   std::shared_ptr<std::vector<std::shared_ptr<shape>>> scene);
};

#endif //RAY_TRACER_WHITTEDRT_H