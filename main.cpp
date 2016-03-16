#include "lib/whitted_rt.h"
#include "lib/parser.h"
#include <CImg.h>

using namespace std;

int main(int argc, char *argv[]) {
	if (argc == 1) {
		cout << "Usage: " << argv[0] << " <input>" << endl
			<< "        <input> - Path of the XML file specifying the camera, lights and geometry." << endl;
		return 0;
	}
	string out_file;
	shared_ptr<whitted_rt> rt = parser::parse(argv[1], out_file);
	rt->render();
	array<unsigned long, 2> res = rt->get_resolution();
	cimg_library::CImg<unsigned char> img(res[0], res[1], 1, 3);
	cimg_forXY(img, x, y) {
		array<unsigned char, 3> p = rgb(*rt->get_pixel(x, y));
		img(x, y, 0) = p[0];
		img(x, y, 1) = p[1];
		img(x, y, 2) = p[2];
	}
	img.save_png(out_file.c_str());
	return 0;
}