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
	if (step < cam->max_bounces - 1) {
		std::shared_ptr<ray> sctr_ray(
				new ray(*is.pos, cam->s->get_solid_angle_samples(*is.norm, static_cast<float>(M_PI / 2), 1)->at(0)));
		color sctr_col = *is.object->shade(cast_ray(*sctr_ray, step + 1, internal), sctr_ray->d, *is.norm, -r.d,
										   *is.local_pos, internal);
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