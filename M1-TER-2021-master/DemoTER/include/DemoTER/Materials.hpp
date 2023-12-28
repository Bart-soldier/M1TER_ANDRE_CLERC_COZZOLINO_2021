#ifndef __MATERIALPRESETS_HPP
#define	__MATERIALPRESETS_HPP

#include "DemoTER/glwrapper/Texture.hpp"

/**
* Cette classe permet de repr�senter et de manipuler les mat�riaux.
*/
class Materials {
public:
	struct Material {
		Texture albedo;
		Texture normal;
		Texture roughness;
		Texture metallic;
		Texture ao;
	}; /**< Une structure pour un mat�riau. Elle comprend toutes les textures composant un mat�riau. */

	enum {
		DEFAULT = -1,

		BARK = 0,
		BRICKS = 1,
		CERBERUS = 2,
		GROUND_GRAVEL = 3,
		GROUND_ICE = 4,
		METAL = 5,
		METAL_PANEL = 6,
		ROCK_MOSS = 7,
		RUSTED_IRON = 8,
		STATUE = 9,
		SWORD = 10,
		TEXTILES_CRAFT = 11,
		WOOD_VARNISH_ROUGH = 12,

		CUSTOM = 13
	}; /**< Une enum pour les types de mat�riau. Elle contient tous les presets de mat�riau existant, ainsi que la possibilit� d'en cr�er un personnalis�. */

	/**
	* Cr�er un nouveau mat�riau en fonction de celui d�sir�.
	* @param material Le mat�riau que l'on souhaite cr�er, sous forme d'une constante symbolique d�finie dans l'enum de cette classe.
	* @return Un pointeur vers le mat�riau cr��.
	*/
	static Material* changeMaterial(int material);

	/**
	* Cr�er un mat�riau de type �croce d'arbre.
	* @return Un pointeur vers le mat�riau cr��.
	*/
	static Material* bark();
	/**
	* Cr�er un mat�riau de type brique.
	* @return Un pointeur vers le mat�riau cr��.
	*/
	static Material* bricks();
	/**
	* Cr�er un mat�riau avec les textures du Cerberus, une arme cr��e par Andrew Maximov et r�cup�r�e sur http://artisaverb.info/PBT.html.
	* @return Un pointeur vers le mat�riau cr��.
	*/
	static Material* cerberus();
	/**
	* Cr�er un mat�riau de type gravier.
	* @return Un pointeur vers le mat�riau cr��.
	*/
	static Material* ground_gravel();
	/**
	* Cr�er un mat�riau de type sol de glace.
	* @return Un pointeur vers le mat�riau cr��.
	*/
	static Material* ground_ice();
	/**
	* Cr�er un mat�riau de type m�tal.
	* @return Un pointeur vers le mat�riau cr��.
	*/
	static Material* metal();
	/**
	* Cr�er un mat�riau de type plaques de m�tal.
	* @return Un pointeur vers le mat�riau cr��.
	*/
	static Material* metal_panel();
	/**
	* Cr�er un mat�riau de type mousse v�g�tale de roche.
	* @return Un pointeur vers le mat�riau cr��.
	*/
	static Material* rock_moss();
	/**
	* Cr�er un mat�riau de type fer rouill�.
	* @return Un pointeur vers le mat�riau cr��.
	*/
	static Material* rusted_iron();
	/**
	* Cr�er un mat�riau avec les textures de la statue, une arme cr��e par Hane3D et r�cup�r�e sur https://www.turbosquid.com/fr/3d-models/thai-sandstone-female-model-1275160.
	* @return Un pointeur vers le mat�riau cr��.
	*/
	static Material* statue();
	/**
	* Cr�er un mat�riau avec les textures d'une �p�e, une arme cr��e par KangaroOz 3D et r�cup�r�e sur https://www.turbosquid.com/fr/3d-models/sting-sword-fbx-free/1125944.
	* @return Un pointeur vers le mat�riau cr��.
	*/
	static Material* sword();
	/**
	* Cr�er un mat�riau de type textile.
	* @return Un pointeur vers le mat�riau cr��.
	*/
	static Material* textiles_craft();
	/**
	* Cr�er un mat�riau de type bois vernis.
	* @return Un pointeur vers le mat�riau cr��.
	*/
	static Material* wood_varnish_rough();

	/**
	* Cr�er un mat�riau personnalis� en fonction des param�tres donn�s.
	* @param color La couleur en RGB de l'albedo du mat�riau.
	* @param normal La couleur en RGB de la carte des normales du mat�riau.
	* @param rough La rugosit� du mat�riau : 0 repr�sente une surface parfaitement lisse et 1 repr�sente une surface compl�tement rugueuse.
	* @param metal L'aspect m�tal du mat�riau : 0 repr�sente une surface non-m�tallique et 1 repr�sente une surface totalement m�talique.
	* @param ao L'occlusion ambiante du mat�riau : 0 repr�sente une ombre totale et 1 repr�sente aucune occlusion ambiante.
	* @return Un pointeur vers le mat�riau cr��.
	*/
	static Material* customMaterial(float color[3], float normal[3], float rough, float metal, float ao);

	/**
	* Cr�er un mat�riau personnalis� en fonction des param�tres donn�s.
	* @param color La couleur en RGB de l'albedo du mat�riau.
	* @param normal La couleur en RGB de la carte des normales du mat�riau.
	* @param rough La rugosit� du mat�riau : 0 repr�sente une surface parfaitement lisse et 1 repr�sente une surface compl�tement rugueuse.
	* @param metal L'aspect m�tallique du mat�riau : 0 repr�sente une surface non-m�tallique et 1 repr�sente une surface totalement m�talique.
	* @param ao L'occlusion ambiante du mat�riau : 0 repr�sente une ombre totale et 1 repr�sente aucune occlusion ambiante.
	* @return Un pointeur vers le mat�riau cr��.
	*/
	static Material* customMaterial(glm::vec3 color, glm::vec3 normal, glm::vec3 rough, glm::vec3 metal, glm::vec3 ao);
};

#endif