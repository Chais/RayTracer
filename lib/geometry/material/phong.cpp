//
// Created by chais on 06.08.15.
//

#include "phong.h"

phong::phong(double ambient, double diffuse, double specular, int exponent) : ambient(ambient), diffuse(diffuse),
																			  specular(specular), exponent(exponent) {
	if (ambient < 0 || diffuse < 0 || specular < 0 || exponent < 0)
		throw material_exception("Phong parameters have to be four non-negative values.");
}

std::ostream &operator<<(std::ostream &out, const phong &a) {
	out << "Phong parameters: Ambient: " << a.ambient << ", Diffuse: " << a.diffuse << ", Specular: " <<
	a.specular << ", Exponent: " << a.exponent;
	return out;
}
