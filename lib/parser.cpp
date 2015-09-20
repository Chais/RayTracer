//
// Created by chais on 15.09.15.
//

#include "parser.h"
#include "geometry/material/lambertian_material.h"

whitted_rt *parser::parse(const char *in_path, std::string &out_path) {
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(in_path, pugi::parse_default | pugi::parse_doctype);
	assert(result);
	pugi::xml_node scene = doc.child("scene");
	out_path = scene.attribute("output_file").value();
	color *background_color = parse_color(scene.child("background_color"));
	camera *cam = parse_camera(scene.child("camera"));
	std::vector<light *> *lights = parse_lights(scene.child("lights"));
	std::vector<shape *> *geometry = parse_surfaces(scene.child("surfaces"));
	return new whitted_rt(background_color, cam, lights, geometry);
}

camera *parser::parse_camera(const pugi::xml_node &cam) {
	if (std::string(cam.attribute("type").value()) == "perspective") {
		point *position = parse_position(cam.child("position"));
		point *lookat = parse_position(cam.child("lookat"));
		direction *up = parse_direction(cam.child("up"));
		std::array<unsigned long, 2> resolution = {std::strtoul(cam.child("resolution").attribute("horizontal").value(),
																nullptr, 10),
												   std::strtoul(cam.child("resolution").attribute("vertical").value(),
																nullptr, 10)};
		perspective_camera *out = new perspective_camera(*position,
														 *lookat,
														 *up,
														 resolution,
														 std::strtoul(cam.child("max_bounces").attribute("n").value(),
																	  nullptr, 10),
														 1, // Number of samples per pixel
														 std::strtof(
																 cam.child("horizontal_fov").attribute("angle").value(),
																 nullptr)
		);
		delete position;
		delete lookat;
		delete up;
		return out;
	}
	return nullptr;
}

std::vector<light *> *parser::parse_lights(const pugi::xml_node &lights) {
	std::vector<light *> *out = new std::vector<light *>();
	out->push_back(parse_ambient_light(lights.child("ambient_light")));
	for (pugi::xml_node l : lights.children("parallel_light"))
		out->push_back(parse_parallel_light(l));
	for (pugi::xml_node l : lights.children("point_light"))
		out->push_back(parse_point_light(l));
	return out;
}

ambient_light *parser::parse_ambient_light(const pugi::xml_node &l) {
	return new ambient_light(parse_color(l.child("color")));
}

parallel_light *parser::parse_parallel_light(const pugi::xml_node &l) {
	return new parallel_light(parse_color(l.child("color")),
							  parse_direction(l.child("direction")));
}

point_light *parser::parse_point_light(const pugi::xml_node &l) {
	return new point_light(parse_color(l.child("color")),
						   parse_position(l.child("position")));
}

std::vector<shape *> *parser::parse_surfaces(const pugi::xml_node &surfaces) {
	std::vector<shape *> *out = new std::vector<shape *>();
	for (pugi::xml_node s : surfaces.children("sphere"))
		out->push_back(parse_sphere(s));
	for (pugi::xml_node m : surfaces.children("mesh"))
		out->push_back(parse_mesh(m));
	return out;
}

sphere *parser::parse_sphere(pugi::xml_node &s) {
	material *matrl = parse_material(s.child("material"));
	sphere *out = new sphere(std::strtof(s.attribute("radius").value(), nullptr), parse_direction(s.child("position")),
							 matrl);
	for (pugi::xml_node t : s.children("transforms"))
		parse_transform(t, out);
	return out;
}

