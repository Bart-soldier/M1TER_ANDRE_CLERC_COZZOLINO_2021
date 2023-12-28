#include "DemoTER/MergeShader.hpp"

MergeShader::MergeShader(): Shader{"shaders/merge.vert", "shaders/merge.frag"} {
	fetchUniformLocations();

	bind();
	sendInt(U_BASE, T_BASE);
	sendInt(U_BLOOM, T_BLOOM);
}

void MergeShader::fetchUniformLocations() {
	uniformLocations = new GLuint[4];

	uniformLocations[U_GAMMA] = queryUniformLocation("gamma");
	uniformLocations[U_BASE] = queryUniformLocation("base");
	uniformLocations[U_BLOOM] = queryUniformLocation("bloom");
	uniformLocations[U_SHOWBLOOM] = queryUniformLocation("showBloom");
}

void MergeShader::setGamma(float gamma) {
	sendFloat(U_GAMMA, gamma);
}

void MergeShader::setShowBloom(bool showBloom) {
	sendBool(U_SHOWBLOOM, showBloom);
}
