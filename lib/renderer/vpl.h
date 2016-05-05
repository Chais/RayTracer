//
// Created by chais on 27/04/16.
//

#ifndef RAY_TRACER_VPL_H
#define RAY_TRACER_VPL_H

#include "renderer.h"
#include "../light/hemisphere_light.h"

class vpl : public renderer {
protected:
	//std::vector<std::vector<std::shared_ptr<hemisphere_light>>> vpls;
	virtual color cast_ray(ray r, int step, bool internal) override;
	virtual void spread_light();

public:
	vpl(const std::shared_ptr<color> &background_color, const std::shared_ptr<camera> &cam,
		const std::shared_ptr<std::vector<std::shared_ptr<light>>> &lights,
		const std::shared_ptr<std::vector<std::shared_ptr<shape>>> &scene);

	virtual void render() override;
};

#endif //RAY_TRACER_VPL_H