#include "DemoTER/PBRShader.hpp"

int PBRShader::MAX_LIGHT_COUNT = 4;

PBRShader::PBRShader(): Shader{"shaders/pbr.vert", "shaders/pbr.frag"} {
	fetchUniformLocations();

	bind();
	sendFloat(PBRShader::U_GAMMA, 2.2);
	sendFloat(PBRShader::U_EXPOSURE, 1);

	sendInt(U_ALBEDO, T_ALBEDO);
	sendInt(U_NORMAL, T_NORMAL);
	sendInt(U_ROUGHNESS, T_ROUGHNESS);
	sendInt(U_METALLIC, T_METALLIC);
	sendInt(U_AO, T_AO);
	sendInt(U_IRRADIANCE, T_IRRADIANCE); 
	sendInt(U_PREFILTER, T_PREFILTER);
	sendInt(U_BRDFLUT, T_BRDFLUT);
}

void PBRShader::fetchUniformLocations() {
	uniformLocations = new GLuint[15];

	uniformLocations[U_MODEL] = queryUniformLocation("M");
	uniformLocations[U_PV] = queryUniformLocation("PV");
	uniformLocations[U_CAM_POS] = queryUniformLocation("camPos");
	uniformLocations[U_LIGHT_POSITIONS] = queryUniformLocation("lightPositions");
	uniformLocations[U_LIGHT_COLORS] = queryUniformLocation("lightColors");
	uniformLocations[U_GAMMA] = queryUniformLocation("gamma");
	uniformLocations[U_EXPOSURE] = queryUniformLocation("exposure");
	uniformLocations[U_ALBEDO] = queryUniformLocation("albedoSampler");
	uniformLocations[U_NORMAL] = queryUniformLocation("normalSampler");
	uniformLocations[U_ROUGHNESS] = queryUniformLocation("roughnessSampler");
	uniformLocations[U_METALLIC] = queryUniformLocation("metallicSampler");
	uniformLocations[U_AO] = queryUniformLocation("aoSampler");
	uniformLocations[U_IRRADIANCE] = queryUniformLocation("irradianceMap");
	uniformLocations[U_PREFILTER] = queryUniformLocation("prefilterMap");
	uniformLocations[U_BRDFLUT] = queryUniformLocation("brdfLUT");
}

void PBRShader::setCamera(Camera *camera) {
	sendMat4(U_PV, camera->getPVMatrix());
	sendVec3(U_CAM_POS, camera->getPosition());
}

void PBRShader::setLights(std::vector<glm::vec3> &lightPositions, std::vector<glm::vec3> &lightColors) {
	sendVec3(U_LIGHT_POSITIONS, lightPositions);
	sendVec3(U_LIGHT_COLORS, lightColors);
}

void PBRShader::setExposure(float e) {
	sendFloat(PBRShader::U_EXPOSURE, e);
}

void PBRShader::setGamma(float g) {
	sendFloat(PBRShader::U_GAMMA, g);
}

void PBRShader::render(Mesh *mesh, Materials::Material *material, glm::mat4x4 &transform) {
	material->albedo.bind(T_ALBEDO);
	material->normal.bind(T_NORMAL);
	material->roughness.bind(T_ROUGHNESS);
	material->metallic.bind(T_METALLIC);
	material->ao.bind(T_AO);

	sendMat4(PBRShader::U_MODEL, transform);
	mesh->draw();
}