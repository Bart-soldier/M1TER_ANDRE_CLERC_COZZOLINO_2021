#ifndef __PBRSHADER_HPP
#define	__PBRSHADER_HPP

#include "DemoTER/glwrapper/Shader.hpp"
#include "DemoTER/glwrapper/Texture.hpp"
#include "DemoTER/utils/Camera.hpp"
#include "DemoTER/Mesh.hpp"
#include "DemoTER/Materials.hpp"
#include <vector>

/**
* Classe correspondant � un shader PBR. Elle h�rite de la classe Shader.
*/
class PBRShader: public Shader {
	protected:
		/**
		* Initialise le tableau uniformLocations.
		* R�cup�re l'adresse correspondant � chaque uniform.
		*/
		virtual void fetchUniformLocations() override;

	public:
		static int MAX_LIGHT_COUNT;

		/**
		* Constructeur.
		* Initialise le Shader PBR. H�rite de Shader.
		*/
		PBRShader();
		
		/**
		* Envoie � la carte graphique les param�tres de la cam�ra.
		* @param camera La cam�ra en question.
		*/
		void setCamera(Camera *camera);
		/**
		* Envoie � la carte graphique les param�tres des lumi�res.
		* @param lightPositions La position des lumi�res en question.
		* @param lightColors La couleur et la puissance des lumi�res en question.
		*/
		void setLights(std::vector<glm::vec3> &lightPositions, std::vector<glm::vec3> &lightColors);
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
		/**
		* Dessine un mod�le avec des textures associ�s.
		* @param mesh Le maillage de l'objet � dessiner.
		* @param material Les texures � associer � l'objet.
		* @param mat4x4 La position de l'objet.
		*/
		void render(Mesh *mesh, Materials::Material *material, glm::mat4x4 &transform);

		enum {
			A_POSITION = 0,
			A_NORMAL = 1,
			A_TANGENT = 2,
			A_UV = 3,


			U_MODEL = 0,
			U_PV = 1,

			U_CAM_POS = 2,

			U_LIGHT_POSITIONS = 3,
			U_LIGHT_COLORS = 4,

			U_GAMMA = 5,
			U_EXPOSURE = 6,
			
			U_ALBEDO = 7,
			U_NORMAL = 8,
			U_ROUGHNESS = 9,
			U_METALLIC = 10,
			U_AO = 11,

			U_IRRADIANCE = 12,
			U_PREFILTER = 13,
			U_BRDFLUT = 14, 


			T_ALBEDO = 0,
			T_NORMAL = 1,
			T_ROUGHNESS = 2,
			T_METALLIC = 3,
			T_AO = 4,

			T_IRRADIANCE = 5,
			T_PREFILTER = 6,
			T_BRDFLUT = 7
		}; /**< Enum. A : Attributs, U : Uniform, T : Textures. */
};

#endif
