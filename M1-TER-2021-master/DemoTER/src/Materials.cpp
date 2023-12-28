#include "DemoTER/Materials.hpp"

Materials::Material* Materials::changeMaterial(int material) {
	switch (material) {
		case 0:
			return bark();
		case 1:
			return bricks();
		case 2:
			return cerberus();
		case 3:
			return ground_gravel();
		case 4:
			return ground_ice();
		case 5:
			return metal();
		case 6:
			return metal_panel();
		case 7:
			return rock_moss();
		case 8:
			return rusted_iron();
		case 9:
			return statue();
		case 10:
			return sword();
		case 11:
			return textiles_craft();
		case 12:
			return wood_varnish_rough();

		default:
			return rusted_iron();
	}
}

Materials::Material* Materials::bark() {
	Texture::Params textureParams{};
	textureParams.correctGamma = true;

	return new Materials::Material{
		{"textures/materials/bark/bark_A.png", textureParams},
		"textures/materials/bark/bark_N.png",
		"textures/materials/bark/bark_R.png",
		glm::vec3{0},
		"textures/materials/bark/bark_AO.png"
	};
}

Materials::Material* Materials::bricks() {
	Texture::Params textureParams{};
	textureParams.correctGamma = true;

	return new Materials::Material{
		{"textures/materials/bricks/bricks_A.png", textureParams},
		"textures/materials/bricks/bricks_N.png",
		"textures/materials/bricks/bricks_R.png",
		glm::vec3{0},
		"textures/materials/bricks/bricks_AO.png"
	};
}

Materials::Material* Materials::cerberus() {
	Texture::Params textureParams{};
	textureParams.correctGamma = true;

	return new Materials::Material{
			{"textures/materials/cerberus/cerberus_A.png", textureParams},
			"textures/materials/cerberus/cerberus_N.png",
			"textures/materials/cerberus/cerberus_R.png",
			"textures/materials/cerberus/cerberus_M.png",
			"textures/materials/cerberus/cerberus_AO.png"
	};
}

Materials::Material* Materials::ground_gravel() {
	Texture::Params textureParams{};
	textureParams.correctGamma = true;

	return new Materials::Material{
		{"textures/materials/ground_gravel/ground_gravel_A.png", textureParams},
		"textures/materials/ground_gravel/ground_gravel_N.png",
		"textures/materials/ground_gravel/ground_gravel_R.png",
		glm::vec3{0},
		"textures/materials/ground_gravel/ground_gravel_AO.png"
	};
}

Materials::Material* Materials::ground_ice() {
	Texture::Params textureParams{};
	textureParams.correctGamma = true;

	return new Materials::Material{
		{"textures/materials/ground_ice/ground_ice_A.png", textureParams},
		"textures/materials/ground_ice/ground_ice_N.png",
		"textures/materials/ground_ice/ground_ice_R.png",
		glm::vec3{0},
		"textures/materials/ground_ice/ground_ice_AO.png"
	};
}

Materials::Material* Materials::metal() {
	Texture::Params textureParams{};
	textureParams.correctGamma = true;

	return new Materials::Material{
		{"textures/materials/metal/metal_A.jpg", textureParams},
		"textures/materials/metal/metal_N.jpg",
		"textures/materials/metal/metal_R.jpg",
		"textures/materials/metal/metal_M.jpg",
		glm::vec3{1},
	};
}

Materials::Material* Materials::metal_panel() {
	Texture::Params textureParams{};
	textureParams.correctGamma = true;

	return new Materials::Material{
		{"textures/materials/metal_panel/metal_panel_A.jpg", textureParams},
		"textures/materials/metal_panel/metal_panel_N.jpg",
		"textures/materials/metal_panel/metal_panel_R.jpg",
		"textures/materials/metal_panel/metal_panel_M.jpg",
		"textures/materials/metal_panel/metal_panel_AO.jpg"
	};
}

Materials::Material* Materials::rock_moss() {
	Texture::Params textureParams{};
	textureParams.correctGamma = true;

	return new Materials::Material{
		{"textures/materials/rock_moss/rock_moss_A.png", textureParams},
		"textures/materials/rock_moss/rock_moss_N.png",
		"textures/materials/rock_moss/rock_moss_R.png",
		glm::vec3{0},
		"textures/materials/rock_moss/rock_moss_AO.png"
	};
}

Materials::Material* Materials::rusted_iron() {
	Texture::Params textureParams{};
	textureParams.correctGamma = true;

	return new Materials::Material{
			{"textures/materials/rusted_Iron/rusted_Iron_A.png", textureParams},
			"textures/materials/rusted_Iron/rusted_Iron_N.png",
			"textures/materials/rusted_Iron/rusted_Iron_R.png",
			"textures/materials/rusted_Iron/rusted_Iron_M.png",
			glm::vec3{1}
	};
}

Materials::Material* Materials::statue() {
	Texture::Params textureParams{};
	textureParams.correctGamma = true;

	return new Materials::Material{
			{"textures/materials/statue/statue_A.jpg", textureParams},
			"textures/materials/statue/statue_N.jpg",
			"textures/materials/statue/statue_R.jpg",
			glm::vec3{0},
			glm::vec3{1}
	};
}

Materials::Material* Materials::sword() {
	Texture::Params textureParams{};
	textureParams.correctGamma = true;

	return new Materials::Material{
			{"textures/materials/sword/sword_A.png", textureParams},
			"textures/materials/sword/sword_N.png",
			"textures/materials/sword/sword_R.png",
			"textures/materials/sword/sword_M.png",
			"textures/materials/sword/sword_AO.png"
	};
}

Materials::Material* Materials::textiles_craft() {
	Texture::Params textureParams{};
	textureParams.correctGamma = true;

	return new Materials::Material{
		{"textures/materials/textiles_craft/textiles_craft_A.png", textureParams},
		"textures/materials/textiles_craft/textiles_craft_N.png",
		"textures/materials/textiles_craft/textiles_craft_R.png",
		glm::vec3{0},
		"textures/materials/textiles_craft/textiles_craft_AO.png"
	};
}

Materials::Material* Materials::wood_varnish_rough() {
	Texture::Params textureParams{};
	textureParams.correctGamma = true;

	return new Materials::Material{
		{"textures/materials/wood_varnish_rough/wood_varnish_rough_A.png", textureParams},
		"textures/materials/wood_varnish_rough/wood_varnish_rough_N.png",
		"textures/materials/wood_varnish_rough/wood_varnish_rough_R.png",
		glm::vec3{0},
		"textures/materials/wood_varnish_rough/wood_varnish_rough_AO.png"
	};
}

Materials::Material* Materials::customMaterial(float color[3], float normal[3], float rough, float metal, float ao) {
	return new Materials::Material{
	glm::vec3{color[0], color[1], color[2]},
	glm::vec3{normal[0], normal[1], normal[2]},
	glm::vec3{rough},
	glm::vec3{metal},
	glm::vec3{ao}
	};
}

Materials::Material* Materials::customMaterial(glm::vec3 color, glm::vec3 normal, glm::vec3 rough, glm::vec3 metal, glm::vec3 ao) {
	return new Materials::Material{
	color,
	normal,
	rough,
	metal,
	ao
	};
}