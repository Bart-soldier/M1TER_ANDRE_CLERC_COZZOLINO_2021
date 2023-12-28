#ifndef __TEXTURE_HPP
#define	__TEXTURE_HPP

#include "DemoTER/glwrapper/TexBuffer.hpp"
#include "glm/vec3.hpp"

/**
* Cette classe permet de représenter et de manipuler les textures. C'est une classe abstraite. Elle hérite de TexBuffer.
*/
class Texture: public TexBuffer {
	public:
		struct Params {
			/**
			* Constructeur de la structure.
			* Définit par défaut la correction du gamma à faux, l'hdr à faux et le MIP mapping à vrai.
			*/
			Params();

			bool correctGamma;
			bool hdr;
			bool createMips;
		}; /**< Une structure pour les paramètres. Ces derniers correspondent à la correction gamma, l'hdr et le MIP mapping. */

		struct Options {
			/**
			* Constructeur de la structure.
			* Définit par défaut le wrapping sur la coordonnée s à GL_REPEAT, celui sur la coordonnée t à GL_REPEAT,
			* le Min Filter GL_LINEAR_MIPMAP_LINEAR et le Mag Filter à GL_LINEAR.
			*/
			Options();

			GLenum wrapS;
			GLenum wrapT;
			GLenum minFilter;
			GLenum magFilter;
		}; /**< Une structure pour les options. Ces derniers correspondent au paramètres de wrapping de texture sur s et t, et si
		   la pixel appliqué sur la texture est plus petit ou plus grande que la texture même. */

		/**
		* Constructeur.
		* Créer une texture en fonction des paramètres fournis.
		* @param path Pointeur indiquant le chemin vers la texture.
		* @param params Les paramètres de la texture, sinon ils correspondront aux valeurs du constructeur associé par défaut.
		* @param options Les options de la texture, sinon ils correspondront aux valeurs du constructeur associé par défaut.
		*/
		Texture(const char *path, Params params = {}, Options options = {});
		/**
		* Constructeur.
		* Créer une texture en fonction des paramètres fournis.
		* @param color Indique une couleur RGB pour la texture, sous forme de vecteur 3D.
		* @param options Les options de la texture, sinon ils correspondront aux valeurs du constructeur associé par défaut.
		*/
		Texture(glm::vec3 color, Options options = {});
		/**
		* Constructeur.
		* Créer une texture en fonction des paramètres fournis.
		* @param w La largeur de la texture.
		* @param h La hauteur de la texture.
		* @param params Les paramètres de la texture, sinon ils correspondront aux valeurs du constructeur associé par défaut.
		* @param options Les options de la texture, sinon ils correspondront aux valeurs du constructeur associé par défaut.
		*/
		Texture(int w, int h, Params params = {}, Options options = {});

		/**
		* Permet de redéfinir les options d'un texture.
		* @param options Les nouvelles options à définir.
		*/
		void setOptions(Options options);

		/**
		* Change la taille de la texture
		* @param w La largeur de la texture.
		* @param h La hauteur de la texture.
		*/
		virtual void setSize(int w, int h) override;

		virtual void bind(int unit = 0) override;

	private:
		Params parameters;
};

#endif
