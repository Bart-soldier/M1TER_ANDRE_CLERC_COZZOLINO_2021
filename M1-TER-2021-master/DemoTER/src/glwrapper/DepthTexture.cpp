#include "DemoTER/glwrapper/DepthTexture.hpp"

DepthTexture::Options::Options(): wrapS{GL_CLAMP_TO_EDGE}, wrapT{GL_CLAMP_TO_EDGE}, minFilter{GL_LINEAR}, magFilter{GL_LINEAR} {}

DepthTexture::DepthTexture(int w, int h, Options options) {
	glGenTextures(1, &id);
	setOptions(options);
	setSize(w, h);
}

void DepthTexture::setSize(int w, int h) {
	width = w;
	height = h;

	bind();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, nullptr);
}

void DepthTexture::setOptions(Options options) {
	bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, options.wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, options.wrapT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, options.minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, options.magFilter);
}

void DepthTexture::bind(int unit) {
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, id);
}