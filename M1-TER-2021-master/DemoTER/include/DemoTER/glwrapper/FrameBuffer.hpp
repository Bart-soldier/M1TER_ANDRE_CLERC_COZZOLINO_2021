#ifndef __FRAMEBUFFER_HPP
#define	__FRAMEBUFFER_HPP

#include <memory>
#include "glad/glad.h"
#include "DemoTER/glwrapper/Texture.hpp"
#include "DemoTER/glwrapper/CubeMapTexture.hpp"
#include "DemoTER/glwrapper/DepthTexture.hpp"
#include "DemoTER/glwrapper/MSTexture.hpp"
#include "DemoTER/glwrapper/MSDepthTexture.hpp"

class FrameBuffer {
	private:
		static int const MAX_ATTACHMENT_COUNT = 6;

		GLuint id;
		std::shared_ptr<TexBuffer> textures[MAX_ATTACHMENT_COUNT];
		std::shared_ptr<TexBuffer> depthTexture;

	public:
		FrameBuffer();
		~FrameBuffer();

		/**
		* Attache une texture de couleur au framebuffer
		*/
		void setTexture(std::shared_ptr<Texture> &texture, int unit = 0);
		void setTexture(std::shared_ptr<MSTexture> &texture, int unit = 0);
		void setTexture(std::shared_ptr<CubeMapTexture> &texture, int unit = 0);
		std::shared_ptr<TexBuffer> getTexture(int unit);

		/**
		* Attache une texture de profondeur au framebuffer
		*/
		void setDepthTexture(std::shared_ptr<DepthTexture> &texture);
		void setDepthTexture(std::shared_ptr<MSDepthTexture> &texture);

		std::shared_ptr<TexBuffer> getDepthTexture();

		/**
		* Change le type d'attachement
		* @param unit, la texture
		* @param attachment, le type d'attachcement
		* @param mip, le niveau de mip
		*/
		void changeAttachment(int unit, GLenum attachment, unsigned int mip = 0);

		/**
		* Prépare le framebuffer pour qu'il soit utilisable, et vérifie qu'il est complet
		*/
		void prepare();

		void bind(int unit = 0);
		void bindWithSize(int width, int height);

		void unbind();
		/**
		* Copie une texture attachée dans le framebuffer par defaut (l'écran)
		* @param unit, la texture à copier
		* @param la méthode de sampling
		*/
		void blitToScreen(int unit = 0, GLenum filter = GL_NEAREST);
		/**
		* Copie une texture attachée dans un autre framebuffer
		* @param seflUnit, la texture à copier
		* @fb le framebuffer cible
		* @param la méthode de sampling
		*/
		void blitTo(int seflUnit, FrameBuffer *fb, GLenum filter = GL_NEAREST);
		/**
		* Change la taille de toutes les textures attachées
		*/
		void resizeAll(int width, int height);
};

#endif
