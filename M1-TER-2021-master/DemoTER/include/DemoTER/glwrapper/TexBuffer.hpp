#ifndef __TEXBUFFER_HPP
#define	__TEXBUFFER_HPP

#include "glad/glad.h"

/**
* Cette classe permet de définir les propritétés d'une texture. C'est une classe abstraite.
*/
class TexBuffer {
	protected:
		GLuint id;
		int width;
		int height;

	public:
		/**
		* Destructeur.
		* Détruit la texture.
		*/
		virtual ~TexBuffer();

		/**
		* Méthode virtuelle pure.
		* Permet de rendre la classe abstraite.
		*/
		virtual void bind(int unit = 0) = 0;
		/**
		* Récupère la largeur de la texture.
		* @return La largeur de la texture.
		*/
		int getWidth() const;
		/**
		* Récupère la hauteur de la texture.
		* @return La hauteur de la texture.
		*/
		int getHeight() const;
		/**
		* Récupère l'identifiant de la texture.
		* @return L'identifiant de la texture.
		*/
		GLuint getId();

		/**
		* Méthode virtuelle pure.
		* Change la taille du buffer
		*/
		virtual void setSize(int w, int h) = 0;
};

#endif
