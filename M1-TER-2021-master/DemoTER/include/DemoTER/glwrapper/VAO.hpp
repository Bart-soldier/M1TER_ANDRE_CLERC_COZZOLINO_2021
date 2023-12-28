#ifndef __VAO_HPP
#define	__VAO_HPP

#include <glad/glad.h>
#include <memory>
#include <vector>
#include "DemoTER/glwrapper/VBO.hpp"

/**
* Cette classe est un wrapper qui englobe les fonctionnalit�s li�s aux VAO d'OpenGL.
*/
class VAO {
	private:
		GLuint id;
		std::vector<std::shared_ptr<VBO>> vbos;
		GLuint drawMode;
		int length;

	public:
		/**
		* Constructeur.
		* Cr�er un VAO dans la carte graphique. Le mode de dessin par d�faut est GL_TRIANGLES.
		*/
		VAO();
		/**
		* Destructeur.
		* D�truit le VAO de la carte graphique.
		*/
		~VAO();

		/**
		* Ajoute un VBO au vecteur de VBOs.
		* @param vbo VBO � ajouter.
		*/
		void addVBO(std::shared_ptr<VBO> vbo);
		/**
		* Red�finit le mode de dessin du VAO.
		* @param mode Mode de dessin, sous forme d'une constante symbolique.
		*/
		void setDrawMode(GLuint mode);
		/**
		* Indique � la carte graphique d'utiliser ce VAO.
		*/
		void bind();
		/**
		* Indique � la carte graphique de ne plus utiliser ce VAO.
		*/
		void unbind();
		/**
		* Indique � la carte graphique d'enregistrer des instructions.
		* Pour chaque VBO, on indiquer � la carte graphique qu'il faut utiliser le VBO en question et � quel attribut du shader correspond ce VBO.
		*/
		void prepare();
		/**
		* Apr�s avoir pr�parer tous les VBOs du VAO, ex�cute le shader avec les VBOs en donn�es d'entr�e.
		*/
		void draw();
};

#endif
