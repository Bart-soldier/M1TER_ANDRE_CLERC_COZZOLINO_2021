#ifndef __BLOOMFILTER_HPP
#define	__BLOOMFILTER_HPP

#include <memory>
#include "DemoTER/glwrapper/Shader.hpp"
#include "DemoTER/glwrapper/FrameBuffer.hpp"
#include "DemoTER/glwrapper/Texture.hpp"
#include "DemoTER/glwrapper/MSTexture.hpp"
#include "DemoTER/glwrapper/VAO.hpp"

class BloomFilter {
	private:
		class BloomShader: public Shader {
			protected:
				virtual void fetchUniformLocations() override;

			public:
				BloomShader(const char *vs, const char *fs);
		};

		class TransferShader: public Shader {
		protected:
			virtual void fetchUniformLocations() override;

		public:
			TransferShader();
		};

		bool fbSelector;
		std::unique_ptr<FrameBuffer> fbPingPong5[2];
		std::unique_ptr<BloomShader> bloomShader5;

		std::unique_ptr<FrameBuffer> fbPingPong9[2];
		std::unique_ptr<BloomShader> bloomShader9;

		std::unique_ptr<FrameBuffer> fbPingPong11[2];
		std::unique_ptr<BloomShader> bloomShader11;

		std::unique_ptr<TransferShader> transferShader;

		std::unique_ptr<VAO> triangleVAO;

	public:
		BloomFilter(int w, int h);

		struct Result {
			std::shared_ptr<TexBuffer> b5;
			std::shared_ptr<TexBuffer> b9;
			std::shared_ptr<TexBuffer> b11;
		};

		/**
		* Exécute l'algorithme du bloom.
		* @param inFb, le framebuffer avec la texture à bloomer
		* @param unit, l'index de la texture du framebuffer
		* @return retourne 3 textures (pour visualisation), utiliser b5 pour le rendu final
		*/
		Result apply(FrameBuffer *inFb, int unit);
		/**
		* Met à jour la taille des framebuffers du bloom
		*/
		void resize(int w, int h);
};

#endif
