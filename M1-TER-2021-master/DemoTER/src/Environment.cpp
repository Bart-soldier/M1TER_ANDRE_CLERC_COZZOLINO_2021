#include "DemoTER/Environment.hpp"
#include "DemoTER/glwrapper/Texture.hpp"
#include "DemoTER/glwrapper/FrameBuffer.hpp"
#include "DemoTER/utils/Parser.hpp"
#include "DemoTER/glwrapper/VAO.hpp"
#include "glm/mat4x4.hpp"
#include <glm/gtc/matrix_transform.hpp>

Environment::EnvShader::EnvShader(): Shader{"shaders/env/rectToCube.vert", "shaders/env/rectToCube.frag"} {
	fetchUniformLocations();
}

void Environment::EnvShader::fetchUniformLocations() {
	uniformLocations = new GLuint[3];
	uniformLocations[0] = queryUniformLocation("projection");
	uniformLocations[1] = queryUniformLocation("view");
	uniformLocations[2] = queryUniformLocation("equirectangularMap");
}

Environment::IrradianceShader::IrradianceShader(): Shader{"shaders/env/irradiance.vert", "shaders/env/irradiance.frag"} {
	fetchUniformLocations();
}

void Environment::IrradianceShader::fetchUniformLocations() {
	uniformLocations = new GLuint[3];
	uniformLocations[0] = queryUniformLocation("projection");
	uniformLocations[1] = queryUniformLocation("view");
	uniformLocations[2] = queryUniformLocation("environmentMap");
}

Environment::PrefilterShader::PrefilterShader(): Shader{"shaders/env/prefilter.vert", "shaders/env/prefilter.frag"} {
	fetchUniformLocations();
}

void Environment::PrefilterShader::fetchUniformLocations() {
	uniformLocations = new GLuint[5];
	uniformLocations[0] = queryUniformLocation("projection");
	uniformLocations[1] = queryUniformLocation("view");
	uniformLocations[2] = queryUniformLocation("environmentMap");
	uniformLocations[3] = queryUniformLocation("roughness");
	uniformLocations[4] = queryUniformLocation("resolution");
}

Environment::BRDFShader::BRDFShader(): Shader{"shaders/env/brdf.vert", "shaders/env/brdf.frag"} {
	fetchUniformLocations();
}

void Environment::BRDFShader::fetchUniformLocations() {
	uniformLocations = new GLuint[0];
}

////////////////

