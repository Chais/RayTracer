//
// Created by chais on 10.01.16.
//

#include "realistic_camera.h"

realistic_camera::realistic_camera(const position &pos, const position &look_at, const direction &up,
								   const std::array<unsigned long, 2> &resolution, const unsigned long max_bounces,
								   const float &fov, const unsigned long &samples, const unsigned long &sr,
								   const std::shared_ptr<sampler> s, const float &defocus, const float &focus,
								   const float &aperture)
		: perspective_camera(pos, look_at, up, resolution, max_bounces, fov, samples, sr, s, defocus), focus(focus),
		  aperture(aperture) {
	assert(focus > 0);
	assert(aperture >= 0);
}

std::shared_ptr<std::vector<ray>> realistic_camera::get_rays(const unsigned long &x, const unsigned long &y) {
	std::shared_ptr<std::vector<vec2>> offsets = s->get_2d_samples(-aperture / 2, aperture / 2, -aperture / 2,
																   aperture / 2, samples);
	std::shared_ptr<std::vector<float>> focus_offsets = s->get_1d_samples(-defocus / 2, defocus / 2, samples);
	std::shared_ptr<std::vector<ray>> out(new std::vector<ray>());
	direction d =
			start + direction(-1, 0, 0) * (stepwidth * x) + direction(0, -1, 0) * (stepwidth * y);
	for (unsigned long i = 0; i < offsets->size(); i++) {
		position o = position((*offsets)[i][0], (*offsets)[i][1], 0);
		out->push_back(transforms(ray(o, position((focus + focus_offsets->at(i)) * d) - o)));
	}
	return out;
}
