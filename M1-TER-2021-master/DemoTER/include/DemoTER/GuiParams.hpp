#ifndef __GUIPARAMS_HPP
#define	__GUIPARAMS_HPP
#include <string>

/**
* Cette classe permet de regroupe les param�tres utilis�s pour l'interface graphique.
*/
class GuiParams {
	public:
		static bool showBloom; /**< Un bool�en. Permet de savoir si  on souhaite afficher uniquement l'effet d'�clat. */

		static int showCubeMap; /**< Un entier. Permet de s�lectionner quel carte d'environnement afficher : 0 pour la carte haute-r�solution,
								1 pour la version repr�senter l'irradiance et 2 pour la carte basse-r�solution. */

		static std::string environmentMap; /**< Une cha�ne de caract�re. Un chemin vers la carte d'environnement � utiliser. */
		static bool environmentChanged; /**< Un drapeau. Permet de savoir si la carte d'environnement a �t� chang�e. */

		static int selectedObject; /**< Un entier. Indique l'objet s�lectionn� parmis les objets de la sc�ne, l'entier �tant l'index correspondant
								   dans la liste. */
		static bool selectedObjectChanged; /**< Un drapeau. Permet de savoir si l'objet s�lectionn� a �t� chang�. */

		static bool materialChanged; /**< Un drapeau. Permet de savoir si la mat�riau de l'objet s�lectionn� a �t� chang�. */
		static int material; /**< Un entier. Correspond � la valeur symbolique de l'enum dans la classe Material pour savoir quel
							 mat�riau a �t� selectionn� pour l'objet. */
		static float customColor[3]; /**< Un tableau de trois flotants. Contient la couleur de l'albedo du mat�riau personnalis� sous forme RGB. */
		static float customNormal[3]; /**< Un tableau de trois flotants. Contient la couleur de la carte des normales du mat�riau personnalis� sous forme RGB. */
		static float customRough; /**< Un flotant. Contient la rugosit� du mat�riau. */
		static float customMetal; /**< Un flotant. Contient l'aspect m�tallique du mat�riau. */
		static float customAO; /**< Un flotant. Contient l'occlusion ambiante du mat�riau. */

		static float exposure; /**< Un flotant. Correspond au param�tre d'exposition de la sc�ne. */
		static float gamma; /**< Un flotant. Correspond au param�tre gamma de la sc�ne. */

		static bool displaySkybox; /**< Un bool�en. � vrai, on affiche la carte d'environnement ; � faux, on ne l'affiche pas. */

		static int bloomSelect; /**< Choisis la texture de bloom � visualiser */
};

#endif
