//
// Created by chais on 10.01.16.
//

#include "realistic_camera.h"


realistic_camera::realistic_camera(const point &position, const point &look_at, const direction &up,
								   const std::array<unsigned long, 2> &resolution, const unsigned long max_bounces,
								   const float &fov, const std::shared_ptr<sampler> &s, float focus)
		: perspective_camera(position, look_at, up, resolution, max_bounces, fov, s), focus(focus) {
	assert(focus > 0);
}

std::shared_ptr<std::vector<ray>> realistic_camera::get_rays(const unsigned long &x, const unsigned long &y) {
	std::shared_ptr<std::vector<vec2>> offsets = s->get_samples();
	std::shared_ptr<std::vector<vec2>> focus_offsets = s->get_samples();
	std::shared_ptr<std::vector<ray>> out(new std::vector<ray>());
	direction d =
			start + direction(-1, 0, 0) * (stepwidth * x) + direction(0, -1, 0) * (stepwidth * y);
	point fp = point(focus * d);
	//for (vec2 os : *offsets) {
	for (unsigned long i = 0; i < offsets->size(); i++) {
		point o = point((*offsets)[i][0], (*offsets)[i][1], 0);
		out->push_back(transforms(ray(o, fp-o+direction((*focus_offsets)[i][0]/focus, (*focus_offsets)[i][1]/focus, 0))));
	}
	return out;
}
