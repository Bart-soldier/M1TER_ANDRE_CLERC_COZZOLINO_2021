#ifndef __MOUSE_HPP
#define	__MOUSE_HPP

#include <memory>
#include "glm/vec2.hpp"

/**
* Cette classe permet de g�rer le comportement de la souris. Elle adopte le patron singleton.
*/
class Mouse {
	private:
		/**
		* Constructeur priv�.
		* D�finit les param�tres initiaux de la souris.
		*/
		Mouse();
		static std::shared_ptr<Mouse> instance; /**< Instance statique de la souris. */

		bool pressedKeys[3];
		glm::vec2 position;
		glm::vec2 velocity;
		glm::vec2 scrollVelocity;

	public:
		/**
		* Patron singleton, cr�ation de l'instance statique.
		*/
		static void init();
		/**
		* Patron singletion, r�cup�ration de l'instance statique.
		*/
		static std::shared_ptr<Mouse> getInstance();

		/**
		* Cette m�thode g�re les clics de souris.
		* @param button Le button de souris cliqu�.
		* @param action Si le button est press� ou rel�ch�.
		* @param mods Modifications particuli�res.
		*/
		static void buttonEvent(int button, int action, int mods);
		/**
		* Cette m�thode g�re le d�placement de la souris.
		* @param x Le d�placement sur l'axe des absisses.
		* @param y Le d�placement sur l'axe des ordonn�es.
		*/
		static void moveEvent(double x, double y);
		/**
		* Cette m�thode g�re la molette.
		* @param xoffset Le param�tre x.
		* @param yoffset Le param�tre y.
		*/
		static void scrollEvent(double xoffset, double yoffset);
		/**
		* Cette m�thode r�initialise la vitesse de la souris ainsi que de la molette.
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
