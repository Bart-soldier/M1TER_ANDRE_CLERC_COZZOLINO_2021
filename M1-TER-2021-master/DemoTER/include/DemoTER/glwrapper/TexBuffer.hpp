#ifndef __TEXBUFFER_HPP
#define	__TEXBUFFER_HPP

#include "glad/glad.h"

/**
* Cette classe permet de d�finir les proprit�t�s d'une texture. C'est une classe abstraite.
*/
class TexBuffer {
	protected:
		GLuint id;
		int width;
		int height;

	public:
		/**
		* Destructeur.
		* D�truit la texture.
		*/
		virtual ~TexBuffer();

		/**
		* M�thode virtuelle pure.
		* Permet de rendre la classe abstraite.
		*/
		virtual void bind(int unit = 0) = 0;
		/**
		* R�cup�re la largeur de la texture.
		* @return La largeur de la texture.
		*/
		int getWidth() const;
		/**
		* R�cup�re la hauteur de la texture.
		* @return La hauteur de la texture.
		*/
		int getHeight() const;
		/**
		* R�cup�re l'identifiant de la texture.
		* @return L'identifiant de la texture.
		*/
		GLuint getId();

		/**
		* M�thode virtuelle pure.
		* Change la taille du buffer
		*/
		virtual void setSize(int w, int h) = 0;
};

#endif
