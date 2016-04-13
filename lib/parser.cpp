//
// Created by chais on 15.09.15.
//

#include "parser.h"

std::shared_ptr<renderer> parser::parse(const char *in_path, std::string &out_path) {
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(in_path, pugi::parse_default | pugi::parse_doctype);
	assert(result);
	pugi::xml_node scene = doc.child("scene");
	out_path = scene.attribute("output_file").value();
	if (std::string(scene.attribute("renderer").value()) == "raytracer")
		return parse_whitted_rt(scene);
	if (std::string(scene.attribute("renderer").value()) == "pathtracer")
		return parse_pathtracer(scene);
	return std::shared_ptr<renderer>();
}

std::shared_ptr<whitted_rt> parser::parse_whitted_rt(const pugi::xml_node &scene) {
	const std::shared_ptr<color> background_color = parse_color(scene.child("background_color"));
	std::shared_ptr<camera> cam = parse_camera(scene.child("camera"));
	std::shared_ptr<std::vector<std::shared_ptr<light>>> lights = parse_lights(scene.child("lights"));
	std::shared_ptr<std::vector<std::shared_ptr<shape>>> geometry = parse_surfaces(scene.child("surfaces"));
	for (std::shared_ptr<light> l : *lights)
		geometry->push_back(std::dynamic_pointer_cast<shape>(l));
	return std::shared_ptr<whitted_rt>(new whitted_rt(background_color, cam, lights, geometry));
}

std::shared_ptr<renderer> parser::parse_pathtracer(const pugi::xml_node &scene) {
	const std::shared_ptr<color> background_color = parse_color(scene.child("background_color"));
	std::shared_ptr<camera> cam = parse_camera(scene.child("camera"));
	std::shared_ptr<std::vector<std::shared_ptr<light>>> lights = parse_lights(scene.child("lights"));
	std::shared_ptr<std::vector<std::shared_ptr<shape>>> geometry = parse_surfaces(scene.child("surfaces"));
	for (std::shared_ptr<light> l : *lights)
		geometry->push_back(std::dynamic_pointer_cast<shape>(l));
	return std::shared_ptr<pathtracer>(new pathtracer(background_color, cam, lights, geometry));
}

std::shared_ptr<camera> parser::parse_camera(const pugi::xml_node &cam) {
	if (std::string(cam.attribute("type").value()) == "perspective")
		return parse_perspective_camera(cam);
	if (std::string(cam.attribute("type").value()) == "realistic")
		return parse_realistic_camera(cam);
	return std::shared_ptr<camera>(nullptr);
}

std::shared_ptr<camera> parser::parse_perspective_camera(const pugi::xml_node &cam) {
	position pos = parse_position(cam.child("position"));
	position lookat = parse_position(cam.child("lookat"));
	direction up = parse_direction(cam.child("up"));
	std::array<unsigned long, 2> resolution = {
			std::strtoul(cam.child("resolution").attribute("horizontal").value(), nullptr, 10),
			std::strtoul(cam.child("resolution").attribute("vertical").value(), nullptr, 10)};
	unsigned long max_bounces = std::strtoul(cam.child("max_bounces").attribute("n").value(), nullptr, 10);
	float fov = std::strtof(cam.child("horizontal_fov").attribute("angle").value(), nullptr);
	unsigned long shadowrays = std::strtoul(cam.child("shadow_rays").attribute("n").value(), nullptr, 10);
	unsigned long samples = 0;
	std::shared_ptr<sampler> s = parse_sampler(cam.child("sampling"), samples);
	float defocus = std::strtof(cam.child("defocus").attribute("d").value(), nullptr);
	std::shared_ptr<perspective_camera> out(
			new perspective_camera(pos, lookat, up, resolution, max_bounces, fov,
								   samples, shadowrays, s, defocus));
	return out;
}

