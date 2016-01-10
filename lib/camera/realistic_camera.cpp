//
// Created by chais on 10.01.16.
//

#include "realistic_camera.h"


realistic_camera::realistic_camera(const point &position, const point &look_at, const direction &up,
								   const std::array<unsigned long, 2> &resolution, const unsigned long max_bounces,
								   const float &fov, const std::shared_ptr<sampler> &s, float focus)
		: perspective_camera(position, look_at, up,
							 resolution, max_bounces, fov,
							 s), focus(focus) {
	assert(focus > 1);
}

std::shared_ptr<std::vector<ray>> realistic_camera::get_rays(const unsigned long &x, const unsigned long &y) {
	std::shared_ptr<std::vector<vec2>> offsets = this->s->get_samples();
	std::shared_ptr<std::vector<ray>> out(new std::vector<ray>());
	direction d =
			this->start + direction(-1, 0, 0) * (this->stepwidth * x) + direction(0, -1, 0) * (this->stepwidth * y);
	point fp = point(focus*d);
	for (vec2 os : *offsets) {
		point o = point(os[0], os[1], 0)+d;
		out->push_back(this->transforms(ray(o, fp-o)));
	}
	return out;
}
