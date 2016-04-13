//
// Created by chais on 10.01.16.
//

#ifndef RAY_TRACER_REALISTIC_CAMERA_H
#define RAY_TRACER_REALISTIC_CAMERA_H


#include "perspective_camera.h"

class realistic_camera : public perspective_camera {
protected:
	float focus;
	float aperture;

public:
	realistic_camera() : perspective_camera(), focus(1), aperture(0) { }

	realistic_camera(const position &pos, const position &look_at, const direction &up,
						 const std::array<unsigned long, 2> &resolution, const unsigned long max_bounces,
						 const float &fov, const unsigned long &samples, const unsigned long &sr,
						 const std::shared_ptr<sampler> s, const float &defocus, const float &focus,
						 const float &aperture);

	virtual std::shared_ptr<std::vector<ray>> get_rays(const unsigned long &x, const unsigned long &y) override;
};
#endif //RAY_TRACER_REALISTIC_CAMERA_H