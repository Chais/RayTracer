//
// Created by chais on 28.07.15.
//

#include <iostream>
#include "lib/sampler/random_sampler.h"

using namespace std;

int main(int argc, char *argv[]) {
	cout << "1D float" << endl;
	for (unsigned long i = 0; i < 300000; i++) {
		random_sampler s;
		cout << s.get_1d_samples(0.0f, 1.0f, 1)->at(0) << ' ';
	}
	cout << endl << "1D long" << endl;
	for (unsigned long i = 0; i < 300000; i++) {
		random_sampler s;
		cout << s.get_1d_samples(0l, 1000l, 1)->at(0) << ' ';
	}
	cout << endl << "2D float" << endl;
	for (unsigned long i = 0; i < 300000; i++) {
		random_sampler s;
		vec2 v = s.get_2d_samples(0, 1, 0, 1, 1)->at(0);
		cout << v[0] << ' ' << v[1] << ';';
	}
	cout << endl;
}