mesh *parser::parse_mesh(const pugi::xml_node &m) {
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string err = tinyobj::LoadObj(shapes, materials, m.attribute("name").value());
	if (!err.empty()) {
		std::cerr << err << std::endl;
		exit(1);
	}
	std::vector<triangle *> *triangles = new std::vector<triangle *>();
	for (tinyobj::shape_t s : shapes)
		for (int i = 0; i < s.mesh.indices.size()/3; i++) {
			std::array<point, 3> *vertices = new std::array<point, 3>();
			std::array<normal, 3> *normals = new std::array<normal, 3>();
			std::array<vec2, 3> *texture_coords = new std::array<vec2, 3>();
			for (int ii = 0; ii < 3; ii++) {
				vertices->at(ii) = point(s.mesh.positions[s.mesh.indices[i*3+ii]*3],
									   s.mesh.positions[s.mesh.indices[i*3+ii]*3+1],
									   s.mesh.positions[s.mesh.indices[i*3+ii]*3+2]);
				normals->at(ii) = normal(s.mesh.normals[s.mesh.indices[i*3+ii]*3],
									   s.mesh.normals[s.mesh.indices[i*3+ii]*3+1],
									   s.mesh.normals[s.mesh.indices[i*3+ii]*3+2]);
				texture_coords->at(ii) = vec2(s.mesh.texcoords[s.mesh.indices[i*3+ii]*2],
											s.mesh.texcoords[s.mesh.indices[i*3+ii]*2+1]);
			}
			triangles->push_back(new triangle(vertices, normals, texture_coords));
		}
	material *matrl;
	if (materials.empty()) {
		matrl = parse_material(m.child("material"));
	}
	return new mesh(new direction(), matrl, triangles);
}

void parser::parse_transform(const pugi::xml_node &t, sphere *s) {
	std::array<float, 3> sf = {
			std::strtof(t.child("scale").attribute("x").value(), nullptr),
			std::strtof(t.child("scale").attribute("y").value(), nullptr),
			std::strtof(t.child("scale").attribute("z").value(), nullptr)
	};
	s->scale(sf);
	for (pugi::xml_node r : t.children()) {
		if (std::string(r.name()) == "rotateX")
			s->rotateX(std::strtof(r.attribute("theta").value(), nullptr));
		else if (std::string(r.name()) == "rotateY")
			s->rotateY(std::strtof(r.attribute("theta").value(), nullptr));
		else if (std::string(r.name()) == "rotateZ")
			s->rotateZ(std::strtof(r.attribute("theta").value(), nullptr));
	}
	direction *d = parse_direction(t.child("translate"));
	s->translate(*d);
	delete d;
}

material *parser::parse_material(const pugi::xml_node &m) {
	if (std::string(m.attribute("type").value()) == "phong") {
		color *col = parse_color(m.child("color"));
		phong_material *out = new phong_material(*col,
												 std::strtof(m.child("phong").attribute("ka").value(), nullptr),
												 std::strtof(m.child("phong").attribute("kd").value(), nullptr),
												 std::strtof(m.child("phong").attribute("ks").value(), nullptr),
												 std::strtof(m.child("phong").attribute("exponent").value(), nullptr));
		delete col;
		return out;
	} else if (std::string(m.attribute("type").value()) == "lambertian") {
		color *col = parse_color(m.child("color"));
		lambertian_material *out = new lambertian_material(*col,
												 std::strtof(m.child("lambertian").attribute("ka").value(), nullptr),
												 std::strtof(m.child("lambertian").attribute("kd").value(), nullptr));
		delete col;
		return out;
	}
	return nullptr;
}

color *parser::parse_color(const pugi::xml_node &col) {
	return new color(std::strtof(col.attribute("r").value(), nullptr),
					 std::strtof(col.attribute("g").value(), nullptr),
					 std::strtof(col.attribute("b").value(), nullptr));
}

point *parser::parse_position(const pugi::xml_node &p) {
	return new point(std::strtof(p.attribute("x").value(), nullptr),
					 std::strtof(p.attribute("y").value(), nullptr),
					 std::strtof(p.attribute("z").value(), nullptr));
}

direction *parser::parse_direction(const pugi::xml_node &d) {
	return new direction(std::strtof(d.attribute("x").value(), nullptr),
						 std::strtof(d.attribute("y").value(), nullptr),
						 std::strtof(d.attribute("z").value(), nullptr));
}
