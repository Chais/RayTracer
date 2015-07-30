//
// Created by chais on 28.07.15.
//

#include <iostream>
#include "lib/math/vec3.h"
#include "lib/math/mat4.h"

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
}