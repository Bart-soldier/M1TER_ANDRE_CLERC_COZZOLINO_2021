#ifndef __VAO_HPP
#define	__VAO_HPP

#include <glad/glad.h>
#include <memory>
#include <vector>
#include "DemoTER/glwrapper/VBO.hpp"

/**
* Cette classe est un wrapper qui englobe les fonctionnalités liés aux VAO d'OpenGL.
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
		* Créer un VAO dans la carte graphique. Le mode de dessin par défaut est GL_TRIANGLES.
		*/
		VAO();
		/**
		* Destructeur.
		* Détruit le VAO de la carte graphique.
		*/
		~VAO();

		/**
		* Ajoute un VBO au vecteur de VBOs.
		* @param vbo VBO à ajouter.
		*/
		void addVBO(std::shared_ptr<VBO> vbo);
		/**
		* Redéfinit le mode de dessin du VAO.
		* @param mode Mode de dessin, sous forme d'une constante symbolique.
		*/
		void setDrawMode(GLuint mode);
		/**
		* Indique à la carte graphique d'utiliser ce VAO.
		*/
		void bind();
		/**
		* Indique à la carte graphique de ne plus utiliser ce VAO.
		*/
		void unbind();
		/**
		* Indique à la carte graphique d'enregistrer des instructions.
		* Pour chaque VBO, on indiquer à la carte graphique qu'il faut utiliser le VBO en question et à quel attribut du shader correspond ce VBO.
		*/
		void prepare();
		/**
		* Après avoir préparer tous les VBOs du VAO, exécute le shader avec les VBOs en données d'entrée.
		*/
		void draw();
};

#endif
