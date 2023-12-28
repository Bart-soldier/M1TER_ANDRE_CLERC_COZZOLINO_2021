#ifndef __PARSER_HPP
#define	__PARSER_HPP

#include <memory>
#include <vector>
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

/**
* Cette classe permet d'analyser un fichier .obj.
*/
class Parser {
	public:
		struct Result {
			std::vector<glm::vec3> vertex;
			std::vector<glm::vec3> normal;
			std::vector<glm::vec3> tangent;
			std::vector<glm::vec2> uv;
		}; /**< Une structure avec les résultats de l'analyse. Elle comprends les éléments composants un fichier .obj, à savoir les
		   sommets, les normales, les tangentes et possiblement les UVs. */

		/**
		* Récupère et analyse le fichier .obj indiqué, avant de sauvegarder les sommets, les normales, les tangentes et possiblement
		* les UVs dans la structure Result associée.
		* @param path Pointeur indiquant le chemin vers le maillage, sous forme de fichier .obj.
		*/
		static std::unique_ptr<Result> loadObj(const char *path);
};

#endif
