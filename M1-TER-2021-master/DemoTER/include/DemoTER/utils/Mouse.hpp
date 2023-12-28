#ifndef __MOUSE_HPP
#define	__MOUSE_HPP

#include <memory>
#include "glm/vec2.hpp"

/**
* Cette classe permet de gérer le comportement de la souris. Elle adopte le patron singleton.
*/
class Mouse {
	private:
		/**
		* Constructeur privé.
		* Définit les paramètres initiaux de la souris.
		*/
		Mouse();
		static std::shared_ptr<Mouse> instance; /**< Instance statique de la souris. */

		bool pressedKeys[3];
		glm::vec2 position;
		glm::vec2 velocity;
		glm::vec2 scrollVelocity;

	public:
		/**
		* Patron singleton, création de l'instance statique.
		*/
		static void init();
		/**
		* Patron singletion, récupération de l'instance statique.
		*/
		static std::shared_ptr<Mouse> getInstance();

		/**
		* Cette méthode gère les clics de souris.
		* @param button Le button de souris cliqué.
		* @param action Si le button est pressé ou relâché.
		* @param mods Modifications particulières.
		*/
		static void buttonEvent(int button, int action, int mods);
		/**
		* Cette méthode gère le déplacement de la souris.
		* @param x Le déplacement sur l'axe des absisses.
		* @param y Le déplacement sur l'axe des ordonnées.
		*/
		static void moveEvent(double x, double y);
		/**
		* Cette méthode gère la molette.
		* @param xoffset Le paramètre x.
		* @param yoffset Le paramètre y.
		*/
		static void scrollEvent(double xoffset, double yoffset);
		/**
		* Cette méthode réinitialise la vitesse de la souris ainsi que de la molette.
		*/
		static void update();

		enum {
			LEFT,
			MIDDLE,
			RIGHT
		}; /**< Une enum. Contient les trois clics possible avec une souris classique. */

		bool isPressed(int key);
		glm::vec2 &getVelocity();
		glm::vec2 &getScrollVelocity();
		glm::vec2 &getPosition();
};

#endif
