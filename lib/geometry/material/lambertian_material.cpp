//
// Created by chais on 26.08.15.
//

#include "lambertian_material.h"

lambertian_material::lambertian_material(color col, float ambient, float diffuse) : col(col), ambient(ambient),
																					diffuse(diffuse) { }

std::ostream &operator<<(std::ostream &out, const lambertian_material &a) {
	out << "Phong material: Color: " << a.col << " Ambient intensity: " << a.ambient << ", Diffuse intensity: " <<
	a.diffuse;
	return out;
}

color lambertian_material::shade(const color &lcol, const direction &l, const normal &n, const direction &v, const vec2 &pos,
								 const bool internal) {
	return color();
}