std::shared_ptr<Environment::Result> Environment::createIBL(const char *path) {
	std::shared_ptr<Environment::Result> result = std::make_shared<Environment::Result>();

	Texture::Params texParams;
	texParams.correctGamma = false;
	texParams.createMips = false;
	texParams.hdr = true;

	Texture::Options texOptions;
	texOptions.magFilter = GL_LINEAR;
	texOptions.minFilter = GL_LINEAR;

	Texture env{path, texParams, texOptions};

	FrameBuffer fbo{};
	
	VAO vao{};
	std::shared_ptr<Parser::Result> r = Parser::loadObj("meshs/invertCube.obj");
	std::shared_ptr<VBO> posVbo = std::make_shared<VBO>(r->vertex, 0);
	vao.addVBO(posVbo);
	vao.prepare();

	glm::mat4 captureProjection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10.0f);
	glm::mat4 captureViews[] = {
	   glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
	   glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
	   glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f)),
	   glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec3(0.0f,  0.0f, -1.0f)),
	   glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
	   glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f))
	};

	////////////////////////////////////////////////////////////////////////////////
	// Creation de la skybox

	CubeMapTexture::Options cubmapOpts;
	cubmapOpts.minFilter = GL_LINEAR_MIPMAP_LINEAR;

	result->skybox = std::make_shared<CubeMapTexture>(1024, 1024, true, cubmapOpts);
	fbo.setTexture(result->skybox, 0);
	fbo.prepare();

	Environment::EnvShader shader;
	shader.bind();
	fbo.bind();

	shader.sendMat4(0, captureProjection);
	shader.sendInt(2, 0);
	env.bind();

	for(unsigned int i = 0; i < 6; ++i) {
		shader.sendMat4(1, captureViews[i]);
		fbo.changeAttachment(0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i);

		vao.draw();
	}

	result->skybox->createMips();

	fbo.unbind();


	////////////////////////////////////////////////////////////////////////////////
	// Creation de l'irradiance

	result->irradiance = std::make_shared<CubeMapTexture>(32, 32, true);
	fbo.setTexture(result->irradiance, 0);
	fbo.prepare();

	Environment::IrradianceShader irShader;

	irShader.bind();
	fbo.bind();
	irShader.sendMat4(0, captureProjection);
	irShader.sendInt(2, 0);
	result->skybox->bind();

	for(unsigned int i = 0; i < 6; ++i) {
		irShader.sendMat4(1, captureViews[i]);
		fbo.changeAttachment(0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i);

		vao.draw();
	}

	fbo.unbind();

	////////////////////////////////////////////////////////////////////////////////
	// Creation de prefilter

	result->prefilter = std::make_shared<CubeMapTexture>(128, 128, true, cubmapOpts);
	result->prefilter->createMips();
	fbo.setTexture(result->prefilter, 0);
	fbo.prepare();

	Environment::PrefilterShader prefilterShader;
	prefilterShader.bind();
	prefilterShader.sendMat4(0, captureProjection);
	prefilterShader.sendInt(2, 0);
	prefilterShader.sendFloat(4, result->skybox->getWidth());
	result->skybox->bind();

	unsigned int maxMipLevels = 5;
	for(unsigned int mip = 0; mip < maxMipLevels; ++mip) {
		// reisze framebuffer according to mip-level size.
		unsigned int mipWidth = result->prefilter->getWidth() * std::pow(0.5, mip);
		unsigned int mipHeight = result->prefilter->getHeight() * std::pow(0.5, mip);
		fbo.bindWithSize(mipWidth, mipHeight);

		float roughness = (float)mip / (float)(maxMipLevels - 1);
		prefilterShader.sendFloat(3, roughness);
		for(unsigned int i = 0; i < 6; ++i) {
			prefilterShader.sendMat4(1, captureViews[i]);
			fbo.changeAttachment(0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, mip);

			vao.draw();
		}
	}

	fbo.unbind();

	return result;
}

std::shared_ptr<Texture> Environment::createBRDFLUT() {
	////////////////////////////////////////////////////////////////////////////////
	// Creation de brdfLUT

	Texture::Options brdfTexOpts;
	brdfTexOpts.wrapS = GL_CLAMP_TO_EDGE;
	brdfTexOpts.wrapT = GL_CLAMP_TO_EDGE;
	brdfTexOpts.minFilter = GL_LINEAR;
	brdfTexOpts.magFilter = GL_LINEAR;

	Texture::Params brdfTexParams;
	brdfTexParams.correctGamma = false;
	brdfTexParams.createMips = false;
	brdfTexParams.hdr = false;

	std::shared_ptr<Texture> brdfLUT = std::make_shared<Texture>(512, 512, brdfTexParams, brdfTexOpts);

	FrameBuffer fbo{};
	fbo.setTexture(brdfLUT, 0);
	fbo.prepare();

	VAO triangleVAO;
	std::shared_ptr<VBO> trianglePos = std::make_shared<VBO>(
		std::vector<glm::vec3>{
			glm::vec3(-1, -1, 0),
			glm::vec3(3, -1, 0),
			glm::vec3(-1, 3, 0)
	}, 0);
	triangleVAO.addVBO(trianglePos);
	triangleVAO.prepare();

	Environment::BRDFShader brdfShader;
	fbo.bind();
	brdfShader.bind();
	triangleVAO.draw();
	fbo.unbind();

	return brdfLUT;
}
