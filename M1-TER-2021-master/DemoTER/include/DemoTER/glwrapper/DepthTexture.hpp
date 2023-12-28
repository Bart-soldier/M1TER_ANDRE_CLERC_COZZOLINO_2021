#ifndef __DEPTHTEXTURE_HPP
#define	__DEPTHTEXTURE_HPP

#include "DemoTER/glwrapper/TexBuffer.hpp"

/**
* Cette classe permet de représenter et de manipuler les textures. C'est une classe abstraite. Elle hérite de TexBuffer.
*/
class DepthTexture: public TexBuffer {
public:
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
	* @param w La largeur de la texture.
	* @param h La hauteur de la texture.
	* @param options Les options de la texture, sinon ils correspondront aux valeurs du constructeur associé par défaut.
	*/
	DepthTexture(int w, int h, Options options = {});

	/**
	* Permet de redéfinir les options d'un texture.
	* @param options Les nouvelles options à définir.
	*/
	void setOptions(Options options);

	virtual void setSize(int w, int h) override;

	virtual void bind(int unit = 0) override;
};

#endif
