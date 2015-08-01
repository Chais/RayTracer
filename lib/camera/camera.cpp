#include "camera.h"

camera::camera() : position(vec3()), direction(vec3(0, 0, -1)), down(vec3(0, 1, 0)), right(vec3(1, 0, 0)),
				   fov(45),
				   maxbounces(100) {
	int resolution[] = {1024, 768};
	rays.reserve(static_cast<unsigned long>(resolution[0]*resolution[1]));
	double stepwidth = tan((this->fov*M_PI)/180)/(resolution[0]/2);
	vec3 start = direction-this->right*((resolution[0]-1)/2.0)*stepwidth-
				 this->down*((resolution[1]-1)/2.0)*stepwidth;
	for (int i = 0; i < resolution[1]; i++)
		for (int j = 0; j < resolution[0]; j++)
			rays.push_back(ray(this->position, start+this->down*(stepwidth*i)+this->right*(stepwidth*j)));
}

camera::camera(const vec3 &position, const vec3 &direction, const vec3 &down, const vec3 &right, const double fov,
			   const int *resolution, const int maxbounces) : position(position), direction(direction), down(down),
															  right(right) {
	if (fov > 0 && fov < 90)
		this->fov = fov;
	else throw new camera_exception("FOV has to be greater than 0 and less than 90.");
	if (resolution[0] > 0 && resolution[1] > 0) {
	} else throw new camera_exception("The resolution vector must consist of two greater than zero values.");
	if (maxbounces > 0)
		this->maxbounces = maxbounces;
	else throw new camera_exception("maxBounces has to be greater than zero.");
	rays.reserve(static_cast<unsigned long>(resolution[0]*resolution[1]));
	double stepwidth = tan((this->fov*M_PI)/180)/(resolution[0]/2);
	vec3 start = this->direction-this->right*((resolution[0]-1)/2.0)*stepwidth-
				 this->down*((resolution[1]-1)/2.0)*stepwidth;
	for (int i = 0; i < resolution[1]; i++)
		for (int j = 0; j < resolution[0]; j++)
			rays[i*resolution[0]+j] = ray(this->position,
												start+this->down*(stepwidth*i)+this->right*(stepwidth*j));
}

ray &camera::operator[](const int i) {
	return this->rays[i];
}

std::ostream &operator<<(std::ostream &out, camera &cam) {
	out << "position: " << cam.position << std::endl
	<< "direction: " << cam.direction << std::endl
	<< "down: " << cam.down << std::endl
	<< "fov: " << cam.fov << std::endl
	<< "maxbounces: " << cam.maxbounces << std::endl;
	return out;
}

const vec3 &camera::getPosition() const {
	return this->position;
}

const vec3 &camera::getDirection() const {
	return this->direction;
}

const vec3 &camera::getDown() const {
	return this->down;
}

const vec3 &camera::getRight() const {
	return this->right;
}

double camera::getFov() const {
	return this->fov;
}

int camera::getMaxbounces() const {
	return this->maxbounces;
}

std::vector<ray>::iterator camera::begin() {
	return this->rays.begin();
}

std::vector<ray>::iterator camera::end() {
	return this->rays.end();
}