#ifndef __VBO_HPP
#define	__VBO_HPP

#include <glad/glad.h>
#include <vector>
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

/**
* Cette classe est un wrapper qui englobe les fonctionnalités liés aux VBO d'OpenGL.
*/
class VBO {
	private:
        GLuint id;

        int tupleSize;
        int length;
        GLuint location;

        /**
        * Fonction de type template, elle permet de paramétrer la définition de la fonction.
        * Cette fonction créer un buffer et initialise un espace de stockage pour les données du buffer.
        * @param data Pointeur vers les données à sauvegarder dans le buffer.
        */
        template<typename T> void build(const std::vector<T> &data);

    public:
        /**
        * Constructeur, appelle le template build.
        * @param data Données à sauvegarder dans le buffer.
        * @param tupleSize Le nombre de tuples dans le vecteur de float.
        * @param attributeLocation Position des attributs dans l'enum du Shader.
        */
        VBO(const std::vector<float> &data, int tupleSize, GLuint attributeLocation);
        /**
        * Constructeur, appelle le template build.
        * @param data Données à sauvegarder dans le buffer.
        * @param attributeLocation Position des attributs dans l'enum du Shader.
        */
        VBO(const std::vector<float> &data, GLuint attributeLocation);
        /**
        * Constructeur, appelle le template build.
        * @param data Données à sauvegarder dans le buffer.
        * @param attributeLocation Position des attributs dans l'enum du Shader.
        */
        VBO(const std::vector<glm::vec2> &data, GLuint attributeLocation);
        /**
        * Constructeur, appelle le template build.
        * @param data Données à sauvegarder dans le buffer.
        * @param attributeLocation Position des attributs dans l'enum du Shader.
        */
        VBO(const std::vector<glm::vec3> &data, GLuint attributeLocation);
        /**
        * Constructeur, appelle le template build.
        * @param data Données à sauvegarder dans le buffer.
        * @param attributeLocation Position des attributs dans l'enum du Shader.
        */
        VBO(const std::vector<glm::vec4> &data, GLuint attributeLocation);
        /**
        * Destructeur.
        */
        ~VBO();

        int getTupleSize();
        int getLength();
        GLuint getLocation();
        /**
        * Appelle la fonction glBindBuffer.
        * Indique à la carte graphique d'utiliser ce VBO.
        */
        void bind();
};

#endif
