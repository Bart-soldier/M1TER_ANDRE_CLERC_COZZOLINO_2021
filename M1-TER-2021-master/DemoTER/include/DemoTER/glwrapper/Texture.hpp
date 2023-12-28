#ifndef __TEXTURE_HPP
#define	__TEXTURE_HPP

#include "DemoTER/glwrapper/TexBuffer.hpp"
#include "glm/vec3.hpp"

/**
* Cette classe permet de repr�senter et de manipuler les textures. C'est une classe abstraite. Elle h�rite de TexBuffer.
*/
class Texture: public TexBuffer {
	public:
		struct Params {
			/**
			* Constructeur de la structure.
			* D�finit par d�faut la correction du gamma � faux, l'hdr � faux et le MIP mapping � vrai.
			*/
			Params();

			bool correctGamma;
			bool hdr;
			bool createMips;
		}; /**< Une structure pour les param�tres. Ces derniers correspondent � la correction gamma, l'hdr et le MIP mapping. */

		struct Options {
			/**
			* Constructeur de la structure.
			* D�finit par d�faut le wrapping sur la coordonn�e s � GL_REPEAT, celui sur la coordonn�e t � GL_REPEAT,
			* le Min Filter GL_LINEAR_MIPMAP_LINEAR et le Mag Filter � GL_LINEAR.
			*/
			Options();

			GLenum wrapS;
			GLenum wrapT;
			GLenum minFilter;
			GLenum magFilter;
		}; /**< Une structure pour les options. Ces derniers correspondent au param�tres de wrapping de texture sur s et t, et si
		   la pixel appliqu� sur la texture est plus petit ou plus grande que la texture m�me. */

		/**
		* Constructeur.
		* Cr�er une texture en fonction des param�tres fournis.
		* @param path Pointeur indiquant le chemin vers la texture.
		* @param params Les param�tres de la texture, sinon ils correspondront aux valeurs du constructeur associ� par d�faut.
		* @param options Les options de la texture, sinon ils correspondront aux valeurs du constructeur associ� par d�faut.
		*/
		Texture(const char *path, Params params = {}, Options options = {});
		/**
		* Constructeur.
		* Cr�er une texture en fonction des param�tres fournis.
		* @param color Indique une couleur RGB pour la texture, sous forme de vecteur 3D.
		* @param options Les options de la texture, sinon ils correspondront aux valeurs du constructeur associ� par d�faut.
		*/
		Texture(glm::vec3 color, Options options = {});
		/**
		* Constructeur.
		* Cr�er une texture en fonction des param�tres fournis.
		* @param w La largeur de la texture.
		* @param h La hauteur de la texture.
		* @param params Les param�tres de la texture, sinon ils correspondront aux valeurs du constructeur associ� par d�faut.
		* @param options Les options de la texture, sinon ils correspondront aux valeurs du constructeur associ� par d�faut.
		*/
		Texture(int w, int h, Params params = {}, Options options = {});

		/**
		* Permet de red�finir les options d'un texture.
		* @param options Les nouvelles options � d�finir.
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
