#include <iostream>
#include "lib/whitted_rt.h"
#include "lib/geometry/sphere.h"
#include "lib/geometry/material/solid_material.h"
#include "lib/light/parallel_light.h"
#include <png++/png.hpp>

using namespace std;

int main() {
	camera cam = camera();
	vec3 bgcolor = vec3();
	std::vector<ambient_light*> lights;
	lights.push_back(new ambient_light(vec3{1, 1, 1}));
	lights.push_back(new parallel_light(vec3{1, 1, 1}, normalise(vec3{0, -1, 0})));
	phong lack = phong(0.1, 0.6, 0.7, 200);
	solid_material *red_lack = new solid_material(vec3{1, 0, 0}, lack, 0, 0, 0);
	std::vector<shape*> scene;
	scene.push_back(new sphere(1.0, red_lack));
	scene[0]->translate(vec3{0, 1, -5});
	double sf[] = {2, 1, 1};
	scene[0]->scale(sf);
	scene[0]->rotateZ(20);
	whitted_rt rt = whitted_rt(bgcolor, cam, lights, scene);
	rt.render();
	png::image<png::rgb_pixel> img(1024, 768);
	png::rgb_pixel *pPtr;
	vector<ray>::iterator rIt = cam.begin();
	for (int y = 0; y < 768; y++) {
		pPtr = &img[y][0];
		for (int x = 0; x < 1024; x++) {
			vec3 tmp = to_color(*rIt->getColor());
			(*pPtr).red = int(tmp[0]);
			(*pPtr).green = int(tmp[1]);
			(*pPtr).blue = int(tmp[2]);
			pPtr++;
			rIt++;
		}
	}
	img.write("test.png");
}