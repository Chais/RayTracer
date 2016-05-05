//
// Created by chais on 27/04/16.
//

#include "vpl.h"

vpl::vpl(const std::shared_ptr<color> &background_color, const std::shared_ptr<camera> &cam,
		 const std::shared_ptr<std::vector<std::shared_ptr<light>>> &lights,
		 const std::shared_ptr<std::vector<std::shared_ptr<shape>>> &scene) : renderer(background_color, cam, lights,
																					   scene) { }

color vpl::cast_ray(ray r, int step, bool internal) {
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
	out = out * (1.0f / lights->size());
	return out;
}

void vpl::spread_light() {
	unsigned long samples = 100;
	if (samples == 0)
		return;
	random_sampler s;
	float completed = 0;
	float perlight = 100.0f / lights->size();
	std::cout << "Shedding light..." << std::endl;
	std::cout << '\r' << std::setw(6) << std::fixed << std::setprecision(2) << completed << " %";
	std::cout.flush();
	std::vector<std::shared_ptr<hemisphere_light>> list = std::vector<std::shared_ptr<hemisphere_light>>();
	for (std::shared_ptr<light> l : *lights) {
		const std::shared_ptr<std::vector<ray>> rays = l->shed(samples);
		for (unsigned long i = 0; i < samples; i++) {
			intersection step = find_nearest(rays->at(i));
			if (!step.object)
				continue;
			color lcol = *l->emit(normalise(*step.pos - rays->at(i).o));
			while (true) {
				ray next = ray(*step.pos,
							   s.get_solid_angle_samples(*step.norm, static_cast<float>(M_PI / 2), 1)->at(0));
				std::vector<direction> dir = *l->get_directions(*step.pos, 1);
				color dc = color();
				if (dir.size() > 0) {
					direction d = normalise(dir.at(0));
					dc = *step.object->shade(*l->emit(d), -d, *step.norm, next.d, *step.local_pos, false);
				}
				color c = *step.object->shade(lcol, -rays->at(i).d, *step.norm, next.d, *step.local_pos, false);
				if (c[0] < 4e-3 && c[1] < 4e-3 && c[2] < 4e-3)
					break;
				list.push_back(std::shared_ptr<hemisphere_light>(
						new hemisphere_light(std::make_shared<color>(c + dc), *step.norm, direction())));
				std::dynamic_pointer_cast<point>(list.back())->translate(*step.pos);
				step = find_nearest(next);
				if (!step.object)
					break;
				lcol = *list.back()->emit(normalise(*step.pos - next.o));
			}
		}
		std::cout << '\r' << std::setw(6) << std::fixed << std::setprecision(2) << (completed += perlight) << " %";
		std::cout.flush();
	}
	std::cout << std::endl << "Created " << list.size() << " VPLs" << std::endl;
	lights->insert(lights->end(), list.begin(), list.end());
	//scene->insert(scene->end(), list.begin(), list.end());
}

void vpl::render() {
	spread_light();
	renderer::render();
}