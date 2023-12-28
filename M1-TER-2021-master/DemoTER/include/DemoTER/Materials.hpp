#ifndef __MATERIALPRESETS_HPP
#define	__MATERIALPRESETS_HPP

#include "DemoTER/glwrapper/Texture.hpp"

/**
* Cette classe permet de représenter et de manipuler les matériaux.
*/
class Materials {
public:
	struct Material {
		Texture albedo;
		Texture normal;
		Texture roughness;
		Texture metallic;
		Texture ao;
	}; /**< Une structure pour un matériau. Elle comprend toutes les textures composant un matériau. */

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
	}; /**< Une enum pour les types de matériau. Elle contient tous les presets de matériau existant, ainsi que la possibilité d'en créer un personnalisé. */

	/**
	* Créer un nouveau matériau en fonction de celui désiré.
	* @param material Le matériau que l'on souhaite créer, sous forme d'une constante symbolique définie dans l'enum de cette classe.
	* @return Un pointeur vers le matériau créé.
	*/
	static Material* changeMaterial(int material);

	/**
	* Créer un matériau de type écroce d'arbre.
	* @return Un pointeur vers le matériau créé.
	*/
	static Material* bark();
	/**
	* Créer un matériau de type brique.
	* @return Un pointeur vers le matériau créé.
	*/
	static Material* bricks();
	/**
	* Créer un matériau avec les textures du Cerberus, une arme créée par Andrew Maximov et récupérée sur http://artisaverb.info/PBT.html.
	* @return Un pointeur vers le matériau créé.
	*/
	static Material* cerberus();
	/**
	* Créer un matériau de type gravier.
	* @return Un pointeur vers le matériau créé.
	*/
	static Material* ground_gravel();
	/**
	* Créer un matériau de type sol de glace.
	* @return Un pointeur vers le matériau créé.
	*/
	static Material* ground_ice();
	/**
	* Créer un matériau de type métal.
	* @return Un pointeur vers le matériau créé.
	*/
	static Material* metal();
	/**
	* Créer un matériau de type plaques de métal.
	* @return Un pointeur vers le matériau créé.
	*/
	static Material* metal_panel();
	/**
	* Créer un matériau de type mousse végétale de roche.
	* @return Un pointeur vers le matériau créé.
	*/
	static Material* rock_moss();
	/**
	* Créer un matériau de type fer rouillé.
	* @return Un pointeur vers le matériau créé.
	*/
	static Material* rusted_iron();
	/**
	* Créer un matériau avec les textures de la statue, une arme créée par Hane3D et récupérée sur https://www.turbosquid.com/fr/3d-models/thai-sandstone-female-model-1275160.
	* @return Un pointeur vers le matériau créé.
	*/
	static Material* statue();
	/**
	* Créer un matériau avec les textures d'une épée, une arme créée par KangaroOz 3D et récupérée sur https://www.turbosquid.com/fr/3d-models/sting-sword-fbx-free/1125944.
	* @return Un pointeur vers le matériau créé.
	*/
	static Material* sword();
	/**
	* Créer un matériau de type textile.
	* @return Un pointeur vers le matériau créé.
	*/
	static Material* textiles_craft();
	/**
	* Créer un matériau de type bois vernis.
	* @return Un pointeur vers le matériau créé.
	*/
	static Material* wood_varnish_rough();

	/**
	* Créer un matériau personnalisé en fonction des paramètres donnés.
	* @param color La couleur en RGB de l'albedo du matériau.
	* @param normal La couleur en RGB de la carte des normales du matériau.
	* @param rough La rugosité du matériau : 0 représente une surface parfaitement lisse et 1 représente une surface complètement rugueuse.
	* @param metal L'aspect métal du matériau : 0 représente une surface non-métallique et 1 représente une surface totalement métalique.
	* @param ao L'occlusion ambiante du matériau : 0 représente une ombre totale et 1 représente aucune occlusion ambiante.
	* @return Un pointeur vers le matériau créé.
	*/
	static Material* customMaterial(float color[3], float normal[3], float rough, float metal, float ao);

	/**
	* Créer un matériau personnalisé en fonction des paramètres donnés.
	* @param color La couleur en RGB de l'albedo du matériau.
	* @param normal La couleur en RGB de la carte des normales du matériau.
	* @param rough La rugosité du matériau : 0 représente une surface parfaitement lisse et 1 représente une surface complètement rugueuse.
	* @param metal L'aspect métallique du matériau : 0 représente une surface non-métallique et 1 représente une surface totalement métalique.
	* @param ao L'occlusion ambiante du matériau : 0 représente une ombre totale et 1 représente aucune occlusion ambiante.
	* @return Un pointeur vers le matériau créé.
	*/
	static Material* customMaterial(glm::vec3 color, glm::vec3 normal, glm::vec3 rough, glm::vec3 metal, glm::vec3 ao);
};

#endif