#ifndef __ORBITCAMERA_HPP
#define	__ORBITCAMERA_HPP

#include "DemoTER/utils/Camera.hpp"
#include "DemoTER/utils/Mouse.hpp"

#define HALF_PI 1.57079632679

/**
* Classe correspondant à une caméra de déplacement libre. Elle hérite de la classe Camera.
*/
class OrbitCamera: public Camera {
	private:
		std::shared_ptr<Mouse> mouse; 
		glm::vec3 angles; /**< Angles d'Euler. Rotation autour de x, y et z */
		glm::vec3 movement; /**< Coordonnées de déplacement de la souris dans l'espace. */
		float distance; /**< Distance par rapport à son centre de rotation. */

	public:
		/**
		* Constructeur.
		* Récupère une instance de souris. Hérite de Camera.
		*/
		OrbitCamera();
		/**
		* Met-à-jour la position de la caméra ainsi que les matrices d'homothéties envoyés au shader, en fonction du déplacement de la souris.
		*/
		virtual void update() override;
};

#endif
