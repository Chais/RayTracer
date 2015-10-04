#include "lib/whitted_rt.h"
#include "lib/parser.h"
#include <png++/png.hpp>

using namespace std;

int main(int argc, char *argv[]) {
	if (argc == 1) {
		cout << "Usage: " << argv[0] << " <input>" << endl
			<< "        <input> - Path of the XML file specifying the camera, lights and geometry." << endl;
		return 0;
	}
	std::string out_file;
	shared_ptr<whitted_rt> rt = parser::parse(argv[1], out_file);
	rt->render();
	std::array<unsigned long, 2> res = rt->get_resolution();
	png::image<png::rgb_pixel> img(res[0], res[1]);
	png::rgb_pixel *pPtr;
	for (unsigned long y = 0; y < res[1]; y++) {
		pPtr = &img[y][0];
		for (unsigned long x = 0; x < res[0]; x++) {
			shared_ptr<color> pix = rt->get_pixel(x, y);
			std::array<int, 3> tmp = rgb(*pix);
			(*pPtr).red = tmp[0];
			(*pPtr).green = tmp[1];
			(*pPtr).blue = tmp[2];
			pPtr++;
		}
	}
	img.write(out_file);
	return 0;
}