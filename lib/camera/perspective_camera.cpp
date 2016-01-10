#include "perspective_camera.h"

perspective_camera::perspective_camera() : perspective_camera(point(0, 0, 0), point(0, 0, -1), direction(0, 1, 0),
															  {1024, 768}, 10, 45,
															  std::make_shared<sampler>(sampler())) {
}

perspective_camera::perspective_camera(const point &position, const point &look_at, const direction &up,
									   const std::array<unsigned long, 2> &resolution, const unsigned long max_bounces,
									   const float &fov, const std::shared_ptr<sampler> s) :
		camera(position, look_at, up, resolution, max_bounces, s), fov(fov) {
	assert(0 < fov && fov < 90);
	stepwidth = std::tan(helper::to_radians(this->fov)) / (resolution[0] / 2);
	start = direction(0, 0, 1) + direction(1, 0, 0) * (((resolution[0] - 1) / 2.0) * stepwidth) +
			direction(0, 1, 0) * (((resolution[1] - 1) / 2.0) * stepwidth);
}

std::shared_ptr<std::vector<ray>> perspective_camera::get_rays(const unsigned long &x, const unsigned long &y) {
	std::shared_ptr<std::vector<vec2>> offsets = this->s->get_samples();
	std::shared_ptr<std::vector<ray>> out(new std::vector<ray>());
	direction d =
			this->start + direction(-1, 0, 0) * (this->stepwidth * x) + direction(0, -1, 0) * (this->stepwidth * y);
	for (vec2 o : *offsets) {
		out->push_back(this->transforms(ray(point(o[0], o[1], 0)+d, d)));
	}
	return out;
}