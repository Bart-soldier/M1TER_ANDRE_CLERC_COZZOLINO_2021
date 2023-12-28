#ifndef __DISPLAY_HPP
#define	__DISPLAY_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

/**
* Classe qui s'occupe de l'affichage. Elle wrap les méthodes de glfw. Elle adopte le patron singleton.
*/
class Display {
	private:
		/**
		* Constructeur privé.
		* Définit une multitude de paramètres pour la fenêtre d'affichage, tels que : la taille au démarrage, le titre de la fenêtre,
		* la version OpenGL, active le super-sampling SSAA x4 et initialise ImGui.
		* @param title Titre de la fenêtre.
		*/
		Display(const char *title);
		/**
		* Destructeur.
		*/
		~Display();

		static Display *instance; /**< Instance statique de la fenêtre d'affichage. */

		GLFWwindow *window;
		/**
		* Fonction de rappel pour l'affichage.
		* Elle est définie dans le main.
		*/
		void(*drawCallback)(void);
		/**
		* Fonction de rappel pour l'affichage de ImGui.
		* Elle est définie dans le main.
		*/
		void(*drawImGuiCallback)(void);
		/**
		* Fonction de rappel pour la redimmension.
		* Elle est définie dans le main.
		*/
		void(*resizeCallback)(float, float);

		/**
		* Est appellée lors de la redimmension de la fenêtre.
		* Passe la main à la fonction de rappel.
		*/
		static void resizeHandle(GLFWwindow *window, int width, int height);
		/**
		* Est appellée lors d'un clic de souris.
		* Vérifie si on clic sur la fenêtre ImGui avant de passer la main à la fonction de rappel.
		*/
		static void mouseButtonHandle(GLFWwindow *window, int button, int action, int mods);
		/**
		* Est appellée lors de la modification de la position du curseur.
		* Vérifie si on se situe sur la fenêtre ImGui avant de passer la main à la fonction de rappel.
		*/
		static void cursorPosHandle(GLFWwindow *window, double x, double y);
		/**
		* Est appellée lors de la modification de la molette.
		* Vérifie si on ses situe sur la fenêtre ImGui avant de passer la main à la fonction de rappel.
		*/
		static void scrollHandle(GLFWwindow *window, double xoffset, double yoffset);

		int width;
		int height;

	public:
		/**
		* Patron singleton, création de l'instance statique.
		*/
		static void init(const char *title);
		/**
		* Patron singletion, récupération de l'instance statique.
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
		* Active une fonctionnalité.
		* @param e Fonctionnalité à activer.
		*/
		void enable(GLenum e);
		/**
		* Appelle la fonction glDisable(e).
		* Désactive une fonctionnalité.
		* @param e Fonctionnalité à désactiver.
		*/
		void disable(GLenum e);
		/**
		* Appelle la fonction glClearColor(r, g, b, a).
		* Permet de choisir la couleur par défaut du fond.
		* @param r Canal rouge de la couleur RGBA.
		* @param g Canal vert de la couleur RGBA.
		* @param b Canal bleu de la couleur RGBA.
		* @param a Canal alpha de la couleur RGBA, définie à 1 par défaut.
		*/
		void setClearColor(float r, float g, float b, float a = 1.);
		/**
		* Appelle la fonction glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT).
		* Nettoie l'écran.
		*/
		void clear();
		/**
		* Appelle la fonction glDepthFunc(e).
		* Spécifie la fonction de comparaison de la profondeur .
		* @param e nom de la fonction de comparaison.
		*/
		void depthFunc(GLenum e);
		/**
		* Appelle la fonction glBindFramebuffer(GL_FRAMEBUFFER, 0).
		* Spécifie le frame buffer comme étant l'écran.
		*/
		void bindDefaultFrameBuffer();
		/**
		* Spécifie les paramètres de la fonction de mélange des dessins
		* couleur finale = sfactor * source + dfactor * destination
		*/
		void blenFunc(GLenum sfactor, GLenum dfactor);
};

#endif
