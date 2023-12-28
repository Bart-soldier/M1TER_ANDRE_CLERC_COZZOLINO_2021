#ifndef __DISPLAY_HPP
#define	__DISPLAY_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

/**
* Classe qui s'occupe de l'affichage. Elle wrap les m�thodes de glfw. Elle adopte le patron singleton.
*/
class Display {
	private:
		/**
		* Constructeur priv�.
		* D�finit une multitude de param�tres pour la fen�tre d'affichage, tels que : la taille au d�marrage, le titre de la fen�tre,
		* la version OpenGL, active le super-sampling SSAA x4 et initialise ImGui.
		* @param title Titre de la fen�tre.
		*/
		Display(const char *title);
		/**
		* Destructeur.
		*/
		~Display();

		static Display *instance; /**< Instance statique de la fen�tre d'affichage. */

		GLFWwindow *window;
		/**
		* Fonction de rappel pour l'affichage.
		* Elle est d�finie dans le main.
		*/
		void(*drawCallback)(void);
		/**
		* Fonction de rappel pour l'affichage de ImGui.
		* Elle est d�finie dans le main.
		*/
		void(*drawImGuiCallback)(void);
		/**
		* Fonction de rappel pour la redimmension.
		* Elle est d�finie dans le main.
		*/
		void(*resizeCallback)(float, float);

		/**
		* Est appell�e lors de la redimmension de la fen�tre.
		* Passe la main � la fonction de rappel.
		*/
		static void resizeHandle(GLFWwindow *window, int width, int height);
		/**
		* Est appell�e lors d'un clic de souris.
		* V�rifie si on clic sur la fen�tre ImGui avant de passer la main � la fonction de rappel.
		*/
		static void mouseButtonHandle(GLFWwindow *window, int button, int action, int mods);
		/**
		* Est appell�e lors de la modification de la position du curseur.
		* V�rifie si on se situe sur la fen�tre ImGui avant de passer la main � la fonction de rappel.
		*/
		static void cursorPosHandle(GLFWwindow *window, double x, double y);
		/**
		* Est appell�e lors de la modification de la molette.
		* V�rifie si on ses situe sur la fen�tre ImGui avant de passer la main � la fonction de rappel.
		*/
		static void scrollHandle(GLFWwindow *window, double xoffset, double yoffset);

		int width;
		int height;

	public:
		/**
		* Patron singleton, cr�ation de l'instance statique.
		*/
		static void init(const char *title);
		/**
		* Patron singletion, r�cup�ration de l'instance statique.
		*/
		static Display *getInstance();

		int getWidth();
		int getHeight();

		/**
		* Boucle de rendu.
		* Elle initialise les fonctions de rappel et entre dans une boucle pour l'affichage.
		*/
		void start();
		void onDraw(void(*callback)(void));
		void onDrawImGui(void(*callback)(void));
		void onResize(void(*callback)(float, float));

		/**
		* Appelle la fonction glEnable(e).
		* Active une fonctionnalit�.
		* @param e Fonctionnalit� � activer.
		*/
		void enable(GLenum e);
		/**
		* Appelle la fonction glDisable(e).
		* D�sactive une fonctionnalit�.
		* @param e Fonctionnalit� � d�sactiver.
		*/
		void disable(GLenum e);
		/**
		* Appelle la fonction glClearColor(r, g, b, a).
		* Permet de choisir la couleur par d�faut du fond.
		* @param r Canal rouge de la couleur RGBA.
		* @param g Canal vert de la couleur RGBA.
		* @param b Canal bleu de la couleur RGBA.
		* @param a Canal alpha de la couleur RGBA, d�finie � 1 par d�faut.
		*/
		void setClearColor(float r, float g, float b, float a = 1.);
		/**
		* Appelle la fonction glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT).
		* Nettoie l'�cran.
		*/
		void clear();
		/**
		* Appelle la fonction glDepthFunc(e).
		* Sp�cifie la fonction de comparaison de la profondeur .
		* @param e nom de la fonction de comparaison.
		*/
		void depthFunc(GLenum e);
		/**
		* Appelle la fonction glBindFramebuffer(GL_FRAMEBUFFER, 0).
		* Sp�cifie le frame buffer comme �tant l'�cran.
		*/
		void bindDefaultFrameBuffer();
		/**
		* Sp�cifie les param�tres de la fonction de m�lange des dessins
		* couleur finale = sfactor * source + dfactor * destination
		*/
		void blenFunc(GLenum sfactor, GLenum dfactor);
};

#endif
