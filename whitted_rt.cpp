//
// Created by chais on 08.07.15.
//

#include "whitted_rt.h"

whitted_rt::whitted_rt(const vec3 &backgroundColor, camera &cam) : backgroundColor(backgroundColor), cam(cam) { }

vec3 whitted_rt::cast_ray(ray r) {
	return r.getDirection();
}

void whitted_rt::render() {
	for (ray &r : cam)
		r.setColor(r.getDirection());
}
