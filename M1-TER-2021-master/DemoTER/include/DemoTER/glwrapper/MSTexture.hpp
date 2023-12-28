#ifndef __MSTEXTURE_HPP
#define	__MSTEXTURE_HPP

#include "DemoTER/glwrapper/TexBuffer.hpp"

/**
* Cette classe permet de représenter et de manipuler unr texture multisamplé. Elle hérite de TexBuffer.
*/
class MSTexture: public TexBuffer {
	private:
		int samples;
		bool hdr;

	public:

		/**
		* Constructeur.
		* Créer une texture en fonction des paramètres fournis.
		* @param w La largeur de la texture.
		* @param h La hauteur de la texture.
		*/
		MSTexture(int w, int h, int samples = 4, bool hdr = true);

		virtual void setSize(int w, int h) override;

		virtual void bind(int unit = 0) override;
};

#endif
