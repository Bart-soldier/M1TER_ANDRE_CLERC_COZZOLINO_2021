#ifndef __CAMERA_HPP
#define	__CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"

/**
* Classe g�n�rale de cam�ra. Elle contient les param�tres n�cessaire pour n'importe quel cam�ra.
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
        * Met-�-jour la matrice de projection.
        */
        virtual void updateProjection();

    public:
        /**
        * Constructeur.
        * D�finit des valeurs pr�d�finies pour la cam�ra et cr�er la matrice de projection associ�e.
        */
        Camera();

        /**
        * M�thode virtuelle pure.
        * Permet de rendre la classe abstraite.
        */
        virtual void update() = 0;

        /**
        * Met-�-jour les propri�t�s fov, ratio, near et far de la cam�ra, et actualise la matrice de projection.
        */
        void setFrustum(float fov, float ratio, float near, float far);
        /**
        * Met-�-jour le ratio et actualise la matrice de projection.
        */
        void setRatio(float r);

        glm::mat4x4 &getViewMatrix();
        glm::mat4x4 &getProjection();
        glm::mat4x4 &getPVMatrix();

        glm::vec3 &getPosition();
};

#endif
