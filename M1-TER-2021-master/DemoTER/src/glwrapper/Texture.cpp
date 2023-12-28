#include "DemoTER/glwrapper/Texture.hpp"
#include "stbimage/stb_image.h"
#include <iostream>
#include <string>
#include "DemoTER/config.hpp"

Texture::Options::Options(): wrapS{GL_REPEAT}, wrapT{GL_REPEAT}, minFilter{GL_LINEAR_MIPMAP_LINEAR}, magFilter{GL_LINEAR} {}

Texture::Params::Params(): correctGamma{false}, hdr{false}, createMips{true} {}

Texture::Texture(const char *path, Texture::Params params, Options options) {
	glGenTextures(1, &id);

	setOptions(options);

	int textureNrChannels;
	std::cout << "Chargement de " << path << std::endl;

	unsigned char *data;
	stbi_set_flip_vertically_on_load(true);
	if(params.hdr) data = (unsigned char *) stbi_loadf(std::string(RESOURCES_DIRECTORY).append(path).c_str(), &width, &height, &textureNrChannels, 0);
	else data = stbi_load(std::string(RESOURCES_DIRECTORY).append(path).c_str(), &width, &height, &textureNrChannels, 0);

	GLenum format = GL_RGB;
	GLenum internalFormat = GL_RGBA;
	if(data) {
		if(params.correctGamma) {
			switch(textureNrChannels) {
				case 1: format = GL_RED; internalFormat = GL_RED; break;
				case 3: format = GL_RGB; internalFormat = GL_SRGB; break;
				case 4: format = GL_RGBA; internalFormat = GL_SRGB_ALPHA;
			}
		} else {
			switch(textureNrChannels) {
				case 1: format = GL_RED; internalFormat = GL_RED; break;
				case 3: format = GL_RGB; internalFormat = GL_RGB; break;
				case 4: format = GL_RGBA; internalFormat = GL_RGBA;
			}
		}

		GLenum dataType = GL_UNSIGNED_BYTE;
		if(params.hdr) {
			internalFormat = GL_RGB16F;
			dataType = GL_FLOAT;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, dataType, data);
		if(params.createMips) glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		std::cout << "Failed to load texture : " << path << std::endl;
	}

	parameters = params;

	stbi_image_free(data);
}

Texture::Texture(glm::vec3 color, Options options) {
	glGenTextures(1, &id);

	setOptions(options);

	width = 1;
	height = 1;

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_FLOAT, &color[0]);
}

Texture::Texture(int w, int h, Texture::Params params, Options options) {
	glGenTextures(1, &id);
	setOptions(options);
	parameters = params;
	setSize(w, h);
}

void Texture::setSize(int w, int h) {
	width = w;
	height = h;

	bind();

	GLenum internalFormat = GL_RGB;
	GLenum dataType = GL_UNSIGNED_BYTE;
	if(parameters.hdr) {
		internalFormat = GL_RGB16F;
		dataType = GL_FLOAT;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, GL_RGB, dataType, nullptr);
}

void Texture::setOptions(Options options) {
	bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, options.wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, options.wrapT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, options.minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, options.magFilter);
}

void Texture::bind(int unit) {
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, id);
}
