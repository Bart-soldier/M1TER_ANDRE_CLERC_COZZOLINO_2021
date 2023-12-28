#ifndef __GUIPARAMS_HPP
#define	__GUIPARAMS_HPP
#include <string>

/**
* Cette classe permet de regroupe les paramètres utilisés pour l'interface graphique.
*/
class GuiParams {
	public:
		static bool showBloom; /**< Un booléen. Permet de savoir si  on souhaite afficher uniquement l'effet d'éclat. */

		static int showCubeMap; /**< Un entier. Permet de sélectionner quel carte d'environnement afficher : 0 pour la carte haute-résolution,
								1 pour la version représenter l'irradiance et 2 pour la carte basse-résolution. */

		static std::string environmentMap; /**< Une chaîne de caractère. Un chemin vers la carte d'environnement à utiliser. */
		static bool environmentChanged; /**< Un drapeau. Permet de savoir si la carte d'environnement a été changée. */

		static int selectedObject; /**< Un entier. Indique l'objet sélectionné parmis les objets de la scène, l'entier étant l'index correspondant
								   dans la liste. */
		static bool selectedObjectChanged; /**< Un drapeau. Permet de savoir si l'objet sélectionné a été changé. */

		static bool materialChanged; /**< Un drapeau. Permet de savoir si la matériau de l'objet sélectionné a été changé. */
		static int material; /**< Un entier. Correspond à la valeur symbolique de l'enum dans la classe Material pour savoir quel
							 matériau a été selectionné pour l'objet. */
		static float customColor[3]; /**< Un tableau de trois flotants. Contient la couleur de l'albedo du matériau personnalisé sous forme RGB. */
		static float customNormal[3]; /**< Un tableau de trois flotants. Contient la couleur de la carte des normales du matériau personnalisé sous forme RGB. */
		static float customRough; /**< Un flotant. Contient la rugosité du matériau. */
		static float customMetal; /**< Un flotant. Contient l'aspect métallique du matériau. */
		static float customAO; /**< Un flotant. Contient l'occlusion ambiante du matériau. */

		static float exposure; /**< Un flotant. Correspond au paramètre d'exposition de la scène. */
		static float gamma; /**< Un flotant. Correspond au paramètre gamma de la scène. */

		static bool displaySkybox; /**< Un booléen. À vrai, on affiche la carte d'environnement ; à faux, on ne l'affiche pas. */

		static int bloomSelect; /**< Choisis la texture de bloom à visualiser */
};

#endif
