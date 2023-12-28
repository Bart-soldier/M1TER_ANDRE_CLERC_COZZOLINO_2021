#ifndef __SKYBOXSHADER_HPP
#define	__SKYBOXSHADER_HPP

#include "DemoTER/glwrapper/Shader.hpp"
#include "DemoTER/utils/Camera.hpp"

/**
* Classe correspondant � un shader permettant d'afficher une texture d'environnement (cubemap). Elle h�rite de la classe Shader.
*/
class SkyboxShader: public Shader {
	protected:
		virtual void fetchUniformLocations() override;

	public:
		SkyboxShader();

		/**
		* Envoie � la carte graphique les param�tres de la cam�ra.
		* @param camera La cam�ra en question.
		*/
		void setCamera(Camera *camare);
		/**
		* Envoie � la carte graphique la valeur de l'exposition.
		* @param e La valeur de l'exposition.
		*/
		void setExposure(float e);
		/**
		* Envoie � la carte graphique la valeur gamma.
		* @param g La valeur gamma.
		*/
		void setGamma(float g);

		enum {
			A_POSITION = 0,

			U_VIEW = 0,
			U_PROJECTION = 1,
			U_EXPOSURE = 2,
			U_GAMMA = 3
		};
};

#endif
