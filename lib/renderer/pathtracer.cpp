//
// Created by chais on 01/04/16.
//

#include "pathtracer.h"

pathtracer::pathtracer(const std::shared_ptr<color> &background_color, const std::shared_ptr<camera> &cam,
					   const std::shared_ptr<std::vector<std::shared_ptr<light>>> &lights,
					   const std::shared_ptr<std::vector<std::shared_ptr<shape>>> &scene) : renderer(background_color,
																									 cam, lights,
																									 scene) { }

color pathtracer::cast_ray(ray r, int step, bool internal) {
	intersection is = find_nearest(r);
	if (!is.object) // No intersection
		return *background_color;
	color out = color();
	for (std::shared_ptr<light> l : *lights) {
		color lcol = color();
		if (is.object.get() == dynamic_cast<const shape *>(l.get())) {
			out += *is.object->shade(color(), direction(), *is.norm, -r.d, *is.local_pos, internal);
			continue;
		}
		const std::shared_ptr<std::vector<direction>> dirs = l->get_directions(*is.pos, cam->shadow_rays);
		for (direction light_dir : *dirs)
			if (!cast_shadow(*is.pos, -light_dir)) {
				light_dir = normalise(light_dir);
				lcol += *is.object->shade(*l->emit(light_dir), -light_dir, *is.norm, -r.d, *is.local_pos, internal);
			}
		if (dirs->size() > 0)
			out += lcol * (1.0f / dirs->size());
	}
	if (step < cam->max_bounces-1) {
		std::shared_ptr<ray> sctr_ray(new ray(*is.pos, *rnd_in_cone(*is.norm, static_cast<float>(M_PI/2))));
		color sctr_col = *is.object->shade(cast_ray(*sctr_ray, step + 1, internal), sctr_ray->d, *is.norm, -r.d, *is.local_pos, internal);
		out += sctr_col;// * dot(*is.norm, sctr_ray->d);
		std::shared_ptr<ray> refl_ray = internal ? nullptr : is.object->reflect(-r.d, *is.norm, *is.pos);
		if (refl_ray) {
			color refl_col = cast_ray(*refl_ray, step + 1, internal);
			refl_col = refl_col * is.object->get_reflectance();
			out += refl_col;
		}
		std::shared_ptr<ray> refr_ray(is.object->refract(-r.d, internal ? -*is.norm : *is.norm, *is.pos, internal));
		if (refr_ray) {
			color refr_col = color();
			refr_col += cast_ray(*refr_ray, step + 1,
								 dot(refr_ray->d, internal ? -*is.norm : *is.norm) < 0 == !internal);
			refr_col = refr_col * (internal ? std::exp(-(1 - is.object->get_transmittance()) * length(*is.pos - r.o))
											: is.object->get_transmittance());
			out += refr_col;
		}
	}
	return out;
}

std::shared_ptr<direction> pathtracer::rnd_in_cone(const direction &center, const float &angle) const {
	assert(angle <= static_cast<float>(M_PI));
	float x = std::abs(center[0]), y = std::abs(center[1]), z = std::abs(center[2]);
	float min = std::min(x, std::min(y, z));
	direction ax = direction();
	if (min == x)
		ax[0] = 1;
	else if (min == y)
		ax[1] = 1;
	else
		ax[2] = 1;
	direction u = cross(center, ax), v = cross(center, u);
	vec2 s = cam->s->get_2d_samples(0, static_cast<float>(2 * M_PI), std::cos(angle), 1, 1)->at(0);
	s[1] = std::acos(s[1]);
	return std::make_shared<direction>(
			std::sin(s[1]) * (std::cos(s[0]) * u + std::sin(s[0]) * v) + std::cos(s[1]) * center);
}