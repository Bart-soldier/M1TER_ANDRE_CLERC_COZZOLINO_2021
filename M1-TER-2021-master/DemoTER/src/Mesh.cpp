#include "DemoTER/Mesh.hpp"
#include "DemoTER/PBRShader.hpp"
#include "DemoTER/utils/Parser.hpp"

Mesh::Mesh(const char *path) {
	std::unique_ptr<Parser::Result> result = Parser::loadObj(path);
	std::shared_ptr<VBO> vertexVBO = std::make_shared<VBO>(result->vertex, PBRShader::A_POSITION);
	vao.addVBO(vertexVBO);
	std::shared_ptr<VBO> normalVBO = std::make_shared<VBO>(result->normal, PBRShader::A_NORMAL);
	vao.addVBO(normalVBO);
	std::shared_ptr<VBO> tangentVBO = std::make_shared<VBO>(result->tangent, PBRShader::A_TANGENT);
	vao.addVBO(tangentVBO);
	if(result->uv.size() > 0) {
		std::shared_ptr<VBO> uvVBO = std::make_shared<VBO>(result->uv, PBRShader::A_UV);
		vao.addVBO(uvVBO);
	}
	vao.prepare();
}

void Mesh::draw() {
	vao.draw();
}
