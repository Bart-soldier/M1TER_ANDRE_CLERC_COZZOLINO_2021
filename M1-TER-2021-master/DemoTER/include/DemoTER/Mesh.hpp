#ifndef __MESH_HPP
#define	__MESH_HPP

#include "DemoTER/glwrapper/VAO.hpp"

/**
* Cette classe permet de représenter et de manipuler les maillages. Elle hértie de la classe Transform.
*/
class Mesh {
	private:
		VAO vao; /**< Un VAO. VAO du maillage en question. */

	public:
		/**
		* Constructeur.
		* Pour un chemin vers un maillage donné en fichier .obj, créer les VBOs associés (sommets, normales, tangentes et UV s'ils
		* existent, afin de former le VAO.
		* @param path Pointeur indiquant le chemin vers le maillage, sous forme de fichier .obj.
		*/
		Mesh(const char *path);
		/**
		* Dessine le maillage, par l'intermédiaire du VAO.
		*/
		void draw();
};

#endif
