//
// Created by chais on 15.09.15.
//

#include "parser.h"

std::shared_ptr<whitted_rt> parser::parse(const char *in_path, std::string &out_path) {
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(in_path, pugi::parse_default | pugi::parse_doctype);
	assert(result);
	pugi::xml_node scene = doc.child("scene");
	out_path = scene.attribute("output_file").value();
	std::shared_ptr<color> background_color = parse_color(scene.child("background_color"));
	std::shared_ptr<camera> cam = parse_camera(scene.child("camera"));
	std::shared_ptr<std::vector<std::shared_ptr<light>>> lights = parse_lights(scene.child("lights"));
	std::shared_ptr<std::vector<std::shared_ptr<shape>>> geometry = parse_surfaces(scene.child("surfaces"));
	return std::shared_ptr<whitted_rt>(new whitted_rt(background_color, cam, lights, geometry));
}

std::shared_ptr<camera> parser::parse_camera(const pugi::xml_node &cam) {
	if (std::string(cam.attribute("type").value()) == "perspective") {
		std::shared_ptr<point> position = parse_position(cam.child("position"));
		std::shared_ptr<point> lookat = parse_position(cam.child("lookat"));
		std::shared_ptr<direction> up = parse_direction(cam.child("up"));
		std::array<unsigned long, 2> resolution = {std::strtoul(cam.child("resolution").attribute("horizontal").value(),
																nullptr, 10),
												   std::strtoul(cam.child("resolution").attribute("vertical").value(),
																nullptr, 10)};
		float stepwidth = std::tan(
				helper::to_radians(std::strtof(cam.child("horizontal_fov").attribute("angle").value(), nullptr))) /
						  (resolution[0] / 2);
		std::shared_ptr<sampler> s = parse_sampler(cam.child("sampling"), stepwidth);
		std::shared_ptr<perspective_camera> out(new perspective_camera(*position, *lookat, *up, resolution,
																	   std::strtoul(cam.child("max_bounces").attribute(
																			   "n").value(), nullptr, 10), std::strtof(
						cam.child("horizontal_fov").attribute(
								"angle").value(), nullptr),
																	   s));
		return out;
	}
	return std::shared_ptr<camera>(nullptr);
}

std::shared_ptr<std::vector<std::shared_ptr<light>>> parser::parse_lights(const pugi::xml_node &lights) {
	std::shared_ptr<std::vector<std::shared_ptr<light>>> out(new std::vector<std::shared_ptr<light>>());
	out->push_back(parse_ambient_light(lights.child("ambient_light")));
	for (pugi::xml_node l : lights.children("parallel_light"))
		out->push_back(parse_parallel_light(l));
	for (pugi::xml_node l : lights.children("point_light"))
		out->push_back(parse_point_light(l));
	return out;
}

std::shared_ptr<ambient_light> parser::parse_ambient_light(const pugi::xml_node &l) {
	return std::make_shared<ambient_light>(ambient_light(parse_color(l.child("color"))));
}

std::shared_ptr<parallel_light> parser::parse_parallel_light(const pugi::xml_node &l) {
	return std::make_shared<parallel_light>(parallel_light(parse_color(l.child("color")),
														   parse_direction(l.child("direction"))));
}

