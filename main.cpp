#include <iostream>
#include "whitted_rt.h"
#include <png++/png.hpp>

using namespace std;

int main() {
	camera cam = camera();
	vec3 bgcolor = vec3();
	whitted_rt rt = whitted_rt(bgcolor, cam);
	rt.render();
	png::image<png::rgb_pixel> img(1024, 768);
	png::rgb_pixel *pPtr;
	vector<ray>::iterator rIt = cam.begin();
	for (int y = 0; y < 768; y++) {
		pPtr = &img[y][0];
		for (int x = 0; x < 1024; x++) {
			vec3 tmp = to_color(rIt->getColor());
			(*pPtr).red = int(tmp[0]);
			(*pPtr).green = int(tmp[1]);
			(*pPtr).blue = int(tmp[2]);
			pPtr++;
			rIt++;
		}
	}
	img.write("test.png");
}