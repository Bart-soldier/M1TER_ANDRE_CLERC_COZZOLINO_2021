#ifndef __SHADER_HPP
#define	__SHADER_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

/**
* Classe générale de shader. Elle contient les paramètres nécessaire pour n'importe quel shader.
*/
class Shader {
	private:
		GLuint id;
		/**
		* Vérifie les erreurs de compilation.
		*/
		void checkCompileErrors(GLuint shader, std::string type);

	protected:
		GLuint *uniformLocations; /**< Tableau qui conserve, pour un program shader, l'adresse de toutes les variables uniformes. */
		/**
		* Appelle la fonction glGetUniformLocation(id, name).
		* Pour un program shader d'ID id, récupère l'adresse en fonction d'une chaîne de caractère.
		* @param name Nom de la variable à chercher.
		* @return Un entier qui sert de pointeur.
		*/
		GLuint queryUniformLocation(const char *name);
		/**
		* Méthode virtuelle pure.
		* Permet de rendre la classe abstraite.
		*/
		virtual void fetchUniformLocations() = 0;

	public:
		/**
		* Constructeur.
		* Récupère et compile le fragment et vertex shader afin de créer le program shader, tout en vérifiant les erreurs de compilation.
		* @param vertexPath Chemin vers le vertex shader
		* @param fragmentPath Chemin vers le fragment shader
		*/
		Shader(const char *vertexPath, const char *fragmentPath);
		/**
		* Destructeur
		*/
		virtual ~Shader();

		/**
		* Appelle la fonction glUseProgram(id).
		* Indique à OpenGL qu'on utilisera ce program shader pour dessiner.
		*/
		void bind() const;

		/**
		* Permet d'envoyer une valeur à la carte graphique, par l'intermédiaire du tableau uniformLocations.
		* @param uid L'entier d'uniformLocations défini par l'enum, correspondant à l'adresse de la variable dans la carte graphique.
		* @param value La valeur à envoyer, sous forme d'entier.
		*/
        void sendInt(GLuint uid, int value) const;
		/**
		* Permet d'envoyer une valeur à la carte graphique, par l'intermédiaire du tableau uniformLocations.
		* @param uid L'entier d'uniformLocations défini par l'enum, correspondant à l'adresse de la variable dans la carte graphique.
		* @param value La valeur à envoyer, sous forme de flotant.
		*/
        void sendFloat(GLuint uid, float value) const;
		/**
		* Permet d'envoyer une valeur à la carte graphique, par l'intermédiaire du tableau uniformLocations.
		* @param uid L'entier d'uniformLocations défini par l'enum, correspondant à l'adresse de la variable dans la carte graphique.
		* @param value La valeur à envoyer, sous forme de vecteur 2D.
		*/
        void sendVec2(GLuint uid, const glm::vec2 &value) const;
		/**
		* Permet d'envoyer une valeur à la carte graphique, par l'intermédiaire du tableau uniformLocations.
		* @param uid L'entier d'uniformLocations défini par l'enum, correspondant à l'adresse de la variable dans la carte graphique.
		* @param value La valeur à envoyer, sous forme de vecteur 3D.
		*/
        void sendVec3(GLuint uid, const glm::vec3 &value) const;
		/**
		* Permet d'envoyer une valeur à la carte graphique, par l'intermédiaire du tableau uniformLocations.
		* @param uid L'entier d'uniformLocations défini par l'enum, correspondant à l'adresse de la variable dans la carte graphique.
		* @param value La valeur à envoyer, sous forme de vecteur de vecteur 3D.
		*/
		void sendVec3(GLuint uid, const std::vector<glm::vec3> &values) const;
		/**
		* Permet d'envoyer une valeur à la carte graphique, par l'intermédiaire du tableau uniformLocations.
		* @param uid L'entier d'uniformLocations défini par l'enum, correspondant à l'adresse de la variable dans la carte graphique.
		* @param value La valeur à envoyer, sous forme de matrice 4D.
		*/
        void sendMat4(GLuint uid, const glm::mat4 &mat) const;
		/**
		* Permet d'envoyer une valeur à la carte graphique, par l'intermédiaire du tableau uniformLocations.
		* @param uid L'entier d'uniformLocations défini par l'enum, correspondant à l'adresse de la variable dans la carte graphique.
		* @param value La valeur à envoyer, sous forme de boolean.
		*/
		void sendBool(GLuint uid, const bool value) const;
};

#endif
