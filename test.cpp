//
// Created by chais on 28.07.15.
//

#include <iostream>
#include <typeinfo>
#include "lib/math/vec3.h"
#include "lib/math/mat4.h"
#include "lib/camera/camera.h"
#include "lib/light/ambient_light.h"
#include "lib/light/parallel_light.h"
#include "lib/geometry/sphere.h"
#include "lib/geometry/material/solid_material.h"

using namespace std;

int main(int argc, char *argv[]) {
	const vec3 a = vec3(1, 2, 4);
	const vec3 b{2, 4, 8};
	vec3 c = vec3();
	cout << "vec3 tests:" << endl;
	cout << "a=" << a << endl;
	cout << "b=" << b << endl;
	cout << "c=" << c << endl;
	cout << "a+b=" << a+b << endl;
	cout << "b-a=" << b-a << endl;
	cout << "a*2=" << a*2 << endl;
	cout << "2*a=" << 2*a << endl;
	c += a;
	cout << "c+=a" << c << endl;
	c -= b;
	cout << "c-=b" << c << endl;
	cout << "-b=" << -b << endl;
	cout << "cross(a, b)=" << cross(a, b) << endl;
	cout << "dot(a, b)=" << dot(a, b) << endl;
	double sf[] = {4, 2, 1};
	cout << "scale(a, double{4, 2, 1})=" << scale(a, sf) << endl;
	cout << "length(a)=" << length(a) << endl;
	cout << "normalise(b)=" << normalise(b) << endl;
	double mat[] = {1, 0, 1, 1,
					0, 1, 0, 1,
					0, 0, 1, 0,
					0, 0, 0, 1};
	mat4 m{mat};
	cout << "mat4 tests:" << endl;
	cout << "m=" << m << endl;
	cout << "invert(m)=" << invert(m) << endl;
	double mata[] = {2, 5, 4, 6,
					 7, 10, 2, 6,
					 7, 5, 3, 2,
					 7, 4, 1, 5};
	double matb[] = {5, 9, 3, 7,
					 4, 3, 9, 2,
					 3, 1, 8, 2,
					 10, 2, 10, 9};
	mat4 ma{mata};
	mat4 mb{matb};
	cout << "ma=" << ma << endl;
	cout << "mb=" << mb << endl;
	cout << "ma*mb=" << ma*mb << endl;
	cout << "Camera tests:" << endl;
	camera cam = camera();
	auto start = cam.begin();
	auto stop = cam.end();
	cout << "start==stop: " << (start == stop) << endl;
	ambient_light *l1 = new ambient_light(vec3{1, 1, 1});
	ambient_light *l2 = new parallel_light(vec3{1, 1, 1}, vec3{0, -1, 0});
	cout << "typeid(*l1) == typeid(*l2): " << (typeid(*l1) == typeid(*l2)) << endl;
	cout << "typeid(*l2)== typeid(parallel_light): " << (typeid(*l2) == typeid(parallel_light)) << endl;
	cout << dynamic_cast<parallel_light *>(l2) << endl;
	phong lack = phong(0.1, 0.6, 0.7, 200);
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