std::shared_ptr<camera> parser::parse_realistic_camera(const pugi::xml_node &cam) {
	position pos = parse_position(cam.child("position"));
	position lookat = parse_position(cam.child("lookat"));
	direction up = parse_direction(cam.child("up"));
	std::array<unsigned long, 2> resolution = {
			std::strtoul(cam.child("resolution").attribute("horizontal").value(), nullptr, 10),
			std::strtoul(cam.child("resolution").attribute("vertical").value(), nullptr, 10)};
	unsigned long max_bounces = std::strtoul(cam.child("max_bounces").attribute("n").value(), nullptr, 10);
	float fov = std::strtof(cam.child("horizontal_fov").attribute("angle").value(), nullptr);
	unsigned long shadowrays = std::strtoul(cam.child("shadow_rays").attribute("n").value(), nullptr, 10);
	unsigned long samples = 1;
	std::shared_ptr<sampler> s = parse_sampler(cam.child("sampling"), samples);
	float defocus = std::strtof(cam.child("defocus").attribute("d").value(), nullptr);
	float focus = std::strtof(cam.child("focus").attribute("d").value(), nullptr);
	focus = focus == 0 ? std::numeric_limits<float>::max() : focus;
	float aperture = std::strtof(cam.child("aperture").attribute("d").value(), nullptr);
	std::shared_ptr<realistic_camera> out(
			new realistic_camera(pos, lookat, up, resolution, max_bounces, fov,
								 samples, shadowrays, s, defocus, focus,
								 aperture));
	return out;
}

std::shared_ptr<std::vector<std::shared_ptr<light>>> parser::parse_lights(const pugi::xml_node &lights) {
	std::shared_ptr<std::vector<std::shared_ptr<light>>> out(new std::vector<std::shared_ptr<light>>());
	for (pugi::xml_node l : lights.children("ambient_light"))
		out->push_back(parse_ambient_light(l));
	for (pugi::xml_node l : lights.children("parallel_light"))
		out->push_back(parse_parallel_light(l));
	for (pugi::xml_node l : lights.children("point_light"))
		out->push_back(parse_point_light(l));
	for (pugi::xml_node l : lights.children("lambertian_light"))
		out->push_back(parse_lambertian_light(l));
	for (pugi::xml_node l : lights.children("mesh_light"))
		out->push_back(parse_mesh_light(l));
	for (pugi::xml_node l : lights.children("sphere_light"))
		out->push_back(parse_sphere_light(l));
	return out;
}

std::shared_ptr<ambient_light> parser::parse_ambient_light(const pugi::xml_node &l) {
	return std::shared_ptr<ambient_light>(new ambient_light(parse_color(l.child("color"))));
}

std::shared_ptr<parallel_light> parser::parse_parallel_light(const pugi::xml_node &l) {
	return std::shared_ptr<parallel_light>(new parallel_light(parse_color(l.child("color")),
															  parse_direction(l.child("direction"))));
}

std::shared_ptr<point_light> parser::parse_point_light(const pugi::xml_node &l) {
	return std::shared_ptr<point_light>(new point_light(parse_color(l.child("color")),
														parse_direction(l.child("position"))));
}

std::shared_ptr<lambertian_light> parser::parse_lambertian_light(const pugi::xml_node &l) {
	return std::shared_ptr<lambertian_light>(new lambertian_light(parse_color(l.child("color")),
																  parse_direction(l.child("direction")),
																  parse_direction(l.child("position"))));
}

std::shared_ptr<mesh_light> parser::parse_mesh_light(const pugi::xml_node &l) {
	std::shared_ptr<mesh> m = parse_mesh(l.child("mesh"));
	parse_transform(l.child("mesh").child("transform"), m);
	return std::shared_ptr<mesh_light>(new mesh_light(m));
}

std::shared_ptr<sphere_light> parser::parse_sphere_light(const pugi::xml_node &l) {
	std::shared_ptr<sphere> s = parse_sphere(l.child("sphere"));
	parse_transform(l.child("sphere").child("transform"), s);
	return std::shared_ptr<sphere_light>(new sphere_light(s));
}

std::shared_ptr<std::vector<std::shared_ptr<shape>>> parser::parse_surfaces(const pugi::xml_node &surfaces) {
	std::shared_ptr<std::vector<std::shared_ptr<shape>>> out(new std::vector<std::shared_ptr<shape>>());
	for (pugi::xml_node s : surfaces.children()) {
		if (std::string(s.name()) == "sphere")
			out->push_back(parse_sphere(s));
		else if (std::string(s.name()) == "mesh")
			out->push_back(parse_mesh(s));
		for (pugi::xml_node t : s.children("transform"))
			parse_transform(t, out->back());
	}
	return out;
}

