#ifndef __ORBITCAMERA_HPP
#define	__ORBITCAMERA_HPP

#include "DemoTER/utils/Camera.hpp"
#include "DemoTER/utils/Mouse.hpp"

#define HALF_PI 1.57079632679

/**
* Classe correspondant � une cam�ra de d�placement libre. Elle h�rite de la classe Camera.
*/
class OrbitCamera: public Camera {
	private:
		std::shared_ptr<Mouse> mouse; 
		glm::vec3 angles; /**< Angles d'Euler. Rotation autour de x, y et z */
		glm::vec3 movement; /**< Coordonn�es de d�placement de la souris dans l'espace. */
		float distance; /**< Distance par rapport � son centre de rotation. */

	public:
		/**
		* Constructeur.
		* R�cup�re une instance de souris. H�rite de Camera.
		*/
		OrbitCamera();
		/**
		* Met-�-jour la position de la cam�ra ainsi que les matrices d'homoth�ties envoy�s au shader, en fonction du d�placement de la souris.
		*/
		virtual void update() override;
};

#endif
