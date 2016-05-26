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
	//random_sampler s;
	//std::shared_ptr<light> l = lights->at(s.get_1d_samples(0, lights->size() - 1, 1)->at(0));
	for (std::shared_ptr<light> l : *lights) {
		color lcol = color();
		if (is.object.get() == dynamic_cast<const shape *>(l.get()))
			out += *is.object->shade(color(), direction(), *is.norm, -r.d, *is.local_pos, internal);
		else {
			const std::shared_ptr<std::vector<intersection>> dirs = l->get_directions(*is.pos, cam->shadow_rays);
			for (intersection d : *dirs) {
				direction light_dir = (*is.pos - *d.pos) * 0.999;
				if (!cast_shadow(*is.pos, -light_dir)) {
					//light_dir = normalise(light_dir);
					lcol += *is.object->shade(*l->emit(light_dir, d), -normalise(light_dir), *is.norm, -r.d,
											  *is.local_pos,
											  internal);
				}
			}
			if (dirs->size() > 0)
				out += lcol * (1.0f / dirs->size());
		}
	}
	//l = vpls->at(s.get_1d_samples(0, vpls->size() - 1, 1)->at(0));
	color dc = color();
	for (std::shared_ptr<hemisphere_light> l : *vpls) {
		color lcol = color();
		const std::shared_ptr<std::vector<intersection>> dirs = l->get_directions(*is.pos, cam->shadow_rays);
		for (intersection d : *dirs) {
			direction light_dir = (*is.pos - *d.pos) * 0.999;
			if (!cast_shadow(*is.pos, -light_dir)) {
				light_dir = normalise(light_dir);
				lcol += *is.object->shade(*l->emit(light_dir, d), -light_dir, *is.norm, -r.d, *is.local_pos, internal);
			}
		}
		if (dirs->size() > 0)
			dc += lcol * (1.0f / dirs->size());
	}
	return out * (1.0f / lights->size()) + dc * (1.0f / vpls->size());
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
		for (unsigned long i = 0; i < rays->size(); i++) {
			intersection step = find_nearest(rays->at(i));
			intersection init = std::dynamic_pointer_cast<shape>(l)->intersect_full(
					ray(rays->at(i).o + rays->at(i).d, -rays->at(i).d));
			if (!step.object)
				continue;
			if (!init.object) {
				init.object = std::dynamic_pointer_cast<shape>(l);
				init.pos = std::make_shared<position>(rays->at(i).o);
				//init.local_pos = std::shared_ptr<vec2>(new vec2());
				//init.norm = std::shared_ptr<normal>(new normal());
			}
			direction d = *step.pos - rays->at(i).o;
			std::shared_ptr<ray> next = step.object->scatter(-normalise(d), *step.norm, *step.pos);
			//ray next = ray(*step.pos, s.get_solid_angle_samples(*step.norm, static_cast<float>(M_PI / 2), 1)->at(0));
			color lcol = *step.object->shade(*l->emit(d, init), -normalise(d), *step.norm, next->d, *step.local_pos,
											 false);
			list.push_back(std::shared_ptr<hemisphere_light>(
					new hemisphere_light(std::make_shared<color>(lcol), *step.norm, direction())));
			for (unsigned long j = 0; j < cam->max_bounces - 1; j++) {
				direction ddir = next->d;
				step = find_nearest(*next);
				if (!step.object)
					break;
				next = step.object->scatter(-ddir, *step.norm, *step.pos);
				if (!next)
					break;
				//next = ray(*step.pos, s.get_solid_angle_samples(*step.norm, static_cast<float>(M_PI / 2), 1)->at(0));
				std::vector<intersection> dir = *l->get_directions(*step.pos, 1);
				color dc = color();
				if (dir.size() > 0) {
					d = *step.pos - *dir.at(0).pos;
					dc = *step.object->shade(*l->emit(d, dir.at(0)), -normalise(d), *step.norm, next->d,
											 *step.local_pos, false);
				}
				lcol = *step.object->shade(lcol, -ddir, *step.norm, next->d, *step.local_pos, false) *
					   static_cast<float>(2 * M_PI) + dc;
				if (lcol[0] < 4e-3 && lcol[1] < 4e-3 && lcol[2] < 4e-3)
					break;
				list.push_back(std::shared_ptr<hemisphere_light>(
						new hemisphere_light(std::make_shared<color>(lcol), *step.norm, direction())));
				std::dynamic_pointer_cast<point>(list.back())->translate(*step.pos);
			}
		}
		std::cout << '\r' << std::setw(6) << std::fixed << std::setprecision(2) << (completed += perlight) << " %";
		std::cout.flush();
	}
	std::cout << std::endl << "Created " << list.size() << " VPLs" << std::endl;
	vpls->insert(vpls->end(), list.begin(), list.end());
	//scene->insert(scene->end(), list.begin(), list.end());
}

void vpl::render() {
	spread_light();
	renderer::render();
}