std::shared_ptr<sphere> parser::parse_sphere(const pugi::xml_node &s) {
	std::shared_ptr<material> matrl = parse_material(s.child("material"));
	return std::make_shared<sphere>(
			sphere(parse_direction(s.child("position")), matrl, std::strtof(s.attribute("radius").value(), nullptr)));
}

std::shared_ptr<mesh> parser::parse_mesh(const pugi::xml_node &m) {
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string err = tinyobj::LoadObj(shapes, materials, m.attribute("name").value());
	if (!err.empty()) {
		std::cerr << err << std::endl;
		exit(1);
	}
	std::shared_ptr<std::vector<std::shared_ptr<triangle>>> triangles(new std::vector<std::shared_ptr<triangle>>());
	std::shared_ptr<material> matrl;
	if (materials.empty())
		matrl = parse_material(m.child("material"));
	for (tinyobj::shape_t s : shapes)
		for (int i = 0; i < s.mesh.indices.size() / 3; i++) {
			std::shared_ptr<std::array<position, 3>> vertices(new std::array<position, 3>());
			std::shared_ptr<std::array<normal, 3>> normals(new std::array<normal, 3>());
			std::shared_ptr<std::array<vec2, 3>> texture_coords(new std::array<vec2, 3>());
			for (unsigned long ii = 0; ii < 3; ii++) {
				vertices->at(ii) = position(s.mesh.positions[s.mesh.indices[i * 3 + ii] * 3],
											s.mesh.positions[s.mesh.indices[i * 3 + ii] * 3 + 1],
											s.mesh.positions[s.mesh.indices[i * 3 + ii] * 3 + 2]);
				normals->at(ii) = normalise(normal(s.mesh.normals[s.mesh.indices[i * 3 + ii] * 3],
												   s.mesh.normals[s.mesh.indices[i * 3 + ii] * 3 + 1],
												   s.mesh.normals[s.mesh.indices[i * 3 + ii] * 3 + 2]));
				if (s.mesh.texcoords.size() != 0)
					texture_coords->at(ii) = vec2(s.mesh.texcoords[s.mesh.indices[i * 3 + ii] * 2],
												  s.mesh.texcoords[s.mesh.indices[i * 3 + ii] * 2 + 1]);
				else
					texture_coords->at(ii) = vec2();
			}
			triangles->push_back(
					std::make_shared<triangle>(triangle(direction(), matrl, vertices, normals, texture_coords)));
		}
	return std::shared_ptr<mesh>(new mesh(direction(), matrl, triangles));
}

void parser::parse_transform(const pugi::xml_node &t, std::shared_ptr<shape> s) {
	for (pugi::xml_node r : t.children()) {
		if (std::string(r.name()) == "scale") {
			std::array<float, 3> sf = {
					std::strtof(r.attribute("x").value(), nullptr),
					std::strtof(r.attribute("y").value(), nullptr),
					std::strtof(r.attribute("z").value(), nullptr)
			};
			s->scale(sf);
		} else if (std::string(r.name()) == "rotateX")
			s->rotateX(std::strtof(r.attribute("theta").value(), nullptr));
		else if (std::string(r.name()) == "rotateY")
			s->rotateY(std::strtof(r.attribute("theta").value(), nullptr));
		else if (std::string(r.name()) == "rotateZ")
			s->rotateZ(std::strtof(r.attribute("theta").value(), nullptr));
		else if (std::string(r.name()) == "translate") {
			direction d = parse_direction(r);
			s->translate(d);
		}
	}
}

