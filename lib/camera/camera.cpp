//
// Created by chais on 09.09.15.
//

#include "camera.h"

camera::camera(const point &position, const point &look_at, const direction &up,
			   const std::array<unsigned long, 2> &resolution, const unsigned long max_bounces,
			   const unsigned long &samples) : resolution(resolution), max_bounces(max_bounces) {
	assert(resolution[0] > 0 && resolution[1] > 0);
	assert(samples > 0);
	direction dir = normalise(look_at-position);
	direction left = cross(normalise(up), dir);
	direction new_up = cross(dir, left);
	std::array<std::array<float, 4>, 4> d = {{
													 {left[0], new_up[0], dir[0], position[0]},
													 {left[1], new_up[1], dir[1], position[1]},
													 {left[2], new_up[2], dir[2], position[2]},
													 {0, 0, 0, 1}
											 }};
	mat4 *m = new mat4(d);
	transforms = transform(m);
	data.resize(resolution[0]);
	for (auto &i : data) {
		i.resize(resolution[1]);
		for (auto &j : i)
			j.resize(samples);
	}
}

void camera::set_data(const unsigned long &x, const unsigned long &y, const std::vector<color> data) {
	this->data[x][y] = data;
}

color *camera::get_pixel(const unsigned long &x, const unsigned long &y) const {
	color *out = new color();
	for (auto &i : this->data[x][y])
		*out += i;
	*out = *out*(1/this->data[x][y].capacity());
	return out;
}

const std::array<unsigned long, 2> &camera::get_resolution() const {
	return resolution;
}