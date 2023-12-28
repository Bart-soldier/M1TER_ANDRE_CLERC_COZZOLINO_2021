#ifndef __CAMERA_HPP
#define	__CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"

/**
* Classe générale de caméra. Elle contient les paramètres nécessaire pour n'importe quel caméra.
*/
class Camera {
    protected:
        float fov;
        float near;
        float far;
        float ratio;

        glm::vec3 center;
        glm::vec3 eye;
        glm::vec3 up;

        glm::mat4x4 projectionMatrix;
        glm::mat4x4 viewMatrix;
        glm::mat4x4 pvMatrix;

        /**
        * Met-à-jour la matrice de projection.
        */
        virtual void updateProjection();

    public:
        /**
        * Constructeur.
        * Définit des valeurs prédéfinies pour la caméra et créer la matrice de projection associée.
        */
        Camera();

        /**
        * Méthode virtuelle pure.
        * Permet de rendre la classe abstraite.
        */
        virtual void update() = 0;

        /**
        * Met-à-jour les propriétés fov, ratio, near et far de la caméra, et actualise la matrice de projection.
        */
        void setFrustum(float fov, float ratio, float near, float far);
        /**
        * Met-à-jour le ratio et actualise la matrice de projection.
        */
        void setRatio(float r);

        glm::mat4x4 &getViewMatrix();
        glm::mat4x4 &getProjection();
        glm::mat4x4 &getPVMatrix();

        glm::vec3 &getPosition();
};

#endif
