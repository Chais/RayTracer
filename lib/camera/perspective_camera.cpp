#include "perspective_camera.h"

perspective_camera::perspective_camera() : perspective_camera(point(0, 0, 0), point(0, 0, -1), direction(0, 1, 0),
															  {1024, 768}, 10, 45, 1,
															  (std::shared_ptr<sampler>(new sampler())), 0) {
}

perspective_camera::perspective_camera(const point &position, const point &look_at, const direction &up,
									   const std::array<unsigned long, 2> &resolution, const unsigned long max_bounces,
									   const float &fov, const unsigned long &samples,
									   const std::shared_ptr<sampler> sampler, const float &defocus) :
		camera(position, look_at, up, resolution, max_bounces, samples, sampler), fov(fov), defocus(defocus) {
	assert(0 < fov && fov < 90);
	assert(defocus >= 0);
	stepwidth = std::tan(helper::to_radians(fov)) / (resolution[0] / 2);
	start = direction(0, 0, 1) + direction(1, 0, 0) * (((resolution[0] - 1) / 2.0) * stepwidth) +
			direction(0, 1, 0) * (((resolution[1] - 1) / 2.0) * stepwidth);
}

std::shared_ptr<std::vector<ray>> perspective_camera::get_rays(const unsigned long &x, const unsigned long &y) {
	std::shared_ptr<std::vector<vec2>> offsets = s->get_samples(defocus, defocus, samples);
	std::shared_ptr<std::vector<ray>> out(new std::vector<ray>());
	direction d = start + direction(-1, 0, 0) * (stepwidth * x) + direction(0, -1, 0) * (stepwidth * y);
	for (vec2 o : *offsets)
		out->push_back(transforms(ray(point(), d + direction(o[0], o[1], 0))));
	return out;
}