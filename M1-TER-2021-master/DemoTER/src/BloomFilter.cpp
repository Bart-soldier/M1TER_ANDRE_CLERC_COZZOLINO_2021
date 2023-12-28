#include "DemoTER/BloomFilter.hpp"
#include "DemoTER/glwrapper/Display.hpp"

BloomFilter::BloomShader::BloomShader(const char *vs, const char *fs): Shader{vs, fs} {
	fetchUniformLocations();

	sendInt(2, 0);
}

void BloomFilter::BloomShader::fetchUniformLocations() {
	uniformLocations = new GLuint[3];
	uniformLocations[0] = queryUniformLocation("horizontal");
	uniformLocations[1] = queryUniformLocation("size");
	uniformLocations[2] = queryUniformLocation("tex");
}

BloomFilter::TransferShader::TransferShader(): Shader{"shaders/bloom/transfer.vert", "shaders/bloom/transfer.frag"} {
	fetchUniformLocations();
	sendInt(0, 0);
}

void BloomFilter::TransferShader::fetchUniformLocations() {
	uniformLocations = new GLuint[1];
	uniformLocations[0] = 0;
}

////////////////////////////////////////////////////////////////

BloomFilter::BloomFilter(int w, int h) {
	Texture::Params params;
	params.correctGamma = false;
	params.createMips = false;
	params.hdr = true;

	Texture::Options opts;
	opts.magFilter = GL_LINEAR;
	opts.minFilter = GL_LINEAR;
	opts.wrapS = GL_CLAMP_TO_EDGE;
	opts.wrapT = GL_CLAMP_TO_EDGE;

	bloomShader5 = std::make_unique<BloomShader>("shaders/bloom/bloom5.vert", "shaders/bloom/bloom5.frag");
	for(int i = 0; i < 2; ++i) {
		fbPingPong5[i] = std::make_unique<FrameBuffer>();
		fbPingPong5[i]->setTexture(std::make_shared<Texture>(w / 4, h / 4, params, opts));
		fbPingPong5[i]->prepare();
		fbPingPong5[i]->unbind();
	}

	bloomShader9 = std::make_unique<BloomShader>("shaders/bloom/bloom9.vert", "shaders/bloom/bloom9.frag");
	for(int i = 0; i < 2; ++i) {
		fbPingPong9[i] = std::make_unique<FrameBuffer>();
		fbPingPong9[i]->setTexture(std::make_shared<Texture>(w / 8, h / 8, params, opts));
		fbPingPong9[i]->prepare();
		fbPingPong9[i]->unbind();
	}

	bloomShader11 = std::make_unique<BloomShader>("shaders/bloom/bloom11.vert", "shaders/bloom/bloom11.frag");
	for(int i = 0; i < 2; ++i) {
		fbPingPong11[i] = std::make_unique<FrameBuffer>();
		fbPingPong11[i]->setTexture(std::make_shared<Texture>(w / 16, h / 16, params, opts));
		fbPingPong11[i]->prepare();
		fbPingPong11[i]->unbind();
	}


	transferShader = std::make_unique<TransferShader>();

	fbSelector = 0;

	
	triangleVAO = std::make_unique<VAO>();
	std::shared_ptr<VBO> trianglePos = std::make_shared<VBO>(
		std::vector<glm::vec3>{
			glm::vec3(-1, -1, 0),
			glm::vec3(3, -1, 0),
			glm::vec3(-1, 3, 0)
	}, 0);
	triangleVAO->addVBO(trianglePos);
	triangleVAO->prepare();
}

BloomFilter::Result BloomFilter::apply(FrameBuffer *inFb, int unit) {
	Display *d = Display::getInstance();

	Result result;

	fbSelector = 0;
	inFb->blitTo(unit, fbPingPong5[fbSelector].get(), GL_LINEAR);
	fbPingPong5[fbSelector]->blitTo(unit, fbPingPong9[fbSelector].get(), GL_LINEAR);
	fbPingPong9[fbSelector]->blitTo(unit, fbPingPong11[fbSelector].get(), GL_LINEAR);

	
	/////////////////////
	bloomShader11->bind();
	int width = fbPingPong11[fbSelector]->getTexture(0)->getWidth();
	int height = fbPingPong11[fbSelector]->getTexture(0)->getHeight();

	for(int i = 0; i < 2; ++i) {
		fbPingPong11[!fbSelector]->bind(0);
		bloomShader11->sendBool(0, fbSelector);
		bloomShader11->sendFloat(1, fbSelector ? width : height);
		fbPingPong11[fbSelector]->getTexture(0)->bind(0);
		triangleVAO->draw();
		fbSelector = !fbSelector;
	}

	result.b11 = fbPingPong11[fbSelector]->getTexture(0);

	/////////////////////
	fbSelector = 0;

	transferShader->bind();
	fbPingPong9[fbSelector]->bind(0);
	result.b11->bind(0);
	d->blenFunc(GL_ONE, GL_ONE);
	triangleVAO->draw();
	d->blenFunc(GL_ONE, GL_ZERO);


	bloomShader9->bind();
	width = fbPingPong9[fbSelector]->getTexture(0)->getWidth();
	height = fbPingPong9[fbSelector]->getTexture(0)->getHeight();

	for(int i = 0; i < 2; ++i) {
		fbPingPong9[!fbSelector]->bind(0);
		bloomShader9->sendBool(0, fbSelector);
		bloomShader9->sendFloat(1, fbSelector ? width : height);
		fbPingPong9[fbSelector]->getTexture(0)->bind(0);
		triangleVAO->draw();
		fbSelector = !fbSelector;
	}

	result.b9 = fbPingPong9[fbSelector]->getTexture(0);

	/////////////////////
	fbSelector = 0;

	transferShader->bind();
	fbPingPong5[fbSelector]->bind(0);
	result.b9->bind(0);
	d->blenFunc(GL_ONE, GL_ONE);
	triangleVAO->draw();
	d->blenFunc(GL_ONE, GL_ZERO);

	bloomShader5->bind();
	width = fbPingPong5[fbSelector]->getTexture(0)->getWidth();
	height = fbPingPong5[fbSelector]->getTexture(0)->getHeight();

	for(int i = 0; i < 2; ++i) {
		fbPingPong5[!fbSelector]->bind(0);
		bloomShader5->sendBool(0, fbSelector);
		bloomShader5->sendFloat(1, fbSelector ? width : height);
		fbPingPong5[fbSelector]->getTexture(0)->bind(0);
		triangleVAO->draw();
		fbSelector = !fbSelector;
	}

	result.b5 = fbPingPong5[fbSelector]->getTexture(0);

	return result;
}

void BloomFilter::resize(int w, int h) {
	for(int i = 0; i < 2; ++i) {
		fbPingPong5[i]->resizeAll(w / 4, h / 4);
		fbPingPong9[i]->resizeAll(w / 8, h / 8);
		fbPingPong11[i]->resizeAll(w / 16, h / 16);
	}
}
