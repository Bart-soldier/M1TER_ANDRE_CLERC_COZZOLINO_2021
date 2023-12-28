#ifndef __TRANSFORM_HPP
#define	__TRANSFORM_HPP

#include <vector>
#include "glm/mat4x4.hpp"
#include "glm/vec3.hpp"
#include "glm/gtx/quaternion.hpp"

/**
* Cette classe contient toutes les méthodes associés aux translations, homothéties et rotations.
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
        * Définit des paramètres par défaut.
        */
        Transform();
        /**
        * Permet de redéfinir l'origine.
        * @param o Matrice 4D correspondant à l'origine.
        */
        void setOrigin(glm::mat4x4 &o);

        /**
        * Réalise un déplacement.
        * @param dx Déplacement selon l'axe x.
        * @param dy Déplacement selon l'axe y.
        * @param dz Déplacement selon l'axe z.
        */
        void move(float dx, float dy, float dz);
        /**
        * Définit la position.
        * @param x Coordonnée x.
        * @param y Coordonnée y.
        * @param z Coordonnée z.
        */
        void setPosition(float x, float y, float z);
        /**
        * Récupère la position.
        * @return Un vecteur 3D contenant la position.
        */
        glm::vec3 &getPosition();

        /**
        * Réalise une rotation selon l'axe x.
        * @param a L'angle, en radians.
        */
        void rotateX(float a);
        /**
        * Réalise une rotation selon l'axe y.
        * @param a L'angle, en radians.
        */
        void rotateY(float a);
        /**
        * Réalise une rotation selon l'axe z.
        * @param a L'angle, en radians.
        */
        void rotateZ(float a);
        /**
        * Réalise une rotation selon l'axe x, l'axe y et l'axe z.
        * @param ax L'angle à travers l'axe x, en radians.
        * @param ay L'angle à travers l'axe y, en radians.
        * @param az L'angle à travers l'axe z, en radians.
        */
        void setRotationZYX(float ax, float ay, float az);
        /**
        * Récupère la rotation.
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
