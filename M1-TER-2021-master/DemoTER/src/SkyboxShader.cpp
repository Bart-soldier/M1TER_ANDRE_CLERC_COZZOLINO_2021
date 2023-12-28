#include "DemoTER/SkyboxShader.hpp"

SkyboxShader::SkyboxShader(): Shader{"shaders/skybox.vert", "shaders/skybox.frag"} {
	fetchUniformLocations();
}

void SkyboxShader::setCamera(Camera *camera) {
	sendMat4(SkyboxShader::U_PROJECTION, camera->getProjection());
	sendMat4(SkyboxShader::U_VIEW, camera->getViewMatrix());
}

void SkyboxShader::setExposure(float e) {
	sendFloat(SkyboxShader::U_EXPOSURE, e);
}

void SkyboxShader::setGamma(float g) {
	sendFloat(SkyboxShader::U_GAMMA, g);
}

void SkyboxShader::fetchUniformLocations() {
	uniformLocations = new GLuint[4];

	uniformLocations[U_VIEW] = queryUniformLocation("V");
	uniformLocations[U_PROJECTION] = queryUniformLocation("P");
	uniformLocations[U_EXPOSURE] = queryUniformLocation("exposure");
	uniformLocations[U_GAMMA] = queryUniformLocation("gamma");
}