std::shared_ptr<point_light> parser::parse_point_light(const pugi::xml_node &l) {
	return std::make_shared<point_light>(point_light(parse_color(l.child("color")),
													 parse_position(l.child("position"))));
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

std::shared_ptr<sphere> parser::parse_sphere(pugi::xml_node &s) {
	std::shared_ptr<material> matrl = parse_material(s.child("material"));
	return std::make_shared<sphere>(sphere(std::strtof(s.attribute("radius").value(), nullptr),
										   parse_direction(s.child("position")),
										   matrl));
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
	for (tinyobj::shape_t s : shapes)
		for (int i = 0; i < s.mesh.indices.size() / 3; i++) {
			std::shared_ptr<std::array<point, 3>> vertices(new std::array<point, 3>());
			std::shared_ptr<std::array<normal, 3>> normals(new std::array<normal, 3>());
			std::shared_ptr<std::array<vec2, 3>> texture_coords(new std::array<vec2, 3>());
			for (unsigned long ii = 0; ii < 3; ii++) {
				vertices->at(ii) = point(s.mesh.positions[s.mesh.indices[i * 3 + ii] * 3],
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
			triangles->push_back(std::make_shared<triangle>(triangle(vertices, normals, texture_coords)));
		}
	std::shared_ptr<material> matrl;
	if (materials.empty())
		matrl = parse_material(m.child("material"));
	return std::shared_ptr<mesh>(new mesh(std::shared_ptr<direction>(new direction()), matrl, triangles));
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
			std::shared_ptr<direction> d = parse_direction(r);
			s->translate(*d);
		}
	}
}

std::shared_ptr<material> parser::parse_material(const pugi::xml_node &m) {
	if (std::string(m.attribute("type").value()) == "phong") {
		return std::make_shared<phong_material>(phong_material(*parse_color(m.child("color")),
															   std::strtof(m.child("phong").attribute("ka").value(),
																		   nullptr),
															   std::strtof(m.child("phong").attribute("kd").value(),
																		   nullptr),
															   std::strtof(m.child("phong").attribute("ks").value(),
																		   nullptr),
															   std::strtof(
																	   m.child("phong").attribute("exponent").value(),
																	   nullptr)));
	} else if (std::string(m.attribute("type").value()) == "lambertian") {
		return std::make_shared<lambertian_material>(lambertian_material(*parse_color(m.child("color")),
																		 std::strtof(m.child("lambertian").attribute(
																							 "ka").value(),
																					 nullptr),
																		 std::strtof(m.child("lambertian").attribute(
																							 "kd").value(),
																					 nullptr)));
	} else if (std::string(m.attribute("type").value()) == "specular") {
		return std::make_shared<specular_material>(specular_material(*parse_color(m.child("color")),
																	 std::strtof(
																			 m.child("phong").attribute("ka").value(),
																			 nullptr),
																	 std::strtof(
																			 m.child("phong").attribute("kd").value(),
																			 nullptr),
																	 std::strtof(
																			 m.child("phong").attribute("ks").value(),
																			 nullptr),
																	 std::strtof(m.child("phong").attribute(
																						 "exponent").value(),
																				 nullptr),
																	 std::strtof(m.child("reflectance").attribute(
																						 "r").value(),
																				 nullptr)));
	} else if (std::string(m.attribute("type").value()) == "transparent") {
		return std::make_shared<transparent_material>(transparent_material(*parse_color(m.child("color")),
																		   std::strtof(m.child("phong").attribute(
																							   "ka").value(),
																					   nullptr),
																		   std::strtof(m.child("phong").attribute(
																							   "kd").value(),
																					   nullptr),
																		   std::strtof(m.child("phong").attribute(
																							   "ks").value(),
																					   nullptr),
																		   std::strtof(m.child("phong").attribute(
																							   "exponent").value(),
																					   nullptr),
																		   std::strtof(m.child("reflectance").attribute(
																							   "r").value(),
																					   nullptr),
																		   std::strtof(
																				   m.child("transmittance").attribute(
																						   "t").value(),
																				   nullptr),
																		   std::strtof(m.child("refraction").attribute(
																							   "iof").value(),
																					   nullptr)));
	} else if (std::string(m.attribute("type").value()) == "textured") {
		return std::make_shared<textured_material>(
				textured_material(std::strtof(m.child("phong").attribute("ka").value(),
											  nullptr),
								  std::strtof(m.child("phong").attribute("kd").value(),
											  nullptr),
								  std::strtof(m.child("phong").attribute("ks").value(),
											  nullptr),
								  std::strtof(m.child("phong").attribute("exponent").value(),
											  nullptr),
								  load_image(m.child("texture").attribute("name").value())));
	}
	return std::shared_ptr<material>(nullptr);
}

std::shared_ptr<color> parser::parse_color(const pugi::xml_node &col) {
	return std::make_shared<color>(color(std::strtof(col.attribute("r").value(), nullptr),
										 std::strtof(col.attribute("g").value(), nullptr),
										 std::strtof(col.attribute("b").value(), nullptr)));
}

std::shared_ptr<point> parser::parse_position(const pugi::xml_node &p) {
	return std::make_shared<point>(point(std::strtof(p.attribute("x").value(), nullptr),
										 std::strtof(p.attribute("y").value(), nullptr),
										 std::strtof(p.attribute("z").value(), nullptr)));
}

std::shared_ptr<direction> parser::parse_direction(const pugi::xml_node &d) {
	return std::make_shared<direction>(direction(std::strtof(d.attribute("x").value(), nullptr),
												 std::strtof(d.attribute("y").value(), nullptr),
												 std::strtof(d.attribute("z").value(), nullptr)));
}

std::shared_ptr<std::vector<std::vector<color>>> parser::load_image(const std::string path) {
	png::image<png::rgb_pixel> img(path);
	std::shared_ptr<std::vector<std::vector<color>>> out(new std::vector<std::vector<color>>());
	out->reserve(img.get_height());
	for (unsigned long y = 0; y < img.get_height(); y++) {
		out->push_back(std::vector<color>());
		out->at(y).reserve(img.get_width());
		for (unsigned long x = 0; x < img.get_width(); x++) {
			png::rgb_pixel tmp = img.get_pixel(x, y);
			out->at(y).push_back(color(static_cast<int>(tmp.red) / 255.0f,
									   static_cast<int>(tmp.green) / 255.0f,
									   static_cast<int>(tmp.blue) / 255.0f));
		}
	}
	return out;
}

std::shared_ptr<sampler> parser::parse_sampler(const pugi::xml_node &node,
											   const float &stepwidth) {
	if (std::string(node.attribute("type").value()) == "random")
		return parse_random_sampler(node, stepwidth);
	else
		return std::shared_ptr<sampler>(new sampler());
}

std::shared_ptr<sampler> parser::parse_random_sampler(const pugi::xml_node &node,
													  const float &stepwidth) {

	return std::shared_ptr<sampler>(
			new random_sampler(stepwidth, stepwidth, std::strtoul(node.attribute("n").value(),
																		nullptr, 10)));
}
