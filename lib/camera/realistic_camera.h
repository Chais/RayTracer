//
// Created by chais on 10.01.16.
//

#ifndef RAY_TRACER_REALISTIC_CAMERA_H
#define RAY_TRACER_REALISTIC_CAMERA_H


#include "perspective_camera.h"

class realistic_camera : public perspective_camera {
protected:
	float focus;

public:
	realistic_camera() : perspective_camera(), focus(std::numeric_limits<float>::max()) { }

	realistic_camera(const point &position, const point &look_at, const direction &up,
					 const std::array<unsigned long, 2> &resolution, const unsigned long max_bounces, const float &fov,
					 const std::shared_ptr<sampler> &s, float focus);

	virtual std::shared_ptr<std::vector<ray>> get_rays(const unsigned long &x, const unsigned long &y) override;
};


#endif //RAY_TRACER_REALISTIC_CAMERA_H
