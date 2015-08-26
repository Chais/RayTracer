#include "perspective_camera.h"
#include "../math/mat4.h"

perspective_camera::perspective_camera() {
	std::array<std::array<float, 4>, 4> d = {{
													 {-1, 0, 0, 0},
													 {0, 1, 0, 0},
													 {0, 0, -1, 0},
													 {0, 0, 0, 1}
											 }};
	mat4 m = mat4(d);
	transforms = transform(mat4(m), mat4(m));
	resolution = {1024, 768};
	data.reserve(1024*768);
	fov = 75;
}

perspective_camera::perspective_camera(const point &position, const point &look_at, const direction &up,
									   const float fov, const unsigned long resolution[2]) : resolution(resolution),
																							 fov(fov) {
	direction dir = normalise(look_at-position);
	direction left = normalise(cross(normalise(up), dir));
	direction new_up = cross(dir, left);
	std::array<std::array<float, 4>, 4> d = {{
													 {left[0], new_up[0], dir[0], position[0]},
													 {left[1], new_up[1], dir[1], position[1]},
													 {left[2], new_up[2], dir[2], position[2]},
													 {0, 0, 0, 1}
											 }};
	mat4 m = mat4(d);
	transforms = transform(m, invert(m));
	data.reserve(resolution[0]*resolution[1]);
}

std::ostream &operator<<(std::ostream &out, const perspective_camera &cam) {
	return out;
}

double perspective_camera::getFov() const {
	return 0;
}
