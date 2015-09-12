//
// Created by chais on 08.07.15.
//

#include "whitted_rt.h"

whitted_rt::whitted_rt(const color &background_color, camera *cam, const std::vector<light *> &lights,
					   const std::vector<shape *> &scene, const unsigned long &max_bounces) : background_color(
		background_color), cam(cam), lights(lights), scene(scene), max_bounces(max_bounces) { }

color whitted_rt::cast_ray(ray r, int step, bool internal) {
	intersection is = this->find_nearest(r);
	if (is.object == nullptr) // No intersection
		return this->background_color;
	color out = color();
	for (light *l : lights) {
		direction light_dir = l->get_direction(*is.pos);
		if (!this->cast_shadow(ray (*is.pos, -light_dir)))
			out += is.object->shade(l->emit(light_dir), -light_dir, *is.norm, -r.d, *is.local_pos, internal);
	}
	return out;
	/*try {
		intersection is = this->find_nearest(r);
		vec3 *base_color = normal.getColor();
		vec3 *reflect_color = new vec3();
		vec3 *refract_color = new vec3();
		material *matrl = object->getMaterial();
		phong_material phng = matrl->getPhong_params();
		double ref = matrl->getReflectance();
		double t = matrl->getTransmittance();
		double iof = matrl->getRefraction();
		vec3 view_dir = -r.getDirection();
		vec3 *ac = new vec3();
		vec3 *dc = new vec3();
		vec3 *sc = new vec3();
		for (light *light : lights) {
			if (parallel_light*l = dynamic_cast<parallel_light *>(light)) {
				if (!internal) {
					vec3 light_dir = -l->getDirection();
					if (this->cast_shadow(normal.getOrigin()))
						continue;
					double phi = std::max(0.0, dot(normal.getDirection(), light_dir));
					if (phi > 0) {
						*dc += l->emit(<#initializer#>)*(phng.diffuse*phi);
						vec3 reflect_dir = normal.getDirection()*(2*phi)-light_dir;
						*sc += l->emit(<#initializer#>)*
							   (std::pow(std::max(0.0, dot(view_dir, reflect_dir)), phng.exponent)*phng.specular);
					}
				}
			} else {
				*ac += light->emit(<#initializer#>)*phng.ambient;
			}
		}
		vec3 *light_weight = new vec3(*ac+*dc);
		double lw[] = {(*light_weight)[0], (*light_weight)[1], (*light_weight)[2]};
		delete light_weight;
		*base_color = (scale(*base_color, lw)+*sc)*(1-ref-t);
		/* Reflect
		if (ref > 0) {
			double phi = std::max(0.0, dot(normal.getDirection(), view_dir));
			vec3 reflect_dir = normal.getDirection()*(2*phi)-view_dir;
			*reflect_color = cast_ray(ray(normal.getOrigin(), reflect_dir), step+1, internal)*ref;
		}
		// Refract
		if (t > 0) {
			vec3 n = internal ? -normal.getDirection() : normal.getDirection();
			double cosi = std::max(0.0, dot(n, view_dir));
			double eta = internal ? iof : 1/iof;
			double sint2 = std::pow(eta, 2)*(1-std::pow(cosi, 2));
			if (sint2 <= 1) {
				vec3 refract_dir = r.getDirection()*eta+n*(eta*cosi-std::sqrt(1-sint2));
				*refract_color = cast_ray(ray(normal.getOrigin(), refract_dir), step+1, !internal)*t;
			} else {
				vec3 reflect_dir = n*(2*cosi)-view_dir;
				*refract_color = cast_ray(ray(normal.getOrigin(), reflect_dir), step+1, internal)*t;
			}
		}
		return *base_color+*reflect_color+*refract_color;
	}*/
}

void whitted_rt::render() {
	const std::array<unsigned long, 2> resolution = this->cam->get_resolution();
	for (unsigned long y = 0; y < resolution[1]; y++)
		for (unsigned long x = 0; x < resolution[0]; x++) {
			std::vector<ray> *rays = this->cam->get_rays(x, y);
			std::vector<color> data;
			data.reserve(rays->size());
			for (auto &r : *rays)
				data.push_back(cast_ray(r, 0, false));
			this->cam->set_data(x, y, data);
		}
}

bool whitted_rt::cast_shadow(const ray &r) {
	for (shape *obstacle : this->scene)
		if (obstacle->intersect_shadow(r))
			return true;
	return false;
}

intersection whitted_rt::find_nearest(ray r) {
	intersection out = intersection();
	float dist = std::numeric_limits<float>::max();
	for (shape *object : scene) {
		intersection cur = object->intersect_full(r);
		if (cur.object == nullptr)
			continue;
		float new_dist = length(r.o-*cur.pos);
		if (new_dist < dist) {
			dist = new_dist;
			out = cur;
		}
	}
	return out;
}
