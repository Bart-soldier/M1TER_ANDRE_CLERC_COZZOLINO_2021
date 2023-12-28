#ifndef __FLATSHADER_HPP
#define __FLATSHADER_HPP

#include "DemoTER/glwrapper/Shader.hpp"
#include "DemoTER/utils/Camera.hpp"

/**
* Classe correspondant à un shader sans lumieres et sans textures. Elle hérite de la classe Shader.
*/
class FlatShader: public Shader {
	protected:
		/**
		* Initialise le tableau uniformLocations.
		* Récupère l'adresse correspondant à chaque uniform.
		*/
		virtual void fetchUniformLocations() override;

	public:
		/**
		* Constructeur.
		* Initialise le Shader. Hérite de Shader.
		*/
		FlatShader();

		/**
		* Envoie à la carte graphique les paramètres de la caméra.
		* @param camera La caméra en question.
		*/
		void setCamera(Camera *camera);

		/**
		* Envoie à la carte graphique la valeur de l'exposition.
		* @param e La valeur de l'exposition.
		*/
		void setExposure(float e);

		enum {
			A_POSITION = 0,

			U_MODEL = 0,
			U_PV = 1,
			U_COLOR = 2,
			U_EXPOSURE = 4,

		}; /**< Enum. A : Attributs, U : Uniform */
};

#endif
