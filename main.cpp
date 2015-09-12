#include <iostream>
#include "lib/whitted_rt.h"
#include "lib/geometry/sphere.h"
#include "lib/geometry/material/solid_material.h"
#include "lib/light/parallel_light.h"
#include "lib/camera/perspective_camera.h"
#include "lib/geometry/material/phong_material.h"
#include "lib/light/ambient_light.h"
#include <png++/png.hpp>

using namespace std;

int main() {
	camera *cam = new perspective_camera();
	color bgcolor = color();
	std::vector<light *> lights;
	lights.push_back(new ambient_light(color{1, 1, 1}));
	lights.push_back(new parallel_light(color{1, 1, 1}, direction{0, -1, 0}));
	phong_material *red_lack = new phong_material(color{1, 0, 0}, 0.1, 0.6, 0.7, 200);
	std::vector<shape*> scene;
	scene.push_back(new sphere(1.0, red_lack));
	std::array<float, 3> sf = {2, 1, 1};
	scene[0]->scale(sf);
	scene[0]->rotateZ(30);
	scene[0]->translate(direction{0, -1, -7});
	scene.push_back(new sphere(1.0, red_lack));
	sf[0] = 100;
	sf[1] = 0.1;
	sf[2] = 100;
	scene[1]->scale(sf);
	scene[1]->translate(direction{0, -4, -1});
	whitted_rt rt = whitted_rt(bgcolor, cam, lights, scene, 10);
	rt.render();
	png::image<png::rgb_pixel> img(1024, 768);
	png::rgb_pixel *pPtr;
	for (unsigned long y = 0; y < 768; y++) {
		pPtr = &img[y][0];
		for (unsigned long x = 0; x < 1024; x++) {
			std::array<int, 3> tmp = rgb(*cam->get_pixel(x, y));
			(*pPtr).red = tmp[0];
			(*pPtr).green = tmp[1];
			(*pPtr).blue = tmp[2];
			pPtr++;
		}
	}
	img.write("test.png");
}