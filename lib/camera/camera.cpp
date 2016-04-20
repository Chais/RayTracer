//
// Created by chais on 09.09.15.
//

#include "camera.h"

camera::camera(const position &pos, const position &look_at, const direction &up,
			   const std::array<unsigned long, 2> &resolution, const unsigned long max_bounces,
			   const unsigned long &samples, const unsigned long &sr, const std::shared_ptr<sampler> s)
		: resolution(resolution), max_bounces(max_bounces), samples(samples), shadow_rays(sr), s(s) {
	assert(resolution[0] > 0 && resolution[1] > 0);
	direction dir = normalise(look_at - pos);
	direction left = cross(normalise(up), dir);
	direction new_up = cross(dir, left);
	std::array<std::array<float, 4>, 4> d = {{
													 {left[0], new_up[0], dir[0], pos[0]},
													 {left[1], new_up[1], dir[1], pos[1]},
													 {left[2], new_up[2], dir[2], pos[2]},
													 {0, 0, 0, 1}
											 }};
	std::shared_ptr<mat4> m(new mat4(d));
	transforms = transform(m);
	data.resize(resolution[0]);
	for (std::vector<color> &i : data) {
		i.resize(resolution[1]);
		for (color &j : i)
			j = color();
	}
}

void camera::set_pixel(const unsigned long &x, const unsigned long &y, const color &data) {
	this->data[x][y] = data;
}

const color &camera::get_pixel(const unsigned long &x, const unsigned long &y) const {
	return data[x][y];
}