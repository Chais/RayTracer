//
// Created by chais on 08.07.15.
//

#include "whitted_rt.h"

whitted_rt::whitted_rt(const color *background_color, camera *cam, std::vector<light *> *lights,
					   std::vector<shape *> *scene) : background_color(
	background_color), cam(cam), lights(lights), scene(scene) { }

color whitted_rt::cast_ray(ray r, int step, bool internal) {
	intersection is = this->find_nearest(r);
	if (is.object == nullptr) // No intersection
		return *this->background_color;
	color out = color();
	for (light *l : *lights) {
		direction *light_dir = l->get_direction(*is.pos);
		if (!this->cast_shadow(*is.pos, -*light_dir)) {
			*light_dir = normalise(*light_dir);
			out += is.object->shade(*l->emit(*light_dir), -*light_dir, *is.norm, -r.d, *is.local_pos, internal);
		}
		delete light_dir;
	}
	if (step < this->cam->get_max_bounces()) {
		std::vector<ray> *refl_ray = internal ? nullptr : is.object->reflect(-r.d, *is.norm, *is.pos, 1);
		if (refl_ray != nullptr) {
			color refl_col = color();
			for (ray &rr : *refl_ray) {
				refl_col += this->cast_ray(rr, step + 1, internal);
			}
			refl_col = (refl_col*(1/refl_ray->size()))*is.object->get_reflectance();
			out += refl_col;
		}
		std::vector<ray> *refr_ray = is.object->refract(-r.d, internal ? -*is.norm : *is.norm, *is.pos, 1, internal);
		if (refr_ray != nullptr) {
			color refr_col = color();
			for (ray &rr : *refr_ray) {
				refr_col += this->cast_ray(rr, step + 1, dot(rr.d, internal ? -*is.norm : *is.norm) < 0 == !internal);
			}
			refr_col = (refr_col*(1/refr_ray->size()))*is.object->get_transmittance();
			out += refr_col;
		}
	}
	return out;
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

bool whitted_rt::cast_shadow(const point &o, const direction &d) {
	for (shape *obstacle : *this->scene)
		if (obstacle->intersect_shadow(o, d))
			return true;
	return false;
}

intersection whitted_rt::find_nearest(ray r) {
	intersection out = intersection();
	float dist = std::numeric_limits<float>::max();
	for (shape *object : *this->scene) {
		intersection cur = object->intersect_full(r);
		if (cur.object == nullptr)
			continue;
		float new_dist = length(r.o - *cur.pos);
		if (new_dist < dist) {
			dist = new_dist;
			out = cur;
		}
	}
	return out;
}

color *whitted_rt::get_pixel(const unsigned long &x, const unsigned long &y) const {
	return this->cam->get_pixel(x, y);
}

const std::array<unsigned long, 2> &whitted_rt::get_resolution() const {
	return this->cam->get_resolution();
}
