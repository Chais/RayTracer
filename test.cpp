//
// Created by chais on 28.07.15.
//

#include <iostream>
#include <typeinfo>
#include <array>
#include "lib/math/mat4.h"
#include "perspective_camera.h"
#include "light.h"
#include "lib/light/parallel_light.h"
#include "lib/geometry/sphere.h"
#include "lib/geometry/material/solid_material.h"

using namespace std;

int main(int argc, char *argv[]) {
	array<array<float, 4>, 4> mat = {{{1, 0, 1, 1},
									  {0, 1, 0, 1},
									  {0, 0, 1, 0},
									  {0, 0, 0, 1}}};
	mat4 m{mat};
	cout << "mat4 tests:" << endl;
	cout << "m=" << m << endl;
	cout << "invert(m)=" << invert(m) << endl;
	array<array<float, 4>, 4> mata = {{{2, 5, 4, 6},
									   {7, 10, 2, 6},
									   {7, 5, 3, 2},
									   {7, 4, 1, 5}}};
	array<array<float, 4>, 4> matb = {{{5, 9, 3, 7},
									   {4, 3, 9, 2},
									   {3, 1, 8, 2},
									   {10, 2, 10, 9}}};
	mat4 ma{mata};
	mat4 mb{matb};
	cout << "ma=" << ma << endl;
	cout << "mb=" << mb << endl;
	cout << "ma*mb=" << ma*mb << endl;
	cout << "Camera tests:" << endl;
	perspective_camera cam = perspective_camera();
	auto start = cam.begin();
	auto stop = cam.end();
	cout << "start==stop: " << (start == stop) << endl;
	light *l1 = new light(vec3{1, 1, 1});
	light *l2 = new parallel_light(vec3{1, 1, 1}, vec3{0, -1, 0});
	cout << "typeid(*l1) == typeid(*l2): " << (typeid(*l1) == typeid(*l2)) << endl;
	cout << "typeid(*l2)== typeid(parallel_light): " << (typeid(*l2) == typeid(parallel_light)) << endl;
	cout << dynamic_cast<parallel_light *>(l2) << endl;
	phong_material lack = phong_material(0.1, 0.6, 0.7, 200);
	solid_material *red_lack = new solid_material(vec3{1, 0, 0}, lack, 0, 0, 0);
	sphere sphere1 = sphere(1.0, red_lack);
	cout << "Transforms: " << sphere1.getTransforms() << endl;
	cout << "Inv. Transforms: " << sphere1.getInvTransforms() << endl;
	cout << "Translate" << endl;
	sphere1.translate(vec3{0, 1, -5});
	cout << "Transforms: " << sphere1.getTransforms() << endl;
	cout << "Inv. Transforms: " << sphere1.getInvTransforms() << endl;
	cout << "Rotate" << endl;
	sphere1.rotateZ(90);
	cout << "Transforms: " << sphere1.getTransforms() << endl;
	cout << "Inv. Transforms: " << sphere1.getInvTransforms() << endl;
	/*cout << "Scale" << endl;
	sf[0] = 2;
	sf[1] = 1;
	sphere1.scale(sf);
	cout << "Transforms: " << sphere1.getTransforms() << endl;
	cout << "Inv. Transforms: " << sphere1.getInvTransforms() << endl;*/
	cout << "M*[0 0 0]'=" << sphere1.getInvTransforms()*vec3{0, 0, 0} << endl;
	cout << "M*[0 -0.2 -1]'=" << transform(sphere1.getInvTransforms(), normalise(vec3{0, -0.2, -1})) << endl;
}