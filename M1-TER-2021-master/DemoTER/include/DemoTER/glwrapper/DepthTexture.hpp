#ifndef __DEPTHTEXTURE_HPP
#define	__DEPTHTEXTURE_HPP

#include "DemoTER/glwrapper/TexBuffer.hpp"

/**
* Cette classe permet de repr�senter et de manipuler les textures. C'est une classe abstraite. Elle h�rite de TexBuffer.
*/
class DepthTexture: public TexBuffer {
public:
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
	* @param w La largeur de la texture.
	* @param h La hauteur de la texture.
	* @param options Les options de la texture, sinon ils correspondront aux valeurs du constructeur associ� par d�faut.
	*/
	DepthTexture(int w, int h, Options options = {});

	/**
	* Permet de red�finir les options d'un texture.
	* @param options Les nouvelles options � d�finir.
	*/
	void setOptions(Options options);

	virtual void setSize(int w, int h) override;

	virtual void bind(int unit = 0) override;
};

#endif
