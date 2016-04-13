//
// Created by chais on 01/04/16.
//

#ifndef RAY_TRACER_PATHTRACER_H
#define RAY_TRACER_PATHTRACER_H

#include "renderer.h"

class pathtracer : public renderer {
protected:
	virtual color cast_ray(ray r, int step, bool internal) override;
	virtual std::shared_ptr<direction> rnd_in_cone(const direction &center, const float &angle) const;

public:
	pathtracer(const std::shared_ptr<color> &background_color, const std::shared_ptr<camera> &cam,
		   const std::shared_ptr<std::vector<std::shared_ptr<light>>> &lights,
		   const std::shared_ptr<std::vector<std::shared_ptr<shape>>> &scene);
};

#endif //RAY_TRACER_PATHTRACER_H