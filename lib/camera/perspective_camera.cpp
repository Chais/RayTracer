#include "perspective_camera.h"

perspective_camera::perspective_camera() : perspective_camera(point(0, 0, 0), point(0, 0, -1), direction(0, 1, 0),
															  {1024, 768}, 1, 45) {
}

perspective_camera::perspective_camera(const point &position, const point &look_at, const direction &up,
									   const std::array<unsigned long, 2> &resolution, const unsigned long &samples,
									   const float &fov) :
		camera(position, look_at, up, resolution, samples), fov(fov) {
	assert(0 < fov && fov < 90);
	stepwidth = tan(helper::to_radians(this->fov))/(resolution[0]/2);
	start = direction(0, 0, 1)+direction(1, 0, 0)*(((resolution[0]-1)/2.0)*stepwidth)+
			direction(0, 1, 0)*(((resolution[1]-1)/2.0)*stepwidth);
}

std::vector<ray> *perspective_camera::get_rays(const unsigned long &x, const unsigned long &y) {
	// TODO extend to support multisampling
	std::vector<ray> *out = new std::vector<ray>();
	out->push_back(this->transforms(
			ray(point(), this->start+direction(-1, 0, 0)*(this->stepwidth*x)+direction(0, -1, 0)*(this->stepwidth*y))));
	return out;
}