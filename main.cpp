#include "lib/renderer/whitted_rt.h"
#include "lib/parser.h"

int main(int argc, char *argv[]) {
	if (argc == 1) {
		std::cout << "Usage: " << argv[0] << " <input>" << std::endl
		<< "        <input> - Path of the XML file specifying the camera, lights and geometry." << std::endl;
		return 0;
	}
	std::string out_file;
	std::shared_ptr<renderer> rt = parser::parse(argv[1], out_file);
	rt->render();
	std::array<unsigned long, 2> res = rt->get_resolution();
	cimg_library::CImg<unsigned char> img(res[0], res[1], 1, 3);
	cimg_forXY(img, x, y) {
			std::array<unsigned char, 3> p = rgb(*rt->get_pixel(x, y));
			img(x, y, 0) = p[0];
			img(x, y, 1) = p[1];
			img(x, y, 2) = p[2];
		}
	img.save_png(out_file.c_str());
	return 0;
}