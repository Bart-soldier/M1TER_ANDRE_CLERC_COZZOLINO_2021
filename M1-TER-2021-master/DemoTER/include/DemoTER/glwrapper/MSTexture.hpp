#ifndef __MSTEXTURE_HPP
#define	__MSTEXTURE_HPP

#include "DemoTER/glwrapper/TexBuffer.hpp"

/**
* Cette classe permet de repr�senter et de manipuler unr texture multisampl�. Elle h�rite de TexBuffer.
*/
class MSTexture: public TexBuffer {
	private:
		int samples;
		bool hdr;

	public:

		/**
		* Constructeur.
		* Cr�er une texture en fonction des param�tres fournis.
		* @param w La largeur de la texture.
		* @param h La hauteur de la texture.
		*/
		MSTexture(int w, int h, int samples = 4, bool hdr = true);

		virtual void setSize(int w, int h) override;

		virtual void bind(int unit = 0) override;
};

#endif