std::shared_ptr<material> parser::parse_material(const pugi::xml_node &m) {
	if (std::string(m.attribute("type").value()) == "solid")
		return std::make_shared<solid_material>(
				solid_material(parse_color(m.child("emit")), parse_color(m.child("color"))));
	if (std::string(m.attribute("type").value()) == "lambertian")
		return std::make_shared<lambertian_material>(
				lambertian_material(parse_color(m.child("emit")), parse_color(m.child("color")),
									std::strtof(m.child("lambertian").attribute("ka").value(), nullptr),
									std::strtof(m.child("lambertian").attribute("kd").value(), nullptr)));
	if (std::string(m.attribute("type").value()) == "phong")
		return std::make_shared<phong_material>(
				phong_material(parse_color(m.child("emit")), parse_color(m.child("color")),
							   std::strtof(m.child("phong").attribute("ka").value(), nullptr),
							   std::strtof(m.child("phong").attribute("kd").value(), nullptr),
							   std::strtof(m.child("phong").attribute("ks").value(), nullptr),
							   std::strtof(m.child("phong").attribute("exponent").value(), nullptr)));
	if (std::string(m.attribute("type").value()) == "specular")
		return std::make_shared<specular_material>(
				specular_material(parse_color(m.child("emit")), parse_color(m.child("color")),
								  std::strtof(m.child("phong").attribute("ka").value(), nullptr),
								  std::strtof(m.child("phong").attribute("kd").value(), nullptr),
								  std::strtof(m.child("phong").attribute("ks").value(), nullptr),
								  std::strtof(m.child("phong").attribute("exponent").value(), nullptr),
								  std::strtof(m.child("reflectance").attribute("r").value(), nullptr)));
	if (std::string(m.attribute("type").value()) == "transparent")
		return std::make_shared<transparent_material>(
				transparent_material(parse_color(m.child("emit")), parse_color(m.child("color")),
									 std::strtof(m.child("phong").attribute("ka").value(), nullptr),
									 std::strtof(m.child("phong").attribute("kd").value(), nullptr),
									 std::strtof(m.child("phong").attribute("ks").value(), nullptr),
									 std::strtof(m.child("phong").attribute("exponent").value(), nullptr),
									 std::strtof(m.child("reflectance").attribute("r").value(), nullptr),
									 std::strtof(m.child("transmittance").attribute("t").value(), nullptr),
									 std::strtof(m.child("refraction").attribute("iof").value(), nullptr)));
	if (std::string(m.attribute("type").value()) == "textured")
		return std::make_shared<textured_material>(
				textured_material(parse_color(m.child("emit")),
								  std::strtof(m.child("phong").attribute("ka").value(), nullptr),
								  std::strtof(m.child("phong").attribute("kd").value(), nullptr),
								  std::strtof(m.child("phong").attribute("ks").value(), nullptr),
								  std::strtof(m.child("phong").attribute("exponent").value(), nullptr),
								  load_image(m.child("texture").attribute("name").value())));
	return std::shared_ptr<material>(nullptr);
}

std::shared_ptr<color> parser::parse_color(const pugi::xml_node &col) {
	return std::shared_ptr<color>(new color(std::strtof(col.attribute("r").value(), nullptr),
											std::strtof(col.attribute("g").value(), nullptr),
											std::strtof(col.attribute("b").value(), nullptr)));
}

position parser::parse_position(const pugi::xml_node &p) {
	position out = position(std::strtof(p.attribute("x").value(), nullptr),
							std::strtof(p.attribute("y").value(), nullptr),
							std::strtof(p.attribute("z").value(), nullptr));
	return out;
}

direction parser::parse_direction(const pugi::xml_node &d) {
	direction out = direction(std::strtof(d.attribute("x").value(), nullptr),
							  std::strtof(d.attribute("y").value(), nullptr),
							  std::strtof(d.attribute("z").value(), nullptr));
	return out;
}

std::shared_ptr<std::vector<std::vector<color>>> parser::load_image(const std::string path) {
	cimg_library::CImg<float> img(path.c_str());
	std::shared_ptr<std::vector<std::vector<color>>> out(new std::vector<std::vector<color>>());
	out->reserve(static_cast<unsigned long>(img.height()));
	for (unsigned int y = 0; y < img.height(); y++) {
		out->push_back(std::vector<color>());
		out->at(y).reserve(static_cast<unsigned long>(img.width()));
		for (unsigned int x = 0; x < img.width(); x++)
			out->at(y).push_back(color(img(x, y, 0) / 255.0f, img(x, y, 1) / 255.0f, img(x, y, 2) / 255.0f));
	}
	return out;
}

std::shared_ptr<sampler> parser::parse_sampler(const pugi::xml_node &node, unsigned long &samples) {
	samples = std::strtoul(node.attribute("n").value(), nullptr, 10);
	if (std::string(node.attribute("type").value()) == "random")
		return parse_random_sampler(node);
	else
		return std::shared_ptr<sampler>(new sampler());
}

std::shared_ptr<sampler> parser::parse_random_sampler(const pugi::xml_node &node) {
	return std::shared_ptr<sampler>(new random_sampler());
}