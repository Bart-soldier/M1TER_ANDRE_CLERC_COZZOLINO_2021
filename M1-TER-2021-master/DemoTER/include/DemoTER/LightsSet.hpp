#ifndef __LIGHTSSET_HPP
#define __LIGHTSSET_HPP

#include "DemoTER/utils/Transform.hpp"
#include <vector>

/**
* Classe contienant une liste de lumiere, et permet de preparer les donnees de ces dernieres pour les envoyer a un shader
*/
class LightsSet {
	public:

		/**
		* Classe représentant une source de lumiere ponctuelle
		*/
		class Light: public Transform {
			private:
				glm::vec3 color;
				float intensity;
				bool on;

			public:
				Light();
				/**
				* Choisi la couleur, valeurs entre 0 et 1
				*/
				void setColor(float r, float g, float b);
				glm::vec3 &getColor();

				/**
				* L'intensite permet de definire la puissance de la source lumineur
				* plus cette valeur est grande, plus ca eclaira loin
				*/
				void setIntensity(float i);
				float& getIntensity();

				/**
				* Allume la lumiere
				*/
				void turnOn();

				/**
				* Eteint la lumiere
				*/
				void turnOff();

				/**
				* Choisi l'etat de la lumiere (allume ou eteint)
				*/
				void setOn(bool o);
				bool isOn();

				/**
				* Retourne la puissance lumineuse sur les canaux rouge vert et bleu
				*/
				glm::vec3 getLux();
		};

	private:
		std::vector<glm::vec3> lightPositionsBuffer;
		std::vector<glm::vec3> lightColorsBuffer;

		std::vector<Light> lights;

	public:
		LightsSet(int count);
		int getLightCount();

		/**
		* Retourne une lumiere pour pouvoir la modifier
		* @param index.
		*/
		Light &light(int index);

		/**
		* Prepare les buffers de positions et de couleurs des lumieres pour les envoyer au shader
		*/
		void update();

		std::vector<glm::vec3> &getLightPositions();
		std::vector<glm::vec3> &getLightColors();
};

#endif
