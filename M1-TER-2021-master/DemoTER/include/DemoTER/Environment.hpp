#ifndef __ENVIRONMENT_HPP
#define	__ENVIRONMENT_HPP

#include <memory>
#include "DemoTER/glwrapper/CubeMapTexture.hpp"
#include "DemoTER/glwrapper/Texture.hpp"
#include "DemoTER/glwrapper/Shader.hpp"

class Environment {
	public:
		struct Result {
			std::shared_ptr<CubeMapTexture> skybox;
			std::shared_ptr<CubeMapTexture> irradiance;
			std::shared_ptr<CubeMapTexture> prefilter;
		};

	private:
		class EnvShader: public Shader {
			protected:
				virtual void fetchUniformLocations() override;

			public:
				EnvShader();
		};

		class IrradianceShader: public Shader {
			protected:
				virtual void fetchUniformLocations() override;

			public:
				IrradianceShader();
		};

		class PrefilterShader: public Shader {
			protected:
				virtual void fetchUniformLocations() override;

			public:
				PrefilterShader();
		};

		class BRDFShader: public Shader {
			protected:
				virtual void fetchUniformLocations() override;

			public:
				BRDFShader();
		};

	public:
		/**
		* Créer les cubemaps de la skybox, la lumière ambiant et spéculaire de l'environnement
		* @param le chemin vers une image equirectangle
		*/
		static std::shared_ptr<Result> createIBL(const char *path);
		static std::shared_ptr<Texture> createBRDFLUT();
};

#endif
