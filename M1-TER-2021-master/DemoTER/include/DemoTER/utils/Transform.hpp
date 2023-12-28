#ifndef __TRANSFORM_HPP
#define	__TRANSFORM_HPP

#include <vector>
#include "glm/mat4x4.hpp"
#include "glm/vec3.hpp"
#include "glm/gtx/quaternion.hpp"

/**
* Cette classe contient toutes les m�thodes associ�s aux translations, homoth�ties et rotations.
*/
class Transform {
    private:
        glm::vec3 position;
        glm::quat rotation;
        glm::mat4x4 matrix;
        glm::mat4x4 origin;

    public:
        /**
        * Constructeur.
        * D�finit des param�tres par d�faut.
        */
        Transform();
        /**
        * Permet de red�finir l'origine.
        * @param o Matrice 4D correspondant � l'origine.
        */
        void setOrigin(glm::mat4x4 &o);

        /**
        * R�alise un d�placement.
        * @param dx D�placement selon l'axe x.
        * @param dy D�placement selon l'axe y.
        * @param dz D�placement selon l'axe z.
        */
        void move(float dx, float dy, float dz);
        /**
        * D�finit la position.
        * @param x Coordonn�e x.
        * @param y Coordonn�e y.
        * @param z Coordonn�e z.
        */
        void setPosition(float x, float y, float z);
        /**
        * R�cup�re la position.
        * @return Un vecteur 3D contenant la position.
        */
        glm::vec3 &getPosition();

        /**
        * R�alise une rotation selon l'axe x.
        * @param a L'angle, en radians.
        */
        void rotateX(float a);
        /**
        * R�alise une rotation selon l'axe y.
        * @param a L'angle, en radians.
        */
        void rotateY(float a);
        /**
        * R�alise une rotation selon l'axe z.
        * @param a L'angle, en radians.
        */
        void rotateZ(float a);
        /**
        * R�alise une rotation selon l'axe x, l'axe y et l'axe z.
        * @param ax L'angle � travers l'axe x, en radians.
        * @param ay L'angle � travers l'axe y, en radians.
        * @param az L'angle � travers l'axe z, en radians.
        */
        void setRotationZYX(float ax, float ay, float az);
        /**
        * R�cup�re la rotation.
        * @return Un quaternion contenant la rotation.
        */
        glm::quat &getRotation();

        /**
        * Fournit les transformations sous forme d'un matrice de transformation.
        * @return Une matrice de transformation.
        */
        glm::mat4x4 &toMatrix();
};

#endif
