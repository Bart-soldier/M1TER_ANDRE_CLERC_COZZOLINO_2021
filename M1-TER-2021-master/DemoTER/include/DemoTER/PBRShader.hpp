#ifndef __PBRSHADER_HPP
#define	__PBRSHADER_HPP

#include "DemoTER/glwrapper/Shader.hpp"
#include "DemoTER/glwrapper/Texture.hpp"
#include "DemoTER/utils/Camera.hpp"
#include "DemoTER/Mesh.hpp"
#include "DemoTER/Materials.hpp"
#include <vector>

/**
* Classe correspondant à un shader PBR. Elle hérite de la classe Shader.
*/
class PBRShader: public Shader {
	protected:
		/**
		* Initialise le tableau uniformLocations.
		* Récupère l'adresse correspondant à chaque uniform.
		*/
		virtual void fetchUniformLocations() override;

	public:
		static int MAX_LIGHT_COUNT;

		/**
		* Constructeur.
		* Initialise le Shader PBR. Hérite de Shader.
		*/
		PBRShader();
		
		/**
		* Envoie à la carte graphique les paramètres de la caméra.
		* @param camera La caméra en question.
		*/
		void setCamera(Camera *camera);
		/**
		* Envoie à la carte graphique les paramètres des lumières.
		* @param lightPositions La position des lumières en question.
		* @param lightColors La couleur et la puissance des lumières en question.
		*/
		void setLights(std::vector<glm::vec3> &lightPositions, std::vector<glm::vec3> &lightColors);
		/**
		* Envoie à la carte graphique la valeur de l'exposition.
		* @param e La valeur de l'exposition.
		*/
		void setExposure(float e);
		/**
		* Envoie à la carte graphique la valeur gamma.
		* @param g La valeur gamma.
		*/
		void setGamma(float g);
		/**
		* Dessine un modèle avec des textures associés.
		* @param mesh Le maillage de l'objet à dessiner.
		* @param material Les texures à associer à l'objet.
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
