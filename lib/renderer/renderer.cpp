//
// Created by chais on 01/04/16.
//

#include <iomanip>
#include "renderer.h"

renderer::renderer(const std::shared_ptr<color> &background_color, const std::shared_ptr<camera> &cam,
				   const std::shared_ptr<std::vector<std::shared_ptr<light>>> &lights,
				   const std::shared_ptr<std::vector<std::shared_ptr<shape>>> &scene) : background_color(
		background_color), cam(cam), lights(lights), scene(scene) { }

bool renderer::cast_shadow(const position &o, const direction &d) {
	for (std::shared_ptr<shape> obstacle : *scene)
		if (obstacle->intersect_shadow(o, d))
			return true;
	return false;
}

intersection renderer::find_nearest(ray r) {
	intersection out = intersection();
	float dist = std::numeric_limits<float>::max();
	for (std::shared_ptr<shape> object : *scene) {
		intersection cur = object->intersect_full(r);
		if (!cur.object)
			continue;
		float new_dist = length(r.o - *cur.pos);
		if (new_dist < dist) {
			dist = new_dist;
			out = cur;
		}
	}
	return out;
}

std::shared_ptr<color> renderer::get_pixel(const unsigned long &x, const unsigned long &y) const {
	return cam->get_pixel(x, y);
}

const std::array<unsigned long, 2> &renderer::get_resolution() const {
	return cam->resolution;
}

void renderer::render() {
	const std::array<unsigned long, 2> resolution = cam->resolution;
	float completed = 0;
	float perline = 100.0f/resolution[1];
	std::cout << '\r' << std::setw(6) << std::fixed << std::setprecision(2) << completed << " %";
	std::cout.flush();
	for (unsigned long y = 0; y < resolution[1]; y++) {
#ifdef NDEBUG
#pragma omp parallel for
#endif
		for (unsigned long x = 0; x < resolution[0]; x++) {
			std::shared_ptr<std::vector<ray>> rays = cam->get_rays(x, y);
			std::vector<color> data;
			data.reserve(rays->size());
			for (auto &r : *rays)
				data.push_back(cast_ray(r, 0, false));
			cam->set_data(x, y, data);
		}
		std::cout << '\r' << std::setw(6) << std::fixed << std::setprecision(2) << (completed+=perline) << " %";
		std::cout.flush();
	}
}