#ifndef __FLATSHADER_HPP
#define __FLATSHADER_HPP

#include "DemoTER/glwrapper/Shader.hpp"
#include "DemoTER/utils/Camera.hpp"

/**
* Classe correspondant � un shader sans lumieres et sans textures. Elle h�rite de la classe Shader.
*/
class FlatShader: public Shader {
	protected:
		/**
		* Initialise le tableau uniformLocations.
		* R�cup�re l'adresse correspondant � chaque uniform.
		*/
		virtual void fetchUniformLocations() override;

	public:
		/**
		* Constructeur.
		* Initialise le Shader. H�rite de Shader.
		*/
		FlatShader();

		/**
		* Envoie � la carte graphique les param�tres de la cam�ra.
		* @param camera La cam�ra en question.
		*/
		void setCamera(Camera *camera);

		/**
		* Envoie � la carte graphique la valeur de l'exposition.
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
